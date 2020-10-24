#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <stdexcept>

#include <boost/foreach.hpp>


const int max_cap = 32;
typedef std::pair<std::string, std::string> parsed_line_type;
std::ostream& operator<<(std::ostream& os, const parsed_line_type& pl)
{
    if ( os )
    {
        os << "[ " << pl.first << ", " << pl.second << " ]";
    }
    return os;
}
class readbuf
{
public:
    readbuf() :
        buf_(),
        read_pos_(),
        source_("./flash/my_lines.txt")
    {
        if ( !source_ )
        {
            throw std::runtime_error("failed to open source file.");
        }
        //else std::cout << source_.rdbuf() << std::endl;
        buf_.resize(max_cap);
        read_pos_ = buf_.end();
    }
    parsed_line_type get_line()
    {
        auto endline_pos = std::find(read_pos_, buf_.end(), '\n');
        if ( endline_pos == buf_.end() && source_ )
        {
            prime_next_chunk();
            endline_pos = std::find(read_pos_, buf_.end(), '\n');
        }
        parsed_line_type result = parse_line(read_pos_, endline_pos);
        read_pos_ = endline_pos;
        if ( read_pos_ != buf_.end() )
        {
            ++read_pos_;
        }
        return result;
    }
    friend std::ostream& operator<<(std::ostream& os, const readbuf& rb);
private:
    void prime_next_chunk()
    {
        // copies all "unread" data, don't call carelessly with more data than necessary
        auto avail = std::distance(read_pos_, buf_.end());
        std::move(read_pos_, buf_.end(), buf_.begin());
        read_pos_ = buf_.begin();
        source_.read(buf_.data() + avail, buf_.size() - avail);
        buf_.resize(avail + source_.gcount());
    }
    parsed_line_type parse_line(std::vector<char>::iterator begin, std::vector<char>::iterator end)
    {
        auto comma_pos = std::find(begin, end, ',');
        return { std::string(begin, comma_pos), std::string(comma_pos == end ? comma_pos : comma_pos + 1, end) };
    }

    std::vector<char> buf_;
    std::vector<char>::iterator read_pos_;
    std::ifstream source_;
};
std::ostream& operator<<(std::ostream& os, const readbuf& rb)
{
    if ( os )
    {
        os << "[";
        std::string sep(" ");
        for ( auto it = rb.read_pos_; it != rb.buf_.end(); ++it )
        {
            os << sep << *it;
            sep = ", ";
        }
        os << " ]";
    }
    return os;
}

int main()
{
    readbuf rb;
    for ( parsed_line_type line = rb.get_line(); line != parsed_line_type{ "", "" }; line = rb.get_line() )
    {
        //std::cout << "readbuf: " << rb << std::endl;
        std::cout << "line  : " << line << std::endl;
    }
    return 0;
}
