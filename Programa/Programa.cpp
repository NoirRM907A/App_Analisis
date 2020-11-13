
#include "Programa.h"

Programa::Programa()
{
    this->pacientes= vector<Paciente>();
    this->enfermedades=vector<Enfermedad>();
}

void Programa::jsonDeserialize()
{
    std::ifstream is("datos_geneticos.json");
    json j= json::parse(is);

    json pacientesJson=j["pacientes"];
    for(int ind=0;ind<pacientesJson.size();ind++)
    {
        vector<Enfermedad> pacienteEnfermedades=vector<Enfermedad>();
        json enfermedadesJson=pacientesJson[ind]["enfermedades"];
        for(int ind2=0;ind2<enfermedadesJson.size();ind2++)
        {
            pacienteEnfermedades.push_back(Enfermedad(enfermedadesJson[ind2]["enfermedad"],enfermedadesJson[ind2]["secuencia"]));
        }
        this->pacientes.push_back(Paciente(pacientesJson[ind]["id"],pacientesJson[ind]["nombre"],pacientesJson[ind]["telefono"],pacientesJson[ind]["correo"],pacientesJson[ind]["secuencia"]));
        this->pacientes[ind].setEnfermedades(pacienteEnfermedades);
    }
}
void Programa::binaryFileCreator()
{
    vector<pacienteTemp> pacientesTemp=pacientesAArray();
    ofstream base_datos;
    base_datos.open("base_datos.dat",ios::binary|ios::out);
    if(base_datos.is_open())
    {
        for(int ind=0;ind<pacientesTemp.size();ind++)
        {
            pacienteTemp p=pacientesTemp[ind];
            base_datos.write((char*)&p,sizeof(p));
        }
        cout<<"\nArchivo binario creado correctamente!\n"<<endl;
    }
    else
    {
        cout<<"\nError al crear el archivo binario!\n"<<endl;
    }

    this->pacientes=vector<Paciente>();
    base_datos.close();
}
vector<Paciente> Programa::binaryFileReader()
{
    ifstream base_datos;
    base_datos.open("base_datos.dat",ios::binary|ios::in);
    vector<Paciente>output=vector<Paciente>();
    if(base_datos.is_open())
    {

        while(!base_datos.eof())
        {
            pacienteTemp p;
            base_datos.read((char*)&p,sizeof(pacienteTemp));

            Paciente paciente= Paciente(convertToString(p.id,sizeof(p.id)/sizeof(char)),convertToString(p.nombre,sizeof(p.nombre)/sizeof(char)),convertToString(p.telefono,sizeof(p.telefono)/sizeof(char)),convertToString(p.correo,sizeof(p.correo)/sizeof(char)),convertToString(p.secuencia,sizeof(p.secuencia)/sizeof(char)));
            int size=sizeof(p.enfermedades)/sizeof(enfermedadTemp);
            vector<Enfermedad>enfermedades=vector<Enfermedad>();
            for(int ind=0;ind<size;ind++)
            {
                enfermedadTemp e=p.enfermedades[ind];
                if(e.enfermedad[0]=='\000')
                {
                    break;
                }
                Enfermedad enfermedad= Enfermedad(convertToString(e.enfermedad,sizeof(e.enfermedad)/sizeof(char)),convertToString(e.secuencia,sizeof(e.secuencia)/sizeof(char)));
                enfermedades.push_back(enfermedad);
            }
            paciente.setEnfermedades(enfermedades);
            output.push_back(paciente);
        }
    }
    else
    {
        cout<<"\nError al crear el archivo binario!\n"<<endl;
    }
    base_datos.close();
    output.erase(output.end());
    return output;

}
void Programa::analisis1()
{
    if(this->pacientes.empty())
    {
        this->pacientes = binaryFileReader();
        setEnfermedades();
    }

    vector<int>incidencias=vector<int>();
    vector<vector<Paciente>>pacientesIncidentesPorEnfermedad= vector<vector<Paciente>>();

    for(int ind=0;ind<this->enfermedades.size();ind++)
    {
        Enfermedad enfermedad=this->enfermedades[ind];
        int incidencia=0;
        vector<Paciente> pacientesIncidentes= vector<Paciente>();
        for(int ind2=0;ind2<this->pacientes.size();ind2++)
        {
            Paciente paciente=this->pacientes[ind2];
            vector<Enfermedad>enfermedadesPaciente=paciente.getEnfermedades();
            for(int ind3=0;ind3<enfermedadesPaciente.size();ind3++)
            {
                if(enfermedadesPaciente[ind3].getEnfermedad()==enfermedad.getEnfermedad())
                {
                    incidencia++;
                    pacientesIncidentes.push_back(paciente);
                    break;
                }
            }
        }
        incidencias.push_back(incidencia);
        pacientesIncidentesPorEnfermedad.push_back(pacientesIncidentes);
    }
    vector<vector<int>> ordenados=insertionSort(incidencias);

    std::reverse(ordenados[0].begin(), ordenados[0].end());
    std::reverse(ordenados[1].begin(), ordenados[1].end());

    cout<<"----------------------ANALISIS 1: REPORTE DE PACIENTES POR ENFERMEDAD ---------------------- \n"<<endl;
    for(int ind=0;ind<ordenados[1].size();ind++)
    {
        cout<<"-->"+this->enfermedades[ordenados[1][ind]].getEnfermedad()+" ("+this->enfermedades[ordenados[1][ind]].getSecuencia()+")"<<endl;
        cout<<"\tPacientes susceptibles: "+to_string(ordenados[0][ind])+"\n"<<endl;
        vector<Paciente>pacientesSusceptibles=pacientesIncidentesPorEnfermedad[ordenados[1][ind]];
        for(int ind2=0;ind2<pacientesSusceptibles.size();ind2++)
        {
            cout<<"\t\t"+to_string(ind2+1)+") "+pacientesSusceptibles[ind2].getNombre()<<endl;
        }
        cout<<"\n"<<endl;
    }

}
void Programa::analisis2()
{
    if (this->pacientes.empty())
    {
        this->pacientes = binaryFileReader();
        setEnfermedades();
    }
    cout<<"----------------------ANALISIS 2: CONCENTRACION DE BASES NITROGENADAS POR PACIENTE ---------------------- \n"<<endl;
    for(int ind=0;ind<this->pacientes.size();ind++)
    {
        Paciente paciente= this->pacientes[ind];
        cout<<"---> Paciente: "+paciente.getNombre()+"\n"<<endl;
        float A=0;
        float T=0;
        float G=0;
        float C=0;

        int total=0;
        string secuencia=paciente.getSecuencia();
        for(int ind2=0;ind2<secuencia.size();ind2++)
        {
            char valor=secuencia.at(ind2);
            if(valor=='A')
            {
                A++;
            }
            else if(valor=='T')
            {
                T++;
            }
            else if(valor=='G')
            {
                G++;
            }
            else if(valor=='C')
            {
                C++;
            }
            total++;
        }
        A=(A/total)*100;
        T=(T/total)*100;
        G=(G/total)*100;
        C=(C/total)*100;

        cout<<"\t\tA- %"<< fixed << setprecision(2)<<A<<" T- %"<<T<<" G- %"<<G<<" C- %"<<C<<"\n"<<endl;

    }
}
void Programa::analisis3()
{
    if (this->pacientes.empty())
    {
        this->pacientes = binaryFileReader();
        setEnfermedades();
    }
    cout<<"----------------------ANALISIS 3: SUSCEPTIBILIDAD POR PACIENTE A CADA ENFERMEDAD ---------------------- \n"<<endl;
    for(int ind=0;ind<this->pacientes.size();ind++)
    {
        Paciente paciente=this->pacientes[ind];
        vector<int> incidenciasPorEnfermedad=getEnfermedadesPorPaciente(paciente);
        cout<<"--->Paciente: "+paciente.getNombre()+"\n"<<endl;
        for(int ind2=0;ind2<paciente.getEnfermedades().size();ind2++)
        {
            Enfermedad enfermedad=paciente.getEnfermedades()[ind2];
            cout<<"\t\t-Enfermedad: "<<enfermedad.getEnfermedad()<<" ("<<incidenciasPorEnfermedad[ind2]<<" Coincidencias)\n"<<endl;
            if(incidenciasPorEnfermedad[ind2]<2)
            {
                cout<<"\t\t\tProbabilidad de contraer la enfermedad: menos del 35%\n"<<endl;
            }
            else if(incidenciasPorEnfermedad[ind2]==2)
            {
                cout<<"\t\t\tProbabilidad de contraer la enfermedad: 35%\n"<<endl;
            }
            else if(incidenciasPorEnfermedad[ind2]>=3)
            {
                cout<<"\t\t\tProbabilidad de contraer la enfermedad: 65%\n"<<endl;
            }

        }
    }
}


vector<Programa::pacienteTemp> Programa::pacientesAArray()
{
    vector<pacienteTemp>output=vector<pacienteTemp>();

    for(int ind= 0;ind<this->pacientes.size();ind++)
    {
        Paciente paciente= this->pacientes[ind];
        pacienteTemp p= pacienteTemp ();
        strcpy(p.id,paciente.getId().c_str());
        strcpy(p.nombre,paciente.getNombre().c_str());
        strcpy(p.correo,paciente.getCorreo().c_str());
        strcpy(p.secuencia,paciente.getSecuencia().c_str());
        strcpy(p.telefono,paciente.getTelefono().c_str());

        for(int ind2=0;ind2<paciente.getEnfermedades().size();ind2++)
        {
            Enfermedad enfermedad= paciente.getEnfermedades()[ind2];
            enfermedadTemp e= enfermedadTemp ();
            strcpy(e.enfermedad,enfermedad.getEnfermedad().c_str());
            strcpy(e.secuencia,enfermedad.getSecuencia().c_str());
            p.enfermedades[ind2]=e;
        }
        output.push_back(p);
    }
    return output;
}
string Programa::convertToString(char charArr[],int size)
{
    string s = "";
    for (int i = 0; i <size; i++) {
        if(charArr[i]!='\000')
        {
            s +=charArr[i];
        }
    }

    return s;
}
void Programa::setEnfermedades()
{
    this->enfermedades=vector<Enfermedad>();
    for(int ind=0;ind<this->pacientes.size();ind++)
    {
        vector<Enfermedad>enfermedadesPaciente= this->pacientes[ind].getEnfermedades();
        for(int ind2=0;ind2<enfermedadesPaciente.size();ind2++)
        {
            int size=this->enfermedades.size();
            bool exists=false;
            for(int ind3=0;ind3<size;ind3++)
            {
                if(this->enfermedades[ind3].getEnfermedad()==enfermedadesPaciente[ind2].getEnfermedad())
                {
                    exists=true;
                }
            }
            if(!exists)
            {
                this->enfermedades.push_back(enfermedadesPaciente[ind2]);
            }
        }
    }
}
vector<vector<int>> Programa::insertionSort(vector<int> arregloIncidencia)
{
    vector<int>posiciones=vector<int>();
    for(int ind=0;ind<arregloIncidencia.size();ind++)
    {
        posiciones.push_back(ind);
    }

    while(!ordenado(arregloIncidencia))
    {
        int ind = 1;
        while (ind < arregloIncidencia.size())
        {
            if (arregloIncidencia[ind] < arregloIncidencia[ind - 1])
            {
                int tempInd = 0;
                while (arregloIncidencia[tempInd] < arregloIncidencia[ind])
                {
                    tempInd++;
                }
                arregloIncidencia.insert(arregloIncidencia.begin() + tempInd, arregloIncidencia[ind]);
                arregloIncidencia.erase(arregloIncidencia.begin() + ind + 1);

                posiciones.insert(posiciones.begin() + tempInd, posiciones[ind]);
                posiciones.erase(posiciones.begin() + ind + 1);
            }
            ind++;
        }
        break;

    }
    return {arregloIncidencia,posiciones};
}
bool Programa::ordenado(vector<int> arreglo)
{
    int ind=0;
    while(ind<arreglo.size()-1)
    {
        if(arreglo[ind]>arreglo[ind+1])
        {
            return false;
        }
        ind++;
    }
    return true;
}

vector<int>Programa::getEnfermedadesPorPaciente(Paciente paciente)
{
    vector<int> salida=vector<int>();
    for(int ind=0;ind<paciente.getEnfermedades().size();ind++)
    {
        int incidencias=0;
        Enfermedad enfermedad=paciente.getEnfermedades()[ind];
        int pacienteSecuenciaL=paciente.getSecuencia().length();
        int enfermedadSecuenciaL=enfermedad.getSecuencia().length();

        string secuenciaPaciente=paciente.getSecuencia();
        string secuenciaEnfermedad=enfermedad.getSecuencia();

        for(int ind2=0;ind2<pacienteSecuenciaL;ind2++)
        {
            string fragmento="";

            if(secuenciaPaciente[ind2]==secuenciaEnfermedad[0])
            {
                for (int ind3 = ind2; ind3 < ind2 + enfermedadSecuenciaL; ind3++) {
                    if (ind3 > pacienteSecuenciaL) {
                        break;
                    }
                    fragmento += secuenciaPaciente[ind3];
                }
                if (fragmento.length() != enfermedadSecuenciaL) {
                    break;
                }
                if (fragmento == secuenciaEnfermedad)
                {
                    incidencias++;
                }
            }
        }
        salida.push_back(incidencias);
    }
    return salida;
}
