
#include "Enfermedad.h"

Enfermedad::Enfermedad()
{
    this->enfermedad="";
    this->secuencia="";
}

Enfermedad::Enfermedad(string enfermedad, string secuencia)
{
    this->enfermedad=enfermedad;
    this->secuencia=secuencia;
}

string Enfermedad::getEnfermedad()
{
    return this->enfermedad;
}

string Enfermedad::getSecuencia()
{
    return this->secuencia;
}
