#include "city.h"
#include "country.h"
#include "world-util.h"

#include <map>
#include <iostream>
#include <string>
#include <memory>
#include <algorithm>
#include <numeric>

using namespace std;
using namespace world;

// TODO: Find cities with the min and the max population in each country

map<int,shared_ptr<city>> cities;
map<string,shared_ptr<country>> countries;

template <class E,class T>
struct statistics {
    E min_element;
    E max_element;
    T min;
    T max;
    int numberOfSamples;
    statistics() : numberOfSamples(0) {}
};

ostream& operator<<(ostream& out,const statistics<shared_ptr<city>,int>& stats){
    if (stats.min_element.get()==nullptr) {
        out << "No body lives in this country!" ;
    }else{
        out << "statistics [ "
            << stats.min_element->name
            << " ( " << stats.min << " )"
            << ",  " << stats.max_element->name
            << " ( " << stats.max << " )"
            << " ]";
    }
    return out;
}

int main(int argc, char* argv[]){
    create_world();

    for (auto& entry: countries){
        auto this_country= entry.second;
        auto country_cities= this_country->cities;
        auto statisticsReducer=  [](statistics<shared_ptr<city>,int>& cityPopulationStatistics, shared_ptr<city>& a_city) -> statistics<shared_ptr<city>,int>&  {
            auto cityPopulation= a_city->population;
            if (cityPopulationStatistics.numberOfSamples==0){
                cityPopulationStatistics.min= cityPopulation;
                cityPopulationStatistics.min_element= a_city;
                cityPopulationStatistics.max= cityPopulation;
                cityPopulationStatistics.max_element= a_city;
            }
            cityPopulationStatistics.numberOfSamples++;
            if (cityPopulationStatistics.min>cityPopulation){
                cityPopulationStatistics.min= cityPopulation;
                cityPopulationStatistics.min_element= a_city;
            } else
            if (cityPopulationStatistics.max<cityPopulation){
                cityPopulationStatistics.max= cityPopulation;
                cityPopulationStatistics.max_element= a_city;
            }
            return cityPopulationStatistics;
        };
        auto populationStatistics= accumulate(country_cities.begin(),country_cities.end(),statistics<shared_ptr<city>,int>(),statisticsReducer);
        cout << this_country->name << "'s statistics:" << endl;
        cout << populationStatistics << endl;
    }

    return 0;
}