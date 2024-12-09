#ifndef REGISTRO_H
#define REGISTRO_H

#include "Auto.h"
#include "Propietario.h"

class Registro {
public:
    Auto autoPermitido;
    Propietario propietario;

    Registro(const Auto& autoPermitido, const Propietario& propietario);
};

#endif // REGISTRO_H
