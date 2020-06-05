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

// TODO: Find the min, the max, and the average population at each continent

map<int,shared_ptr<city>> cities;
map<string,shared_ptr<country>> countries;

template <class T>
struct statistics {
    T minimum;
    T maximum;
    double sum;
    int numberOfSamples;
    statistics() : sum(0), numberOfSamples(0) {}
    statistics(T value) : sum(value), numberOfSamples(1),minimum(value),maximum(value) {}
    double average() const {
        if (numberOfSamples==0) return 0.0;
        return sum/numberOfSamples;
    }
};

template <class T>
ostream& operator<<(ostream& out,const statistics<T>& stats){
    out << "statistics [ number of samples= " << stats.numberOfSamples
        << ", minimum=" << stats.minimum
        << ", maximum=" << stats.maximum
        << ", sum=" <<stats.sum
        << ", average=" << stats.average()
        << " ]";
    return out;
}

using statistics_int = statistics<int> ;
using statistics_int_ptr = shared_ptr<statistics_int> ;

int main(int argc, char* argv[]){
    create_world();

    auto statisticsReducer=  [](map<string,statistics_int_ptr>& continentStatistics, pair<const string,shared_ptr<country>>& entry) -> map<string,statistics_int_ptr>&  {
        auto country= entry.second;
        auto continent= country->continent;
        auto continentStatisticsIterator= continentStatistics.find(continent);
        if (continentStatisticsIterator==continentStatistics.end())
            continentStatistics[continent]= make_shared<statistics_int>(statistics_int(country->population));
        else {
            auto continentStat= continentStatisticsIterator->second;
            auto countryPopulation= country->population;
            if (continentStat->minimum > countryPopulation) continentStat->minimum= countryPopulation;
            if (continentStat->maximum < countryPopulation) continentStat->maximum= countryPopulation;
            continentStat->sum += countryPopulation;
            continentStat->numberOfSamples++;
        }
        return continentStatistics;
    };

    auto continentStatistics= accumulate(countries.begin(),countries.end(),map<string,statistics_int_ptr>(),statisticsReducer);

    for (auto& entry: continentStatistics){
        cout << entry.first << ": " << *(entry.second) << endl;
    }

    return 0;
}