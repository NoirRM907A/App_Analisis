
#ifndef APP_PROCESAMIENTO_PACIENTE_H
#define APP_PROCESAMIENTO_PACIENTE_H

#include <string>
#include<vector>
#include "Enfermedad.h"

using namespace std;
class Paciente
{
    private:
        string id;
        string nombre;
        string telefono;
        string correo;
        string secuencia;
        vector<Enfermedad>enfermedades;

    public:
        Paciente();
        Paciente(string id,string nombre,string telefono,string correo,string secuencia);
        string getId();
        string getTelefono();
        string getCorreo();
        string getSecuencia();
        string getNombre();
        void setEnfermedades(vector<Enfermedad> enfermedades);
        vector<Enfermedad>getEnfermedades();



};


#endif //APP_PROCESAMIENTO_PACIENTE_H
