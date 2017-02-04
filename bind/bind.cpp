#include "bind.hpp"
#include <iostream>
#include <functional>

using std::cout;
using std::endl;

int make_arithmetics(int a, int b, int c, int d, int e) {
    a = b = c = 0;
    return a + b - c / d * e;
}

int make_arithmetics_link(int& a, int& b, int& c, int& d, int& e) {
    a = b = c = 0;
    return a + b - c / d * e;
}

int main() {
    auto my_bind_1 = bind(make_arithmetics, 1, 2, 3, 4, 5);
    auto st_bind_1 = std::bind(make_arithmetics, 1, 2, 3, 4, 5);
    
    cout << my_bind_1() << " " << st_bind_1() << endl;
    
    auto my_bind_2 = bind(make_arithmetics, 1, 2, 3, _1, _2);
    auto st_bind_2 = std::bind(make_arithmetics, 1, 2, 3, std::placeholders::_1, std::placeholders::_2);
    
    cout << my_bind_2(4, 5) << " " << st_bind_2(4, 5) << endl;
    
    auto my_bind_3 = bind(make_arithmetics, bind([](int a) {return -a;}, _1), 2, 3, _1, _2);
    auto st_bind_3 = std::bind(make_arithmetics, std::bind([](int a) {return -a;}, std::placeholders::_1), 2, 3, std::placeholders::_1, std::placeholders::_2);
    
    cout << my_bind_3(4, 5) << " " << st_bind_3(4, 5) << endl;
    
    auto my_bind_4 = bind(my_bind_2, 4, 5);
    auto st_bind_4 = std::bind(st_bind_2, 4, 5);
    
    cout << my_bind_4() << " " << st_bind_4() << endl;
    
    int a = 1, b = 2, c = 3;
    
    auto my_bind_5 = bind(make_arithmetics_link, a, b, c, 4, 5);
    auto st_bind_5 = std::bind(make_arithmetics_link, a, b, c, 4, 5);
    
    cout << my_bind_5() << " " << st_bind_5() << endl;
    
    cout << a << b << c << endl;
}

