#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <memory>
#include <deque>
#include <filesystem>

#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

#include <aoc/path_def.hpp>

enum class file_type { file, dir };
struct file
{
    std::string full_path;
    std::string name;
    file* parent;
    size_t size;
    file_type type;
    std::map<std::string, file*> files;

    file(std::string const& full_path, file* parent) : full_path(full_path), name(name_from_path(full_path)), parent(parent), size(0), type(file_type::dir) {}
    file(std::string const& full_path, file* parent, size_t size) : full_path(full_path), name(name_from_path(full_path)), parent(parent), size(size), type(file_type::file) {}
    std::string name_from_path(std::filesystem::path const& path)
    {
        return path.filename();
    }
};

bool operator< (file const& lhs, file const& rhs)
{
    return lhs.full_path < rhs.full_path;
}

using filesystem_type = std::map<std::string, std::unique_ptr<file> >;
filesystem_type all_files;

struct instruction_handler
{
    file* root;
    file* curr;
    std::filesystem::path path;

    instruction_handler(file* file) : root(file), curr(root) {}
    void handle_instructions(std::istream& input)
    {
        std::string line;
        while(std::getline(input, line))
        {
            if ( line == "" ) return;
            std::vector<std::string> instruction_tokens;
            boost::algorithm::split(instruction_tokens, line, boost::is_any_of(" "));
            if ( instruction_tokens[0] == "$" )
            {
                if ( instruction_tokens[1] == "cd" )
                {
                    curr = change_directory(instruction_tokens[2]);
                }
                // else ls
            }
            else //continue ls'ing
            {
                if ( instruction_tokens[0] == "dir" )
                {
                    auto the_file = std::make_unique<file>(path / instruction_tokens[1], curr);
                    curr->files[instruction_tokens[1]] = the_file.get();
                    all_files[the_file->full_path] = std::move(the_file);
                }
                else // it's not a dir
                {
                    auto the_file = std::make_unique<file>(path / instruction_tokens[1], curr, boost::lexical_cast<size_t>(instruction_tokens[0]));
                    curr->files[instruction_tokens[1]] = the_file.get();
                    all_files[the_file->full_path] = std::move(the_file);
                }
            }
        }
    }

    file* change_directory(std::string const& name)
    {
        if ( name == "/" )
        {
            path = name;
            return root;
        }
        if ( name == ".." )
        {
            path = path.parent_path();
            return curr->parent;
        }
        path /= name;
        return all_files[path].get();
    }
};

size_t file_size(file* const file)
{
    if (file->size != 0 ) return file->size;
    std::for_each(file->files.begin(), file->files.end(), [&](auto const& entry){ file->size += file_size(entry.second); });
    return file->size;
}

size_t sum_dirs_smaller_than(filesystem_type const& fs, size_t threshold)
{
    size_t result = 0;
    for ( auto&& file_entry : fs )
    {
        auto size = file_size(file_entry.second.get());
        if ( size <= threshold && file_entry.second->type == file_type::dir ) result += size;
    }
    return result;
}

size_t smallest_dir_size_to_del()
{
    size_t unused = 70000000 - all_files["/"]->size;
    size_t needs = 30000000 - unused;
    file* best = all_files["/"].get();
    for ( auto&& file_entry : all_files )
    {
        if ( file_entry.second->type == file_type::dir &&
             file_entry.second->size > needs &&
             file_entry.second->size < best->size )
        {
            best = file_entry.second.get();
        }
    }
    return best->size;
}


int main()
{
    std::ifstream input(PROJEUL_AOC_PATH "/07_input.txt");
    if ( !input ) throw std::runtime_error("Failed to open input file");

    all_files["/"] = std::make_unique<file>("", nullptr);
    auto handler = instruction_handler(all_files["/"].get());
    handler.handle_instructions(input);

    auto p1 = sum_dirs_smaller_than(all_files, 100000);
    std::cout << "Part 1 result: " << p1 << std::endl;

    auto p2 = smallest_dir_size_to_del();
    std::cout << "Part 2 result: " << p2 << std::endl;

    return 0;
}
