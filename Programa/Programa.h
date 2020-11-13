
#ifndef APP_ANALISIS_PROGRAMA_H
#define APP_ANALISIS_PROGRAMA_H

#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include "../Entidades/Paciente.h"
#include "../Entidades/Enfermedad.h"
#include "../json.hpp"

using namespace std;



using json=nlohmann::json ;

class Programa
{
    private:
        vector<Paciente> pacientes;
        vector<Enfermedad>enfermedades;

    public:
        typedef struct
        {
            char enfermedad[100];
            char secuencia[10];
        }enfermedadTemp;

        typedef struct
        {
            char id[20];
            char nombre[50];
            char correo[100];
            char secuencia[2048];
            char telefono[50];
            enfermedadTemp enfermedades[15];
        }pacienteTemp;

        Programa();
        void jsonDeserialize();
        void binaryFileCreator();
        vector<Paciente> binaryFileReader();
        void analisis1();
        void analisis2();
        void analisis3();
        vector<pacienteTemp> pacientesAArray();
        string convertToString(char charArr[],int size);
        void setEnfermedades();
        vector<vector<int>> insertionSort(vector<int> arregloIncidencia);
        bool ordenado(vector<int> arreglo);
        vector<int>getEnfermedadesPorPaciente(Paciente paciente);

};


#endif //APP_ANALISIS_PROGRAMA_H
