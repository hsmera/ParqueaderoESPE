//a) Escriba unmétodo que entregue una aproximación (con precisión epsilon) del valor de x que
//correspondealúnicomínimoquetomalafuncióncontinuafenel intervalo[a,b]
//Notas: Encabezamiento:doublexmin(doublea,doubleb,doubleepsilon, Funcionf). Funcionesuna
//claseointerfacequecontieneun métododeencabezamiento:
//public double evaluar(double x) 
//Utiliceunalgoritmodebúsquedabinariademodoqueencadaiteración
//1. encuentreelpuntomedio(p)del intervalo
//2. evalúelafunción enp+epsilon/2ypepsilon/2
//3. descarte la primera o segunda mitad del intervalo de acuerdo a si la función
//aumenta/disminuyeenelentornocercanodep
//b) Utiliceelmétodo enunprogramaquecalculeel ángulo (con3decimalesdeprecisión) enque la
//funciónsenotomaelmenorvalorenel intervalo [π,2π]

#include <iostream>
#include <cmath>

using namespace std;

// Definir una interfaz (clase abstracta) para funciones matemáticas
class Funcion {
public:
    virtual double evaluar(double x) const = 0; // Método virtual puro
    virtual ~Funcion() {} // Destructor virtual
};

// Implementación de la función Seno
class Seno : public Funcion {
public:
    double evaluar(double x) const override {
        return sin(x);
    }
};

// Método para obtener el mínimo absoluto en [a, b]
double minx(double a, double b, double eps, const Funcion* f) {
    double p = (a + b) / 2;
    if (b - a < eps) 
        return p;
    
    double y1 = f->evaluar(p - eps);
    double y2 = f->evaluar(p + eps);

    if (y1 > y2)
        return minx(p, b, eps, f);
    else
        return minx(a, p, eps, f);
}

int main() {
    Seno seno;
    double minimo = minx(M_PI, 2 * M_PI, 0.001, &seno);
    cout << "Mínimo de sin(x) en [π, 2π]: " << minimo << endl;
    return 0;
}
