#ifndef AUTO_H
#define AUTO_H

#include <string>
using namespace std;

class Auto {
public:
    string placa;
    string marca;
    string color;

    Auto(const string& placa, const string& marca, const string& color);
};

#endif // AUTO_H
