
#include "Paciente.h"

Paciente::Paciente()
{
    this->id="";
    this->nombre="";
    this->telefono="";
    this->correo="";
    this->secuencia="";
    this->enfermedades=vector<Enfermedad>();
}

Paciente::Paciente(string id, string nombre, string telefono, string correo, string secuencia)
{
    this->id=id;
    this->nombre=nombre;
    this->telefono=telefono;
    this->correo=correo;
    this->secuencia=secuencia;
    this->enfermedades=vector<Enfermedad>();
}

string Paciente::getId()
{
    return this->id;
}

string Paciente::getTelefono()
{
    return this->telefono;
}

string Paciente::getCorreo()
{
    return this->correo;
}

string Paciente::getSecuencia()
{
    return this->secuencia;
}

void Paciente::setEnfermedades(vector<Enfermedad> enfermedades)
{
    this->enfermedades=enfermedades;
}

vector<Enfermedad> Paciente::getEnfermedades()
{
    return this->enfermedades;
}

string Paciente::getNombre()
{
    return this->nombre;
}

