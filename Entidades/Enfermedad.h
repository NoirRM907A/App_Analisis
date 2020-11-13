
#ifndef APP_PROCESAMIENTO_ENFERMEDAD_H
#define APP_PROCESAMIENTO_ENFERMEDAD_H

#include <string>

using namespace std;

class Enfermedad
{
    private:
        string enfermedad;
        string secuencia;

    public:
        Enfermedad();
        Enfermedad(string enfermedad, string secuencia);
        string getEnfermedad();
        string getSecuencia();
};


#endif //APP_PROCESAMIENTO_ENFERMEDAD_H
