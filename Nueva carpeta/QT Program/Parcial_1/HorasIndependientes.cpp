#include <iostream>
#include "GestionInformacion.h"
#include "RegistrarInformacion.h"

using namespace std;


void LetreroHorasEstudio()
{
    ifstream archivo("HorasEstudio.txt");
    if (!archivo){
        cout << "No se pudo abrir el archivo." << endl;
        return;
    }
    char caracter;
    while (archivo.get(caracter)){
        cout << caracter;
    }
    archivo.close();
}

int CalcularEstudioIndependiente (char*** Matriz, int Posiciones[],int Materias)
{
    int contador=0;
    for ( int i = 0 ; i < Materias ; i++)
    {
        contador+=Char2Int(Matriz[Posiciones[i]][3][0]);
    }
    return contador;
}

int CalcularEstudioProfesor (char*** Matriz, int Posiciones[],int Materias)
{
    int contador=0;
    for ( int i = 0 ; i < Materias ; i++)
    {
        contador+=Char2Int(Matriz[Posiciones[i]][2][0]);
    }
    return contador;
}

void HorasClaseDia (char*** Semana, int ClasesPorDia[])
{
    int contador;
    for ( int i = 0; i<7;i++)
    {
        contador=0;
        for ( int j = 0; j<24;j++)
        {
            if (Semana[i][j][0]>='A' && Semana[i][j][0]<='Z') contador++;
        }
        ClasesPorDia[i] = contador;
    }
}

void HorasLibresDia (char*** Semana, int HorasLibresPorDia[])
{
    int contador;
    for ( int i = 0; i<7;i++)
    {
        contador=0;
        for ( int j = 0; j<24;j++)
        {
            if (Semana[i][j][1]=='-') contador++;
        }
        HorasLibresPorDia[i] = contador;
    }
}

void RepartirHorasEstudio (char*** Matriz, int Posiciones[], int Materias,int HorasRepartidas[] )
{
    int HI, valor;
    int Posicion = 0;
    for ( int i = 0; i<Materias; i++)
        {
            HI = Char2Int(Matriz[Posiciones[i]][3][0]);
            for ( int j = 0; j<HI;j++)
            {
                valor = Posiciones[i];
                HorasRepartidas[Posicion]=valor;
                Posicion++;

            }
        }
    cout<<endl;
}

void HorasEstudioAutomatico ( char*** Matriz, char*** Horario, int Posiciones[], int Materias, int Horaslibres[],int HorasSemana)
{
    int contador_1, contador_2,dia,hora;
    int RepartirHoras[HorasSemana];
    RepartirHorasEstudio(Matriz,Posiciones,Materias,RepartirHoras);
    contador_1 = 0;
    dia=0;
    while(contador_1 <HorasSemana)
    {
        hora=0;
        contador_2 = 0;
        while(contador_2<Horaslibres[dia])
        {
            if (Horario[dia][hora][1] == '-')
            {
                for ( int j=1;j<8;j++)
                {
                    Horario[dia][hora][j] = Matriz[RepartirHoras[contador_1]][0][j-1];
                }
                contador_2++;
                contador_1++;
            }
            hora++;
        }
        dia++;
    }
    ImprimirHorario(Horario);
}

bool ConfirmarHoraLibre ( char*** Horario, int dia, int hora)
{
    if (Horario[dia][hora][1]=='-') return true;
    else
    {
        cout<<"\t\t\t\t\t\t Ya tiene un evento programado en esa hora."<<endl;
        return false;
    }
}

void HorasEstudioManual ( char*** Matriz, char*** Horario, int Posiciones[], int Materias, int HorasSemana)
{
    int contador_1, contador_2,dia,hora;
    int* RepartirHoras = new int[HorasSemana];
    bool val;
    RepartirHorasEstudio(Matriz,Posiciones,Materias,RepartirHoras);
    contador_1 = 0;
    dia=0;

    while(contador_1 <HorasSemana)
    {
        val = false;
        ImprimirHorario(Horario);
        while (!val)
        {
            cout << "\t\t\t\t\t\t ¿ Que dia desea programar la hora de estudio "<<contador_1+1<<" ?  : "<<endl<<endl;
            ImprimirDiasSemana();
            dia = 0;
            while (dia<=0 || dia>7 )
            {
                cout << "\t\t\t\t\t\t Ingrese una opcion : ";
                cin >> dia;
                cout<<endl;
            }
            cout << "\t\t\t\t\t (Formato de 24 horas) ¿ A que horas desea programar la hora de estudio ?  : ";
            cin >> hora;
            cout<<endl;
            val = ConfirmarHoraLibre(Horario,dia-1,hora);
        }
        for ( int j=1;j<8;j++)
        {
            Horario[dia-1][hora][j] = Matriz[RepartirHoras[contador_1]][0][j-1];
        }
        contador_1++;
    }
    delete [] RepartirHoras;
    ImprimirHorario(Horario);
}


char*** CargarHorario(char nombreArchivo[])
{
    std::ifstream archivo(nombreArchivo, std::ios::in | std::ios::ate);
    int tamano = archivo.tellg();
    archivo.seekg(0);
    char* contenido = new char[tamano];
    archivo.read(contenido, tamano);
    int contador_contenido = 0;
    char*** semana = new char**[7];
    for (int i = 0; i < 7; i++) {
        semana[i] = new char*[24];
        for (int j = 0; j < 24; j++) {
            semana[i][j] = new char[9];
            semana[i][j][8] = '\0';
            for (int k = 0; k < 8; k++) {
                semana[i][j][k] =contenido[contador_contenido];
                contador_contenido++;
            }
        }
    }
    delete[] contenido;
    archivo.close(); // Cerramos el archivo
    return semana;
}

int ContarHoras ( int Arreglo[] )
{
    int contador=0;
    for ( int i = 0; i<7;i++)
    {
        contador+=Arreglo[i];
    }
    return contador;
}

int PosicionMayor (int Arreglo[] )
{
    int mayor = 0, posicion;
    for ( int i = 0; i<7;i++)
    {
        if (Arreglo[i]>mayor)
        {
            mayor=Arreglo[i];
            posicion = i;
        }
    }
    return posicion;
}

void DisminuirHoras (int Arreglo[], int HorasSemana)
{
    int posicion;
    while (ContarHoras(Arreglo) != HorasSemana )
    {
        posicion = PosicionMayor (Arreglo);
        Arreglo[posicion]--;
    }
}

void AumentarHoras (int Arreglo[], int HorasSemana)
{

    while (ContarHoras(Arreglo) != HorasSemana )
    {
        Arreglo[6]++;
        if (ContarHoras(Arreglo) == HorasSemana) break;
        Arreglo[6]++;
    }
}

int roundnumber(double num)
{
    if (num > 0) {
        return static_cast<int>(num + 0.5);
    } else if (num < 0) {
        return static_cast<int>(num - 0.5);
    } else {
        return 0;
    }
}


void distribucionProporcional(int horasEstudio, int horasLibres[], int diasSemana)
{
    int totalHorasLibres = 0;
    double proporciones[7];
    for (int i = 0; i < diasSemana; i++) {
        totalHorasLibres += horasLibres[i];
    }
    for (int i = 0; i < diasSemana; i++) {
        proporciones[i] = (double)horasLibres[i] / totalHorasLibres;
    }
    for (int i = 0; i < diasSemana; i++) {
        horasLibres[i] = roundnumber(horasEstudio * proporciones[i]);
    }
}
