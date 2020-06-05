#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <numbers>
#include <numeric>
#include <fstream>

#include "person.h"

double degree2radian(double deg) {
    return deg * 3.14 / 180;
}

void my_print_person(const person_t &per, std::ostream &out, person_t::output_format_t format) {
    std::cout << "my_print_person is running..." << std::endl;
    if (format == person_t::full_name)
        out << per.surname() << ", " << per.name() << ", " << per.age() << "\n";
    else
        out << per.name() << ", " << per.age() << "\n";
}

template<class T, class OrderBy, class Compare>
auto getOrder(OrderBy orderBy, Compare compareBy) {
    return [orderBy,compareBy](const T& first,const T& second) {
        return compareBy(orderBy(first),orderBy(second));
    };
}

int main() {
    std::vector<double> degrees{0, 30, 45, 60, 180};
    std::vector<double> radians(degrees.size());
    // binary -> unary
    auto deg2rad = std::bind(std::multiplies<double>(), std::placeholders::_1, 3.14 / 180);
    std::cout << deg2rad(125) << std::endl;
    auto _125deg2rad = std::bind(std::multiplies<double>(), 125, 3.14 / 180);

    // degrees (double) --> radian (double)
    std::transform(degrees.cbegin(), degrees.cend(), radians.begin(), deg2rad);
    std::for_each(radians.begin(), radians.end(), [](double x) { std::cout << x << std::endl; });

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
    auto print_person = [](const person_t &per) {
        std::cout << per.surname() << ", " << per.name() << ", " << per.age() << std::endl;
    };
    std::for_each(people.cbegin(), people.cend(), print_person);
    auto orderByAgeDesc = [](const person_t &first, const person_t &second) {
        return first.age() > second.age();
    };
    /*
    auto orderByAgeAsc = [](const person_t &first, const person_t &second) {
        return first.age() < second.age();
    };
     */
    auto orderByAgeAsc = std::bind(orderByAgeDesc, std::placeholders::_2, std::placeholders::_1);
    auto partial_print_person = std::bind(my_print_person,
                                          std::placeholders::_1, std::ref(std::cout), person_t::name_only);
    std::ofstream file("people.txt");
    auto partial_print_full_person_to_file = std::bind(my_print_person,
                                                       std::placeholders::_1, std::ref(file), person_t::full_name);

    std::sort(people.begin(), people.end(), orderByAgeDesc);
    std::cout << "After sorting... order by age desc" << std::endl;
    std::for_each(people.cbegin(), people.cend(), partial_print_full_person_to_file);

    std::cout << "After sorting... order by age asc" << std::endl;
    std::sort(people.begin(), people.end(), orderByAgeAsc);
    std::for_each(people.cbegin(), people.cend(), print_person);

    std::vector<int> numbers{42, 15, 8, 16, 4, 23};
    std::sort(numbers.begin(), numbers.end(),
              std::bind(std::greater<int>(), std::placeholders::_2, std::placeholders::_1));
    std::for_each(numbers.cbegin(), numbers.cend(), [](int x) { std::cout << x << " "; });
    std::cout << std::endl;
    auto byLastName = [](const person_t& per)  { return per.surname();};
    auto byAge = [](const person_t& per)  { return per.age();};
    std::sort(people.begin(), people.end(),
            getOrder<person_t>(byLastName,std::greater<std::string>()));
    std::for_each(people.cbegin(), people.cend(), print_person);
    std::sort(people.begin(), people.end(),
            getOrder<person_t>(byAge,std::less<int>()));
    std::for_each(people.cbegin(), people.cend(), print_person);
    return 0;
}
