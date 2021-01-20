
#include <iostream>
#include <map>
#include <boost/asio.hpp>
#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/algorithm/string.hpp>
#include <websocketpp/client.hpp>
#include <websocketpp/config/asio_no_tls_client.hpp>

class cli
{
public:
    cli(boost::asio::io_context& io_context) :
        io_context_(io_context)
    {}
    typedef boost::function<void(boost::system::error_code const&, const std::string&)> async_read_callback;
private:
    boost::asio::io_context& io_context_;
};

typedef websocketpp::client<websocketpp::config::asio_client> client;

class connectioner {
public:
    typedef boost::shared_ptr<connectioner> ptr;

    connectioner(int id, websocketpp::connection_hdl hdl, std::string uri)
      : id_(id)
      , hdl_(hdl)
      , status_("Connecting")
      , uri_(uri)
      , server_("N/A")
    {}

    void on_open(client * c, websocketpp::connection_hdl hdl) {
        status_ = "Open";

        client::connection_ptr con = c->get_con_from_hdl(hdl);
        server_ = con->get_response_header("Server");
    }

    void on_fail(client * c, websocketpp::connection_hdl hdl) {
        status_ = "Failed";

        client::connection_ptr con = c->get_con_from_hdl(hdl);
        server_ = con->get_response_header("Server");
        error_reason_ = con->get_ec().message();
    }
    friend std::ostream & operator<< (std::ostream & out, connectioner const & data);
private:
    int id_;
    websocketpp::connection_hdl hdl_;
    std::string status_;
    std::string uri_;
    std::string server_;
    std::string error_reason_;
};

std::ostream & operator<< (std::ostream & out, connectioner const & data) {
    out << "> URI: " << data.uri_ << "\n"
        << "> Status: " << data.status_ << "\n"
        << "> Remote Server: " << (data.server_.empty() ? "None Specified" : data.server_) << "\n"
        << "> Error/close reason: " << (data.error_reason_.empty() ? "N/A" : data.error_reason_);

    return out;
}

class endpointer {
public:
    endpointer () {
        endpoint_.clear_access_channels(websocketpp::log::alevel::all);
        endpoint_.clear_error_channels(websocketpp::log::elevel::all);

        endpoint_.init_asio();
        endpoint_.start_perpetual();

        thread_ = boost::make_shared<boost::thread>(&client::run, &endpoint_);
    }
    int connect(std::string const & uri)
    {
        websocketpp::lib::error_code ec;

        client::connection_ptr con = endpoint_.get_connection(uri, ec);

        if (ec) {
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

        endpoint_.connect(con);

        return new_id;
    }

    connectioner::ptr get_metadata(int id) const
    {
        con_list::const_iterator metadata_it = connection_list_.find(id);
        if (metadata_it == connection_list_.end()) {
            return connectioner::ptr();
        } else {
            return metadata_it->second;
        }
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
        else if (boost::starts_with(command, "connect") )
        {
            int id = endpoint.connect(command.substr(8));
            if (id != -1) {
                std::cout << "> Created connection with id " << id << std::endl;
            }
        }
        else if (command.substr(0,4) == "show")
        {
            int id = atoi(command.substr(5).c_str());

            connectioner::ptr metadata = endpoint.get_metadata(id);
            if (metadata) {
                std::cout << *metadata << std::endl;
            } else {
                std::cout << "> Unknown connection id " << id << std::endl;
            }
        }
        else
        {
            std::cout << "unrecognised command: " << command << "\n";
        }
    }
}

int main()
{

    std::cout << "hello" << std::endl;
    main_loop();
    return 0;
}
