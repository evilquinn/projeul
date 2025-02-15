
#include <iostream>
#include <map>
#include <vector>
#include <utility>
#include <boost/asio.hpp>
#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/algorithm/string.hpp>
#include <websocketpp/client.hpp>
#include <websocketpp/config/asio_no_tls_client.hpp>

static const int max_input_size = 128;
class cli
{
public:
    explicit cli(boost::asio::io_context& io_context) :
        io_context_(io_context),
        input_(io_context_, ::dup(STDIN_FILENO)),
        input_buffer_(max_input_size)
    {
    }
    typedef boost::function<void(boost::system::error_code const&, const std::string&)> async_read_callback;
private:
    boost::asio::io_context& io_context_;
    boost::asio::posix::stream_descriptor input_;
    boost::asio::streambuf input_buffer_;
};

typedef websocketpp::client<websocketpp::config::asio_client> client;

class connectioner {
public:
    typedef boost::shared_ptr<connectioner> ptr;

    connectioner(int id, websocketpp::connection_hdl hdl, std::string uri) :
        id_(id),
        hdl_(hdl),
        status_("Connecting"),
        uri_(uri),
        server_("N/A"),
        messages_()
    {}

    void on_open(client * c, websocketpp::connection_hdl hdl)
    {
        status_ = "Open";
        client::connection_ptr con = c->get_con_from_hdl(hdl);
        server_ = con->get_response_header("Server");
    }

    void on_fail(client * c, websocketpp::connection_hdl hdl)
    {
        status_ = "Failed";
        client::connection_ptr con = c->get_con_from_hdl(hdl);
        server_ = con->get_response_header("Server");
        error_reason_ = con->get_ec().message();
    }
    void on_close(client * c, websocketpp::connection_hdl hdl)
    {
        status_ = "Closed";
        client::connection_ptr con = c->get_con_from_hdl(hdl);
        std::stringstream s;
        s << "close code: " << con->get_remote_close_code() << " ("
          << websocketpp::close::status::get_string(con->get_remote_close_code())
          << "), close reason: " << con->get_remote_close_reason();
        error_reason_ = s.str();
    }
    void on_message(websocketpp::connection_hdl, client::message_ptr msg)
    {
        if ( msg->get_opcode() == websocketpp::frame::opcode::text )
        {
            messages_.push_back(msg->get_payload());
        }
        else
        {
            messages_.push_back(websocketpp::utility::to_hex(msg->get_payload()));
        }
    }
    websocketpp::connection_hdl get_hdl() const
    {
        return hdl_;
    }
    int get_id() const
    {
        return id_;
    }
    std::string get_status() const
    {
        return status_;
    }
    void record_sent_message(std::string message)
    {
        messages_.push_back(">> " + message);
    }
    friend std::ostream & operator<< (std::ostream & out, connectioner const & data);
private:
    int id_;
    websocketpp::connection_hdl hdl_;
    std::string status_;
    std::string uri_;
    std::string server_;
    std::string error_reason_;
    std::vector<std::string> messages_;
};

std::ostream & operator<< (std::ostream & out, connectioner const & data)
{
    out << "> URI: " << data.uri_ << "\n"
        << "> Status: " << data.status_ << "\n"
        << "> Remote Server: " << (data.server_.empty() ? "None Specified" : data.server_) << "\n"
        << "> Error/close reason: " << (data.error_reason_.empty() ? "N/A" : data.error_reason_) << "\n";

    out << "> Messages Processed: (" << data.messages_.size() << ") \n";

    std::vector<std::string>::const_iterator it;
    for (it = data.messages_.begin(); it != data.messages_.end(); ++it)
    {
        out << *it << "\n";
    }
    return out;
}

class endpointer {
public:
    endpointer () : next_id_(0)
    {
        endpoint_.clear_access_channels(websocketpp::log::alevel::all);
        endpoint_.clear_error_channels(websocketpp::log::elevel::all);

        endpoint_.init_asio();
        endpoint_.start_perpetual();

        thread_ = boost::make_shared<boost::thread>(&client::run, &endpoint_);
    }

    ~endpointer()
    {
        endpoint_.stop_perpetual();

        for (con_list::const_iterator it = connection_list_.begin(); it != connection_list_.end(); ++it)
        {
            if (it->second->get_status() != "Open")
            {
                // Only close open connections
                continue;
            }

            std::cout << "> Closing connection " << it->second->get_id() << std::endl;

            websocketpp::lib::error_code ec;
            endpoint_.close(it->second->get_hdl(), websocketpp::close::status::going_away, "", ec);
            if (ec)
            {
                std::cout << "> Error closing connection "
                          << it->second->get_id()
                          << ": "
                          << ec.message() << std::endl;
            }
        }

        thread_->join();
    }

    int connect(std::string const & uri)
    {
        websocketpp::lib::error_code ec;

        client::connection_ptr con = endpoint_.get_connection(uri, ec);

        if (ec)
        {
            std::cout << "> Connect initialization error: " << ec.message() << std::endl;
            return -1;
        }

        int new_id = next_id_++;
        connectioner::ptr metadata_ptr = boost::make_shared<connectioner>(new_id, con->get_handle(), uri);
        connection_list_[new_id] = metadata_ptr;

        con->set_open_handler(boost::bind(
            &connectioner::on_open,
            metadata_ptr,
            &endpoint_,
            boost::placeholders::_1
        ));
        con->set_fail_handler(boost::bind(
            &connectioner::on_fail,
            metadata_ptr,
            &endpoint_,
            boost::placeholders::_1
        ));
        con->set_close_handler(boost::bind(
            &connectioner::on_close,
            metadata_ptr,
            &endpoint_,
            boost::placeholders::_1
        ));
        con->set_message_handler(boost::bind(
            &connectioner::on_message,
            metadata_ptr,
            boost::placeholders::_1,
            boost::placeholders::_2
        ));
        endpoint_.connect(con);

        return new_id;
    }

    connectioner::ptr get_metadata(int id) const
    {
        con_list::const_iterator metadata_it = connection_list_.find(id);
        if (metadata_it == connection_list_.end())
        {
            return connectioner::ptr();
        }
        else
        {
            return metadata_it->second;
        }
    }

    void close(int id, websocketpp::close::status::value code, const std::string& reason)
    {
        con_list::iterator metadata_it = connection_list_.find(id);
        if (metadata_it == connection_list_.end())
        {
            std::cout << "> No connection found with id " << id << std::endl;
            return;
        }

        websocketpp::lib::error_code ec;
        endpoint_.close(metadata_it->second->get_hdl(), code, reason, ec);
        if (ec)
        {
            std::cout << "> Error initiating close: " << ec.message() << std::endl;
        }
    }

    void send(int id, std::string message)
    {
        con_list::iterator metadata_it = connection_list_.find(id);
        if (metadata_it == connection_list_.end())
        {
            std::cout << "> No connection found with id " << id << std::endl;
            return;
        }

        websocketpp::lib::error_code ec;
        endpoint_.send(metadata_it->second->get_hdl(), message, websocketpp::frame::opcode::text, ec);
        if (ec)
        {
            std::cout << "> Error sending message: " << ec.message() << std::endl;
            return;
        }
        metadata_it->second->record_sent_message(message);
    }

private:
    typedef std::map<int, connectioner::ptr> con_list;
    client endpoint_;
    boost::shared_ptr<boost::thread> thread_;
    con_list connection_list_;
    int next_id_;
};

std::string read_from_user(const std::string& prompt = "command> ")
{
    std::string line;
    std::cout << prompt;
    std::getline(std::cin, line);
    return line;
}

void main_loop()
{
    endpointer endpoint;
    bool quitting = false;
    while( !quitting )
    {
        std::string command = read_from_user();
        if ( command == "quit" )
        {
            std::cout << "quitting...\n";
            quitting = true;
        }
        else if ( command == "help" )
        {
            std::cout
                << "\nCommand List:\n"
                << "help: Display this help text\n"
                << "quit: Exit the program\n"
                << std::endl;
        }
        else if ( boost::starts_with(command, "connect") )
        {
            if ( command.size() < 8 ) throw std::runtime_error("connect command with no argumant");
            std::string url = command.substr(8);
            int id = endpoint.connect(url);
            if (id == -1)
            {
                std::cout << "> Failed to connect to url " << url << std::endl;
            }
            else
            {
                std::cout << "> Created connection with id " << id << std::endl;
            }

        }
        else if ( boost::starts_with(command, "show") )
        {
            if ( command.size() < 5 ) throw std::runtime_error("show command with no argumant");
            int id = atoi(command.substr(5).c_str());
            connectioner::ptr metadata = endpoint.get_metadata(id);
            if (metadata)
            {
                std::cout << *metadata << std::endl;
            }
            else
            {
                std::cout << "> Unknown connection id " << id << std::endl;
            }
        }
        else if ( boost::starts_with(command, "close") )
        {
            std::stringstream ss(command);
            std::string cmd;
            int id = -1;
            int close_code = websocketpp::close::status::normal;
            std::string reason;
            ss >> cmd >> id >> close_code;
            std::getline(ss, reason);

            endpoint.close(id, close_code, reason);
        }
        else if ( boost::starts_with(command, "send") )
        {
            std::stringstream ss(command);
            std::string cmd;
            int id;
            std::string message = "";
            ss >> cmd >> id;
            std::getline(ss, message);

            endpoint.send(id, message);
        }
        else
        {
            std::cout << "unrecognised command: " << command << "\n";
        }
    }
}

int main()
{

    boost::asio::io_context io_context;
    cli clier(io_context);
    std::cout << "hello" << std::endl;
    main_loop();
    return 0;
}
