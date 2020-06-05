#include "city.h"
#include "country.h"
#include "world-util.h"

#include <map>
#include <vector>
#include <iostream>
#include <string>
#include <memory>
#include <algorithm>
#include <numeric>
#include <ranges>

using namespace std;
using namespace world;

// TODO: Find the capital with highest population in the world

map<int,shared_ptr<city>> cities;
map<string,shared_ptr<country>> countries;

int main(int argc, char* argv[]){
    create_world();

    auto highPopulatedCapitalReducer=  [](shared_ptr<city>& highPopulatedCapital, pair<const string,shared_ptr<country>>& entry) -> shared_ptr<city>&  {
        auto capital= entry.second->capital;
        if(capital==nullptr) return highPopulatedCapital;
        auto population= capital->population;
        if (highPopulatedCapital==nullptr){
            highPopulatedCapital= capital;
        } else  if (highPopulatedCapital->population<population) {
            highPopulatedCapital= capital;
        }
        return highPopulatedCapital;
    };

    auto highPopulatedCapital = accumulate(countries.begin(),countries.end(),shared_ptr<city>(nullptr),highPopulatedCapitalReducer).get();

    cout << *highPopulatedCapital << endl;

    return 0;
}