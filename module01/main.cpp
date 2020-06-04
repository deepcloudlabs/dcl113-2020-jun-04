#include <iostream>
#include <vector>
#include <fstream>
#include <ranges>
#include <execution>
#include <parallel/algorithm>

int
count_lines(const std::string &file){
    std::ifstream  in(file);
            // internal loop
    return std::count(std::istreambuf_iterator<char>(in),
              std::istreambuf_iterator<char>(), '\n');
}

std::vector<int>
count_lines_functional(const std::vector<std::string> &files) {
   std::vector<int> result(files.size());
   // internal loop
   std::transform(std::execution::par, files.cbegin(),files.cend(),result.begin(), count_lines);
   return result;
}
namespace rng = std::ranges;

template <rng::range R>
constexpr auto to_vector(R &&r){
    using elem_t = std::decay_t<rng::range_value_t<R>>;
    return std::vector<elem_t>{r.begin(), r.end()};
}
std::ifstream open_file(const std::string &file){
    return std::ifstream(file);
}

int
count_lines_file(std::ifstream in){
    return std::count(std::istreambuf_iterator<char>(in),
                      std::istreambuf_iterator<char>(), '\n');
}

// C++ Ranges
std::vector<int>
count_lines_functional_with_ranges(const std::vector<std::string> &files) {
    // internal loop, Lazy evaluation
    // files => (open files) => (line number, int)
   return to_vector( files | std::ranges::views::transform(open_file)
                           | std::ranges::views::transform(count_lines_file) );
}

std::vector<int>
count_lines_imperative(const std::vector<std::string> &files){
   std::vector<int> result;
   // external loop
   for (const auto &file : files){
       char c;
       int line_count = 0;
       std::ifstream in(file);
       while (in.get(c)){
           if (c=='\n')
               ++line_count;
       }
       result.push_back(line_count);
   }
   return result;
}

int main() {
    std::vector<std::string> files;
    files.push_back(std::string("c:\\tmp\\dictionary-tur.txt"));
    files.push_back(std::string("c:\\tmp\\notes-hives.txt"));
    files.push_back(std::string("c:\\tmp\\spark-notes.txt"));
    for (auto &line : count_lines_functional_with_ranges(files)){
        std::cout << line << std::endl;
    }
    for (auto &line : count_lines_functional(files)){
        std::cout << line << std::endl;
    }
    return 0;
}