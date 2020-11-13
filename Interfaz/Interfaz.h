
#ifndef APP_PROCESAMIENTO_INTERFAZ_H
#define APP_PROCESAMIENTO_INTERFAZ_H


#include "../Programa/Programa.h"

using namespace std;




class Interfaz
{
    private:
        Programa programa;
    public:
        Interfaz()
            {
                this->programa=Programa();
                bool corriendo=true;
                cout << "Bienvenido al programa de analisis de datos"<<endl;
                while(corriendo)
                {
                    int opcion=0;
                    cout<<"1. Cargar datos del archivco datos_geneticos.json\n"
                          "2. Analisis 1\n"
                          "3. Analisis 2\n"
                          "4. Analisis 3\n"
                          "5. Salir\n"<<endl;
                    while(opcion<1 or opcion>5)
                    {
                        cout<<"Seleccione una de las opciones anteriores: "<<endl;
                        cin>>opcion;
                        if(cin.fail())
                        {
                            opcion=0;
                            cin.clear();
                            cin.ignore(256,'\n');
                        }
                    }
                    if(opcion==1)
                    {
                        this->programa.jsonDeserialize();
                        this->programa.binaryFileCreator();

                    }
                    else if(opcion==2)
                    {
                        this->programa.analisis1();
                    }
                    else if(opcion==3)
                    {
                        this->programa.analisis2();
                    }
                    else if(opcion==4)
                    {
                        this->programa.analisis3();
                    }
                    else if(opcion==5)
                    {
                        cout<<"Saliendo del programa..."<<endl;
                        corriendo=false;
                    }

                }
            }
};


#endif //APP_PROCESAMIENTO_INTERFAZ_H
