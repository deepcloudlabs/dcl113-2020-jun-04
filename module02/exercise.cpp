#include <vector>
#include <iostream>
#include <parallel/algorithm>
#include <execution>
#include "person.h"

bool
is_female(const person_t &person) {
    return person.gender() == person_t::female;
}

void
print_person(person_t &person) {
    person.print(std::cout, person_t::name_only);
}
auto counter = 0;
std::string
person_to_name_mapper(const person_t &person) {
    counter++; // side effect
    return person.name();
}

void
print_names(std::string &name) {
    std::cout << name << std::endl;
}

// global data
std::vector<std::string> female_names2;

void
transform_person(const person_t &person) {
    female_names2.push_back(person.name());
}

int main(int argc, char *argv[]) {
    std::vector<person_t> people{
            {"Jack",    "Shephard",   person_t::male,   46},
            {"Kate",    "Austen",     person_t::female, 37},
            {"Ben",     "Linus",      person_t::male,   55},
            {"Juliet",  "Burke",      person_t::female, 41},
            {"James",   "Sawyer",     person_t::male,   39},
            {"Claire ", "Littleton",  person_t::female, 29},
            {"John",    "Locke",      person_t::male,   58},
            {"Shannon", "Rutherford", person_t::female, 26},
            {"Sun",     "Kwon",       person_t::female, 36}
    };
    std::vector<person_t> females;
    std::copy_if(people.cbegin(), people.cend(), std::back_inserter(females), is_female);
    std::for_each(females.begin(), females.end(), print_person);
    std::vector<std::string> female_names(females.size());
    // internal loop
    std::transform(std::execution::par, females.cbegin(), females.cend(), female_names.begin(), person_to_name_mapper);
    std::for_each(females.begin(), females.end(), transform_person);
    std::for_each(std::execution::par, female_names.begin(), female_names.end(), print_names);
    std::for_each(female_names2.begin(), female_names2.end(), print_names);
    int x, y, z = 2;
    double a = 0.1, b = 0.2, c = 0.3;
    auto is_equal = ((a + b) + c) == (a + (b + c));
    std::cout << is_equal << std::endl; // false
}