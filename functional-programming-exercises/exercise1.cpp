#include "city.h"
#include "country.h" 
#include "world-util.h" 

#include <set>
#include <map>
#include <iostream>
#include <string>
#include <memory>
#include <algorithm>
#include <numeric>

using namespace std;
using namespace world;

map<int,shared_ptr<city>> cities;
map<string,shared_ptr<country>> countries;

int main(int argc, char* argv[]){
	create_world();

    auto continentReducer =  [ ](
            set<std::string>& conts, // reduce type
            pair<const string, shared_ptr<country>> &entry)
            -> set<string>&  {
        auto ctry = entry.second ;
        auto continent = ctry->continent;
        conts.insert(continent);
        return conts;
    };
    auto continents = std::accumulate(
            countries.begin(),
            countries.end(),
            std::set<std::string>(), // reduce type
            continentReducer
    );
	auto print_continent = [](const std::string& cont){
	    std::cout << cont << "," ;
	};
	std::for_each(continents.cbegin(),continents.cend(),print_continent);

    auto surface_area_reducer =  [ ](
            double area, // reduce type
            pair<const string, shared_ptr<country>> &entry)
            -> double  {
        return area + entry.second->surface_area;
    };
	auto totalSurfaceArea = accumulate(
            countries.begin(),
            countries.end(),
            0.0,
            surface_area_reducer
	        );
	cout << "\n Total surface area: " << totalSurfaceArea << "\n" ;
	auto values = countries.
	return 0;
}