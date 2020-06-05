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

    // TODO: Find the number of countries in each continent

    return 0;
}