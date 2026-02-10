#include <iostream>

auto sayHello=[](){
    std::cout<<"Hello";
};

int main(){

    int x=10,y=20;

    auto f=[&](){
        x+=1;
        y+=2;
    };

    f();

    auto d = [=]() {
        std::cout << x << " " << y << "\n";
        // x++; ❌ cannot modify (const copies)
    };

    d();

    int x = 10;

    auto k = [x]() {
        std::cout << x << "\n"; // prints 10
    };

    x = 20;
    k(); // still prints 10

    sayHello();
    return 0;
}