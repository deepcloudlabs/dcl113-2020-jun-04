#include <iostream>
#include <vector>
#include <numeric>

double i_average_score(const std::vector<int> &scores){
    int sum = 0;
    for (auto score: scores){
        sum += score;
    }
    return sum / (double)scores.size();
}

double d_average_score(const std::vector<int> &scores){
    // internal loop
    return std::accumulate(scores.cbegin(),scores.cend(),0, std::plus<int>()) / (double)scores.size();
}

int fun(int x, int y){
    return x * y;
}
// C++
// 1) (Global) Function
// 2) Function Object (Functor) -> Class -> operator()(?) -> Object -> Higher Order Function
      // builtin: plus<>, multiplies<>, ...
// 3) Lambda Expression

double d_average_score_with_multiplication(const std::vector<int> &scores){
    // internal loop
    return std::accumulate(scores.cbegin(),scores.cend(),
              1,
              fun) / (double)scores.size();
}

int main() {
    std::vector<int> scores{1,2,3,4,5,6,7,8,9,10};
    std::cout << i_average_score(scores) << std::endl;
    std::cout << d_average_score(scores) << std::endl;
    std::cout << d_average_score_with_multiplication(scores) << std::endl;
    return 0;
}
