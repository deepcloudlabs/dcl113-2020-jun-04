#include "city.h"
#include "country.h"
#include "world-util.h"

#include <set>
#include <map>
#include <iostream>
#include <string>
#include <memory>
#include <parallel/algorithm>
#include <numeric>

using namespace std;
using namespace world;

map<int, shared_ptr<world::city>> cities;
map<std::string, shared_ptr<world::country>> countries;

int main(int argc, char *argv[]) {
    create_world();

    auto continentCountriesReducer = [](
            std::map<std::string, int> &countinentCountries, // reduce type
            pair<const string, shared_ptr<country>> &entry)
            -> std::map<std::string, int> & {
        auto ctry = entry.second;
        auto continent = ctry->continent;
        auto end = countinentCountries.end();
        auto iterator = countinentCountries.emplace_hint(end, continent, 0);
        (iterator->second)++;
        return countinentCountries;
    };
    auto continentCountries = std::accumulate(
            countries.begin(),
            countries.end(),
            std::map<std::string, int>(), // reduce type
            continentCountriesReducer
    );
    auto print_continent_countries = [](const pair<string, int> &pair){
        std::cout << pair.first << ": " << pair.second << "\n" ;
    };

    std::for_each(continentCountries.cbegin(),continentCountries.cend(),print_continent_countries);
    return 0;
}