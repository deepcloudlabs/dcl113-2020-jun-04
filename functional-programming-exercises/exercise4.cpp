#include "city.h"
#include "country.h"
#include "world-util.h"

#include <map>
#include <iostream>
#include <string>
#include <memory>
#include <parallel/algorithm>
#include <numeric>
#include <execution>

using namespace std;
using namespace world;

map<int, shared_ptr<city>> cities;
map<string, shared_ptr<country>> countries;
using mypair = pair<const string, shared_ptr<country>>;

int main(int argc, char *argv[]) {
    create_world();

    auto compareByGnp = [](shared_ptr<country> &left, shared_ptr<country> &right) {
        return left->gnp < right->gnp;
    };
    auto continentRichestCountryReducer = [&compareByGnp](
            map<string, shared_ptr<country>> &continentCountries, // reduce type
            pair<const string, shared_ptr<country>> &entry)
            -> std::map<string, shared_ptr<country>> & {
        auto ctry = entry.second;
        auto continent = ctry->continent;
        auto continentRichestCountry = continentCountries.find(continent);
        if (continentRichestCountry == continentCountries.end())
            continentCountries[continent] = ctry;
        else {
            auto richestCountry = continentRichestCountry->second;
            if (compareByGnp(richestCountry,ctry))
               continentCountries[continent] = ctry;
        }
        return continentCountries;
    };
    auto continentCountries = std::accumulate(
            countries.begin(),
            countries.end(),
            std::map<std::string, shared_ptr<country>>(), // reduce type
            continentRichestCountryReducer
    );
    auto print_continent_richest_country = [](const pair<string, shared_ptr<country>> &pair){
        std::cout << pair.first << ": " << pair.second->name << "\n" ;
    };

    std::for_each(continentCountries.cbegin(),continentCountries.cend(),print_continent_richest_country);

    return 0;
}