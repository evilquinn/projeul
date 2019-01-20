
#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>

namespace evilquinn {

template<typename IStream>
IStream& getlogline(IStream& log_stream, std::string& log_line)
{
    static const std::regex log_line_begin_matcher("^<\\d\\d\\d>\\d \\d\\d\\d\\d");
    std::ostringstream line_acca;
    bool first_line = true;
    auto pos_cache = log_stream.tellg();
    for ( std::string line; std::getline(log_stream, line); )
    {
        if ( !first_line && std::regex_search(line, log_line_begin_matcher) )
        {
            // reset the stream to effectively put the line back in
            // for next time
            log_stream.seekg(pos_cache);
            break;
        }
        // remember this position to revert to if we detect the next line is
        // a new log beginning
        pos_cache = log_stream.tellg();
        if ( !first_line )
        {
            line_acca << "\n";
        }
        line_acca << line;
        first_line = false;
    }
    log_line = std::move(line_acca.str());
    if ( !log_line.empty() )
    {
        // if we captured something, make sure we return a "good" state
        log_stream.clear();
    }
    return log_stream;
}

} // end namepsace evilquinn

int main()
{
    std::ifstream log_stream("/home/evilquinn/git/projeul/log_file_stream/log_file_small.txt");

    if ( !log_stream.is_open() )
    {
        std::cout << "wtf?" << std::endl;
    }

    std::string logline;
    while ( evilquinn::getlogline(log_stream, logline) )
    {
        std::cout << logline << std::endl;
        std::cout << "BOOM!" << std::endl;
    }

    return 0;
}