/***************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                  *
 * Proposito:                      Proyecto Primer Parcial                             *
 * Autor:                          Kerlly Chiriboga,Heidy Mera                         *
 * Fecha de creacion:              06/12/2024                                          *
 * Fecha de modificacion:          06/12/2024                                          *
 * Materia:                        Estructura de datos                                 *
 * NRC :                           1978                                                *
 **************************************************************************************/

#include "Validaciones.h"
#include <iostream>
#include <string>
#include <conio.h>
#include <cstdlib>
#include <regex>


using namespace std;

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
            if (isalpha(c))
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

    // Validar el formato
    if (i != 10 || cad[4] != '-' || cad[7] != '-') // Verificar longitud y posiciones de los guiones
    {
        printf("\nFormato invalido. Intente de nuevo.\n");
        return ingresarFecha(msj); // Llamar recursivamente en caso de error
    }
    return std::string(cad); // Devolver la fecha válida
}

template <typename T>
std::string Validaciones<T>::ingresarPlaca(char *msj)
{
    char cad[20]; // Tamaño máximo para la placa
    char c;
    int i = 0;
    printf("%s", msj);

    while ((c = getch()) != 13) // Enter para finalizar
    {
        if (isalnum(c)) // Permitir solo letras y números
        {
            if (i < 19) // Limitar el tamaño
            {
                c = toupper(c); // Convertir a mayúscula
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

    // Convertir a std::string para validar
    std::string placa(cad);

    // Validar formato de placa ecuatoriana
    std::regex formatoEcuador(R"([A-Z]{3}\d{3,4}[A-Z]?)"); // AAA1234 o AAA123A
    if (!std::regex_match(placa, formatoEcuador))
    {
        printf("\nFormato de placa invalido. Intente de nuevo.\n");
        return ingresarPlaca(msj); // Llamar recursivamente en caso de error
    }

    // Validar los primeros tres caracteres (región o provincia)
    std::set<std::string> provinciasValidas = {
        "A", "B", "U", "G", "X", "W", "P", "Y", "T", "O", "M", "N", "S", "R", "H", "Z", "J", "K", "Q", "I", "E", "L", "V", "C"};
    std::string provincia = placa.substr(0, 1);
    if (provinciasValidas.find(provincia) == provinciasValidas.end())
    {
        printf("\nCodigo de provincia invalido. Intente de nuevo.\n");
        return ingresarPlaca(msj); // Llamar recursivamente en caso de error
    }

    return placa; // Devolver la placa válida
}

template <typename T>
std::string Validaciones<T>::ingresarCedula(char *msj)
{
    char cad[20]; // Tamaño máximo para la cédula
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

    // Validar longitud de la cédula (10 dígitos)
    if (cedula.length() != 10) {
        printf("\nCedula invalida. Intente de nuevo.\n");
        return ingresarCedula(msj); // Recursividad en caso de error
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

    // Validar formato del correo usando una expresión regular
    std::regex formatoCorreo(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");
    if (!std::regex_match(correo, formatoCorreo)) {
        printf("\nCorreo electronico invalido. Intente de nuevo.\n");
        return ingresarCorreo(msj); // Recursividad en caso de error
    }

    return correo; // Devolver el correo válido
}

template<typename T>
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