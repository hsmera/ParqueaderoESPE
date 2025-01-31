/***************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                  *
 * Proposito:                      Proyecto Primer Parcial                             *
 * Autor:                          Kerlly Chiriboga,Heidy Mera                         *
 * Fecha de creacion:              06/12/2024                                          *
 * Fecha de modificacion:          06/12/2024                                          *
 * Materia:                        Estructura de datos                                 *
 * NRC :                           1978                                                *
 **************************************************************************************/

#ifndef __Validaciones_Validaciones_h
#define __Validaciones_Validaciones_h

#include <iostream>
#include <string>
#include <conio.h>
#include <cstdlib>
#include <regex>
#include <set>
#include <limits>
#include <ctime>    // Para obtener la fecha actual // Para usar getch()
#include <string> 
#include <cctype>    // Para isalpha() y isdigit()
#include <set>       // Para manejar la lista de provincias válidas

using namespace std;

template <typename T>
class Validaciones
{
public:
    Validaciones();
    T ingresar(char *msj, char *tipo);
    std::string ingresarFecha(char *msj);
    std::string ingresarPlaca(char *msj);
    std::string ingresarCedula(char *msj);
    std::string ingresarCorreo(char *msj);
    std::string ingresarEspacioId(const char *msj);
    static string ingresarHora(const string& mensaje);
    std::string ingresarPrefijo(const char *msj);
    bool validarCedulaEcuatoriana(const std::string& cedula);


private:
    T numero;
};

template <typename T>
Validaciones<T>::Validaciones()
{
}

template <typename T>
T Validaciones<T>::ingresar(char *msj, char *tipo)
{
    char cad[100];
    char c;
    int i = 0;
    T valor;
    printf("%s", msj);
    while ((c = getch()) != 13)
    {
        if (tipo == "entero")
        {
            if (c >= '0' && c <= '9')
            {
                printf("%c", c);
                cad[i++] = c;
            }
            else if (c == 8)
            {
                if (i > 0)
                {
                    printf("\b \b");
                    i--;
                }
            }
        }
        else if (tipo == "flotante" || tipo == "double")
        {
            if (c >= '0' && c <= '9')
            {
                printf("%c", c);
                cad[i++] = c;
            }
            else if (c == 8)
            {
                if (i > 0)
                {
                    printf("\b \b");
                    i--;
                }
            }
            else if (c == 46)
            {
                bool aux = false;
                for (int j = 0; cad[j] != '\0'; j++)
                {
                    if (cad[j] == 46)
                    {
                        aux = true;
                        break;
                    }
                }
                if (aux == false)
                {
                    printf("%c", c);
                    cad[i++] = c;
                }
            }
        }
        else if (tipo == "string")
        {
            if (isalpha(c) || c == ' ')
            {
                printf("%c", c);
                cad[i++] = c;
            }
            else if (c == 8)
            {
                if (i > 0)
                {
                    printf("\b \b");
                    i--;
                }
            }
        }
        else if (tipo == "char")
        {
            if (isalpha(c))
            {
                printf("%c", c);
                valor = c;
                break;
            }
            else if (c == 8)
            {
                if (c >= 'a' && c <= 'z')
                {
                    printf("\b \b");
                }
            }
        }
    }
    cad[i] = '\0';
    if (tipo == "entero")
    {
        int entero;
        entero = atoi(cad);
        return valor = entero;
    }
    else if (tipo == "flotante")
    {
        float flotante;
        for (int j = 0; cad[j] != '\0'; j++)
        {
            flotante = atof(cad);
        }
        return valor = flotante;
    }
    else if (tipo == "double")
    {
        double doble;
        for (int j = 0; cad[j] != '\0'; j++)
        {
            doble = atof(cad);
        }
        return valor = doble;
    }
    else if (tipo == "char")
    {
        return valor;
    }
    else if (tipo == "string")
    {
        for (int j = 0; cad[j] != '\0'; j++)
        {
            valor = valor + cad[j];
        }
        return valor;
    }
    return valor; 
}

template <typename T>
std::string Validaciones<T>::ingresarPlaca(char *msj)
{
    char cad[8]; // Placa ecuatoriana debe ser EXACTAMENTE 7 caracteres (AAA1234)
    char c;
    int i = 0;

    // Provincias válidas en Ecuador (primera letra de la placa)
    std::set<char> provinciasValidas = {'A', 'B', 'U', 'G', 'X', 'W', 'P', 'Y', 'T', 'O',
                                         'M', 'N', 'S', 'R', 'H', 'Z', 'J', 'K', 'Q', 'I', 'E', 'L', 'V', 'C'};

    printf("%s", msj);

    while (i < 7) // Solo permitimos 7 caracteres
    {
        c = getch();

        if (i < 3) // Primeros 3 caracteres deben ser letras
        {
            if (isalpha(c))
            {
                c = toupper(c); // Convertir a mayúscula
                printf("%c", c);
                cad[i++] = c;
            }
        }
        else if (i >= 3 && i < 7) // Últimos 4 caracteres deben ser números
        {
            if (isdigit(c))
            {
                printf("%c", c);
                cad[i++] = c;
            }
        }
        else if (c == 8 && i > 0) // Backspace para borrar
        {
            printf("\b \b");
            i--;
        }
    }

    cad[i] = '\0'; // Finalizar la cadena
    std::string placa(cad);

    // **Validación final antes de devolver**
    if (placa.length() != 7) // Asegurar que sean exactamente 7 caracteres
    {
        printf("\nError: La placa debe tener exactamente 7 caracteres.\n");
        return ingresarPlaca(msj); // Reintentar si hay error
    }

    // **Validar la provincia (primera letra)**
    if (provinciasValidas.find(placa[0]) == provinciasValidas.end())
    {
        printf("\nError: La primera letra de la placa no corresponde a una provincia de Ecuador.\n");
        return ingresarPlaca(msj); // Reintentar si hay error
    }

    printf("\nPlaca ingresada correctamente.\n");
    return placa;
}

template <typename T>
std::string Validaciones<T>::ingresarFecha(char *msj)
{
    char cad[11]; // Fecha en formato YYYY-MM-DD (10 caracteres + '\0')
    char c;
    int i = 0;
    char ultimoCaract = 0; // Para guardar el último carácter ingresado

    printf("%s", msj);

    while ((c = getch()) != 13) // Enter para finalizar
    {
        if ((c >= '0' && c <= '9') || c == '-') // Permitir números y guiones
        {
            if (c == '-' && ultimoCaract == '-') // Evitar guiones consecutivos
            {
                continue; // Ignorar el guion y no agregarlo
            }

            if (i < 10) // Limitar a 10 caracteres
            {
                printf("%c", c);
                cad[i++] = c;
                ultimoCaract = c; // Actualizar el último carácter ingresado
            }
        }
        else if (c == 8) // Backspace para borrar
        {
            if (i > 0)
            {
                printf("\b \b");
                i--;
                ultimoCaract = (i > 0) ? cad[i - 1] : 0; // Actualizar el último carácter al borrar
            }
        }
    }
    cad[i] = '\0'; // Terminar la cadena

    //Validar el formato correcto**
    if (i != 10 || cad[4] != '-' || cad[7] != '-') // Verificar longitud y posiciones de los guiones
    {
        printf("\nFormato invalido. Intente de nuevo.\n");
        return ingresarFecha(msj); // Llamar recursivamente en caso de error
    }

    //  Extraer Año, Mes y Día**
    int anio, mes, dia;
    sscanf(cad, "%d-%d-%d", &anio, &mes, &dia); // Extraer los valores de la fecha

    //Validar el año (Debe estar entre 2020 y el año actual)**
    time_t t = time(nullptr);
    struct tm *now = localtime(&t);
    int anioActual = now->tm_year + 1900; // Año actual

    if (anio < 2020 || anio > anioActual)
    {
        printf("\nFecha invalida. El anio debe estar entre 2020 y %d.\n", anioActual);
        return ingresarFecha(msj);
    }

    // Validar el mes (1-12)**
    if (mes < 1 || mes > 12)
    {
        printf("\nFecha invalida. El mes debe estar entre 1 y 12.\n");
        return ingresarFecha(msj);
    }

    // Validar el día según el mes**
    int diasPorMes[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; // Meses [1-12]
    
    // Verificar si el año es bisiesto (para ajustar febrero)
    if ((anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0))
    {
        diasPorMes[2] = 29; // Año bisiesto, febrero tiene 29 días
    }

    if (dia < 1 || dia > diasPorMes[mes])
    {
        printf("\nFecha invalida. El dia ingresado no es valido para el mes especificado.\n");
        return ingresarFecha(msj);
    }

    // **Si todas las validaciones pasan, retornamos la fecha válida**
    return std::string(cad);
}

template <typename T>
bool Validaciones<T>::validarCedulaEcuatoriana(const std::string& cedula) {
    if (cedula.length() != 10) return false; // Verificar la longitud

    // Verificar que todos los caracteres sean numéricos
    for (char c : cedula) {
        if (!isdigit(c)) return false;
    }

    int provincia = std::stoi(cedula.substr(0, 2)); // Obtener provincia
    int tercerDigito = cedula[2] - '0'; // Obtener tercer dígito

    if (provincia < 1 || provincia > 24) return false; // Provincia válida
    if (tercerDigito < 0 || tercerDigito > 6) return false; // Tercer dígito válido

    // Validar dígito verificador con el algoritmo oficial
    int coeficientes[9] = {2, 1, 2, 1, 2, 1, 2, 1, 2};
    int suma = 0;

    for (int i = 0; i < 9; i++) {
        int valor = (cedula[i] - '0') * coeficientes[i];
        if (valor >= 10) valor -= 9;
        suma += valor;
    }

    // Cálculo del dígito verificador
    int digitoVerificadorCalculado = (10 - (suma % 10)) % 10;
    if (digitoVerificadorCalculado == 10) digitoVerificadorCalculado = 0; // Si el dígito es 10, se toma como 0

    int digitoVerificadorCedula = cedula[9] - '0'; // Convertir décimo dígito a entero

    return (digitoVerificadorCalculado == digitoVerificadorCedula); // Comparar
}

template <typename T>
std::string Validaciones<T>::ingresarCedula(char *msj)
{
    char cad[11]; // 10 dígitos + '\0'
    char c;
    int i = 0;
    printf("%s", msj);

    while ((c = getch()) != 13) // Enter para finalizar
    {
        if (isdigit(c)) // Permitir solo números
        {
            if (i < 10) // Limitar el tamaño a 10 dígitos
            {
                printf("%c", c);
                cad[i++] = c;
            }
        }
        else if (c == 8) // Backspace para borrar
        {
            if (i > 0)
            {
                printf("\b \b");
                i--;
            }
        }
    }
    cad[i] = '\0'; // Terminar la cadena

    std::string cedula(cad);

    // Validar la cédula usando el algoritmo de verificación
    if (!validarCedulaEcuatoriana(cedula)) {
        printf("\nCédula invalida. Intente de nuevo.\n");
        return ingresarCedula(msj); // Pedir la cédula nuevamente
    }

    return cedula; // Devolver la cédula válida
}

template <typename T>
std::string Validaciones<T>::ingresarCorreo(char *msj)
{
    char cad[50]; // Tamaño máximo para el correo
    char c;
    int i = 0;
    printf("%s", msj);

    while ((c = getch()) != 13) // Enter para finalizar
    {
        if (isalnum(c) || c == '@' || c == '.' || c == '_') // Permitir letras, números, @, . y _
        {
            if (i < 49) // Limitar el tamaño
            {
                c = tolower(c); // Convertir a minúsculas
                printf("%c", c);
                cad[i++] = c;
            }
        }
        else if (c == 8) // Backspace para borrar
        {
            if (i > 0)
            {
                printf("\b \b");
                i--;
            }
        }
    }
    cad[i] = '\0'; // Terminar la cadena

    std::string correo(cad);

    // **Validar que antes del '@' solo haya letras o números, sin puntos al inicio**
    size_t posAt = correo.find('@');
    if (posAt == std::string::npos || posAt == 0) {
        printf("\nCorreo invalido: Debe contener un '@' y no puede empezar con el.\n");
        return ingresarCorreo(msj);
    }

    // **Validar que haya exactamente un '@'**
    if (correo.find('@', posAt + 1) != std::string::npos) {
        printf("\nCorreo invalido: Solo debe haber un '@'.\n");
        return ingresarCorreo(msj);
    }

    std::string usuario = correo.substr(0, posAt); // Parte antes del '@'
    std::string dominio = correo.substr(posAt + 1); // Parte después del '@'

    // **Validar que antes del '@' solo haya letras, números, puntos o guiones bajos, sin comenzar con '.'**
    if (usuario.empty() || usuario[0] == '.' || usuario.find("..") != std::string::npos) {
        printf("\nCorreo invalido: La parte antes del '@' no puede empezar con '.' ni contener '..'.\n");
        return ingresarCorreo(msj);
    }

    // **Validar que el dominio contenga al menos un punto (.)**
    size_t posDot = dominio.find('.');
    if (posDot == std::string::npos || posDot == 0 || posDot == dominio.length() - 1) {
        printf("\nCorreo invalido: El dominio debe contener al menos un '.' y no puede empezar ni terminar con el.\n");
        return ingresarCorreo(msj);
    }

    // **Validar que el dominio no tenga '..' consecutivos**
    if (dominio.find("..") != std::string::npos) {
        printf("\nCorreo invalido: El dominio no puede contener '..'.\n");
        return ingresarCorreo(msj);
    }

    // **Validar el formato completo con una expresión regular**
    std::regex formatoCorreo(R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)");
    if (!std::regex_match(correo, formatoCorreo)) {
        printf("\nCorreo invalido. Intente de nuevo.\n");
        return ingresarCorreo(msj);
    }

    printf("\nCorreo ingresado correctamente.\n");
    return correo; // Devolver el correo válido
}


template <typename T>
std::string Validaciones<T>::ingresarEspacioId(const char* msj) {
    std::string espacioId = "";
    char c;
    std::cout << msj;

    while (true) {
        c = getch(); // Capturar carácter

        if (isdigit(c) && espacioId.length() < 2) {
            // Solo permitir números y limitar a 2 caracteres
            espacioId += c;
            std::cout << c; // Mostrar el carácter ingresado
        } else if (c == 8 && !espacioId.empty()) { // Retroceso (Backspace)
            std::cout << "\b \b"; // Borrar el último carácter visualmente
            espacioId.pop_back();
        } else if (c == 13 && espacioId.length() == 2) { // Enter y longitud válida
            std::cout << std::endl;
            break;
        }
    }

    return espacioId;
}

// Definición de la función ingresarHora en el mismo archivo
template <typename T>
string Validaciones<T>::ingresarHora(const string& mensaje) {
    string hora;
    int countDosPuntos = 0;

    while (true) {
        cout << mensaje;
        hora.clear();
        countDosPuntos = 0;
        
        char c;
        while (hora.length() < 8) { // Máximo 8 caracteres
            c = getch(); // Capturar carácter

            if (isdigit(c)) { 
                hora += c;
                cout << c;
            } else if (c == ':' && countDosPuntos < 2) { 
                hora += c;
                cout << c;
                countDosPuntos++;
            } else if (c == 8 && !hora.empty()) { // Retroceso (Backspace)
                if (hora.back() == ':') {
                    countDosPuntos--;
                }
                cout << "\b \b";
                hora.pop_back();
            } else if (c == 13) { // Enter para confirmar
                break;
            }
        }

        if (hora.length() == 8 && countDosPuntos == 2) {
            regex formatoHora("^([01]?[0-9]|2[0-3]):([0-5][0-9]):([0-5][0-9])$");
            if (regex_match(hora, formatoHora)) {
                cout << endl;
                break;
            }
        }

        cout << "\nHora invalida. Ingrese en formato HH:MM:SS.\n";
    }

    return hora;
}

template <typename T>
string Validaciones<T>::ingresarPrefijo(const char* msj) {
    char cad[4]; // Solo permitiremos hasta 3 letras + '\0'
    char c;
    int i = 0;

    // Lista de las primeras letras válidas para provincias de Ecuador
    const std::string provincias = "AEBPYLJOTUSMCFRHGDIXKVZ";

    printf("%s", msj);

    while ((c = getch()) != 13) { // Enter para finalizar
        if (isalpha(c)) { // Solo permitir letras
            if (i < 3) { // Limitar a un máximo de 3 caracteres
                c = toupper(c); // Convertir a mayúsculas
                printf("%c", c);
                cad[i++] = c;
            }
        } else if (c == 8) { // Backspace para borrar
            if (i > 0) {
                printf("\b \b");
                i--;
            }
        }
    }

    cad[i] = '\0'; // Terminar la cadena

    // Validar que la primera letra sea una provincia válida
    if (i == 0 || provincias.find(cad[0]) == std::string::npos) {
        printf("\nEl prefijo no puede estar vacio y debe iniciar con una letra valida de provincia. Intente de nuevo.\n");
        return ingresarPrefijo(msj); // Llamar recursivamente en caso de error
    }

    // Validar que no exceda 3 caracteres
    if (i > 3 || i < 3) {
        printf("\nEl prefijo debe tener un minimo de 3 letras. Intente de nuevo.\n");
        return ingresarPrefijo(msj); // Llamar recursivamente en caso de error
    }

    return std::string(cad); // Devolver el prefijo válido
}

#endif
