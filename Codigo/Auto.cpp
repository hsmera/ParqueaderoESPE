#include "Auto.h"

Auto::Auto() : placa(""), marca(""), color("") {}

Auto::Auto(string placa, string marca, string color)
    : placa(placa), marca(marca), color(color) {}
string Auto::getPlaca() const { return placa; }
string Auto::getMarca() const { return marca; }
string Auto::getColor() const { return color; }

void Auto::setPlaca(const string& placa) { this->placa = placa; }
void Auto::setMarca(const string& marca) { this->marca = marca; }
void Auto::setColor(const string& color) { this->color = color; }

string Auto::toString() const {
    return placa + "," + marca + "," + color;
}
