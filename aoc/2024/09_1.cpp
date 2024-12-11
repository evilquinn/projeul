
#include <algorithm>
#include <fstream>
#include <iostream>
#include <list>
#include "../path_def.hpp"

std::string test_string = "2333133121414131402";

typedef std::pair<int, int>
    file_type;  // first: file id, second: consecutive blocks
typedef std::list<file_type>
    disk_type;  // list of file_types represents the disk

disk_type examine_disk(const std::string& input)
{
    disk_type result;
    size_t file_id = 0;
    bool is_file   = false;
    for (auto&& part : input)
    {
        is_file = !is_file;  // always flip, even if we skip zero length empty
        int length = part - '0';
        if (length == 0)
            continue;  // skip empty block
        if (is_file)
        {
            result.insert(result.end(), { file_id, part - '0' });
            ++file_id;
        }
        else
        {
            result.insert(result.end(), { -1, part - '0' });
        }
    }
    return result;
}

size_t compacted_checksum(std::string const& input)
{
    auto disk = examine_disk(input);

    auto first_empty =
        std::find_if(disk.begin(), disk.end(), [](const file_type& file) {
            return file.first == -1;
        });
    if (first_empty == disk.end())
        throw std::runtime_error("No empty slots!?");
    auto last_file =
        std::find_if(disk.rbegin(), disk.rend(), [](const file_type& file) {
            return file.first != -1;
        });
    if (last_file == disk.rend())
        throw std::runtime_error("No file!?");

    // 'member, last_file is reverse iterator!

    // perhaps can exit when distance(begin, first_empty) >
    // distance(last_file, rend)...? distance is expensive for list... perhaps
    // can achieve the same by manual count as we search for it...
    while (last_file != disk.rend() && first_empty != disk.end() &&
           std::distance(disk.begin(), first_empty) <
               std::distance(last_file, disk.rend()))
    {
        // try move last_file into first_empty
        int& free_space = first_empty->second;
        int& file_size  = last_file->second;
        if (free_space >= file_size)
        {
            // can fully move last_file into first_empty, erase last_file,
            // potentially reduce or erase first_empty
            int remaining = free_space - file_size;
            disk.insert(first_empty, *last_file);
            auto empty_me = last_file;
            last_file     = std::find_if(
                std::next(last_file), disk.rend(), [](const file_type& file) {
                    return file.first != -1;
                });
            empty_me->first     = -1;
            first_empty->second = remaining;
            if (remaining == 0)
            {
                first_empty = std::find_if(
                    std::next(first_empty),
                    disk.end(),
                    [](const file_type& file) { return file.first == -1; });
            }
        }
        else
        {
            // can fully replace first_empty with part of last_file, reduce
            // last file
            int remaining      = last_file->second - first_empty->second;
            first_empty->first = last_file->first;
            last_file->second  = remaining;
            first_empty        = std::find_if(
                std::next(first_empty),
                disk.end(),
                [](const file_type& file) { return file.first == -1; });
        }
    }

    // now checksum
    size_t result = 0;
    size_t idx    = 0;
    for (auto it = disk.begin(); it != disk.end(); ++it)
    {
        if (it->first == -1)
        {
            if (it->second == 0)
                continue;
            else
                break;
        }

        // magic
        size_t next_idx = idx + it->second;
        for (size_t i = idx; i < next_idx; ++i)
        {
            result += it->first * i;
        }
        idx = next_idx;
    }
    return result;
}

int main()
{
    std::string input_path(PROJEUL_AOC_PATH "/09_input.txt");
    std::ifstream input(input_path);
    if (!input)
        throw std::runtime_error(
            std::string("Error reading input file: ").append(input_path));

    std::string input_string;
    std::getline(input, input_string);
    auto result = compacted_checksum(input_string);
    std::cout << "Part 1 result: " << result << std::endl;

    return 0;
}
