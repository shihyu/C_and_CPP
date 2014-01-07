#include <iostream>

class Temp {
private:
    Temp() {}
    ~Temp() {}
    friend class Final;
};

class Final : virtual public Temp {
public:
    Final() {
        std::cout << "Final" << std::endl;
    }

    void fun() {
        std::cout << "In base" << std::endl;
    }
};

class Derived : public Final {

};

int main() {
    Final obj;
    obj.fun();

    // Derived obj;
    //obj.fun();
}
