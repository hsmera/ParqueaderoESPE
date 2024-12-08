#ifndef AUTO_H
#define AUTO_H

#include <string>
using namespace std;

class Auto {
private:
    string placa;
    string marca;
    string color;

public:
    Auto();
    Auto(string placa, string marca, string color);

    string getPlaca() const;
    string getMarca() const;
    string getColor() const;
    void setPlaca(const string& placa);
    void setMarca(const string& marca);
    void setColor(const string& color);

    string toString() const; 
};

#endif
