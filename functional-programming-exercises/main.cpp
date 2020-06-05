#include <iostream>
#include <vector>
#include <list>
#include <forward_list>
#include <set>
#include <deque>

int main() {
   std::list<int> numbers2 {4,8,15,8,16,8,23,42};
   std::forward_list<int> numbers3 {4,8,15,8,16,8,23,42};
   std::vector<int> numbers4 {4,8,15,8,16,8,23,42};
   std::set<int> numbers5 {4,8,15,8,16,8,23,42};
   std::deque<int> numbers6 {4,8,15,8,16,8,23,42};
   for (auto & num : numbers3)
       std::cout << num << std::endl;
   for (auto iter = numbers2.begin();
        iter != numbers2.end();
        ++iter){
       auto & num = *iter;
   }
    std::forward_list<int> w(std::move(numbers3));

    return 0;
}