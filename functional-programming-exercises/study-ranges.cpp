#include "city.h"
#include "country.h"
#include "world-util.h"

#include <vector>
#include <iostream>
#include <ranges>
#include <functional>
#include <numeric>

using namespace std;
using namespace world;

map<int,shared_ptr<city>> cities;
map<string,shared_ptr<country>> countries;

int main(){
    create_world();
    auto even_filter = [](int x){
        cout << "even_filter" << endl;
        return x%2 == 0;
    };
    auto squared = [](int x){
        cout << "squared" << endl;
        return x*x;
    };

    std::vector<int> numbers {4,8,15,16,23,42};
    for (auto num : numbers | std::ranges::views::filter(even_filter)
                            | std::ranges::views::transform(squared)){
        std::cout << num << std::endl;
    }
    auto asian = [](shared_ptr<country> ctry){
        return ctry->continent == "Asia";
    };
    auto to_name = [](shared_ptr<country> ctry){
        return ctry->name;
    };
    auto to_size = [](string s){
        return s.length();
    };
    auto shorter_than = [](string s,int size){
        return s.length() < size;
    };
    auto shorter_than_6 = std::bind(shorter_than, std::placeholders::_1, 6);
    // feature set => stl algorithm
    // parallel?
    for (auto name :    std::ranges::views::values(countries)
                      | std::ranges::views::filter(asian)            // better functional abstraction
                      | std::ranges::views::transform(to_name)       // 1-pass: memory efficient
                      | std::ranges::views::filter(shorter_than_6)){ // lazy evaluation
        cout << name << endl;
    }
}