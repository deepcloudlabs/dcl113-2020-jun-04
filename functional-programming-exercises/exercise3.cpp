#include "city.h"
#include "world-util.h"

#include <map>
#include <iostream>
#include <string>
#include <memory>
#include <functional>
#include <algorithm>

using namespace std;
using namespace world;

map<int, shared_ptr<city>> cities;
map<string, shared_ptr<country>> countries;

using mypair = pair<const string, shared_ptr<country>>;

int main(int argc, char *argv[]) {
    create_world();
    auto compareByGnp = [](mypair &left, mypair &right) {
        return left.second->gnp < right.second->gnp;
    };

    auto richestCountry = max_element(countries.begin(), countries.end(), compareByGnp);
    auto poorCountry = max_element(countries.begin(), countries.end(),
                                   bind(compareByGnp, placeholders::_2, placeholders::_1));
    cout << *(richestCountry->second) << endl;
    cout << *(poorCountry->second) << endl;
    return 0;
}