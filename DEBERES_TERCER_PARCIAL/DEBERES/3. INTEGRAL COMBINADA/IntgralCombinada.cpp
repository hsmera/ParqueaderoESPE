//Dadasdos funciones f(x)yg(x)quese intersectanunasólavezenel intervalo[a,b], escribaunmétodoque
//entregue una buena aproximación del área indicada en el siguiente ejemplo:
//Invocacióndelmétodo: area(f, g, a, b, n) enquenesel Nº total depuntosenquesedividiráel intervalo[a,b] 
//Nótesequeenelpuntomsecumplequef(x)-g(x) = 0
//Porsupuesto,enotrosejemplos,g(x)podríaestarporencimadef(x)antesdelpuntodeintersección

#include <iostream>
#include <cmath>

using namespace std;

class F {
public:
    virtual double valor(double x) const = 0; // Método virtual puro para definir funciones
};

// Método para calcular la raíz de f - g
double raiz(F* f, F* g, double a, double b, double eps) {
    double x = (a + b) / 2;
    if (b - a <= eps)
        return x;
    if ((f->valor(a) - g->valor(a)) * (f->valor(x) - g->valor(x)) > 0)
        return raiz(f, g, x, b, eps);
    else
        return raiz(f, g, a, x, eps);
}

// Método para calcular el signo de un número
int signo(double x) {
    return (x < 0) ? -1 : 1;
}

// Método para calcular la integral numérica
double integral(F* f, double a, double b, int n) {
    double s = 0, x = a, ancho = (b - a) / n;
    for (int i = 1; i <= n; ++i) {
        s += f->valor(x);
        x += ancho;
    }
    return s * ancho;
}

// Método para calcular el área combinada
double area(F* f, F* g, double a, double b, int n, double eps) {
    // Calcular valor de m (raíz de f - g)
    double m = raiz(f, g, a, b, eps);

    // Asegurar que f > g en [a, m]
    if (f->valor(a) < g->valor(a)) {
        F* aux = f;
        f = g;
        g = aux;
    }

    // Calcular área en [a, m]
    double factor = (m - a) / (b - a);
    int n1 = static_cast<int>(n * factor);
    double area1 = integral(f, a, m, n1);

    // Calcular área en [m, b]
    int n2 = n - n1;
    double area2 = integral(g, m, b, n2);

    // Devolver área total
    return area1 + area2;
}

// Alternativa: calcular el área combinada directamente
double area_alternativa(F* f, F* g, double a, double b, int n) {
    double s = 0, x = a, ancho = (b - a) / n;
    for (int i = 1; i <= n; ++i) {
        s += max(f->valor(x), g->valor(x));
        x += ancho;
    }
    return s * ancho;
}
