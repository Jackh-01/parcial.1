#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "GestionInformacion.h"

using namespace std;

bool ExisteMateria (char*** BaseDatos, char Codigo[], int Subjects)
{
    int y;
    for ( int i= 0; i<Subjects;i++)
    {
        y=0;
        for  (int j=0;j<7;j++)
        {
            if (BaseDatos[i][1][j]!=Codigo[j])
            {
                y = 1;
                break;
            }
        }
        if (y == 0) return true;
    }
    cout<<"Materia no registrada en el Pensum. ";
    return false;
}

int BuscarMateria (char*** BaseDatos, char Codigo[], int Subjects)
{
    int y;
    for ( int i= 0; i<Subjects;i++)
    {
        y=0;
        for  (int j=0;j<7;j++)
        {
            if (BaseDatos[i][1][j]!=Codigo[j])
            {
                y = 1;
                break;
            }
        }
        if (y == 0) return i;
    }
    return -1;
}

char*** CrearHorario (int Horas_Dormir, int Hora_Acostarse)
{
    char*** Semana = new char**[7];
    for (int i = 0; i < 7;i++)
    {
        Semana[i] = new char*[24];
        for (int j = 0; j<24;j++)
        {
            Semana[i][j]= new char[9];
            Semana[i][j][8]='\0';
            for ( int k=0;k<8;k++)
            {
                Semana[i][j][k]='-';
            }
        }
    }
    int HorasNocturnas = Horas_Dormir-(24-Hora_Acostarse);
    for (int i = 0; i < 7;i++)
    {
        for ( int k = Hora_Acostarse;k < 24 ; k++ )
        {
            for ( int j = 0; j<8; j++)
            {
                Semana[i][k][j]='*';
            }
        }
    }
    for (int i = 0; i < 7;i++)
    {
        for ( int k = 0;k < HorasNocturnas ; k++ )
        {
            for ( int j = 0; j<8; j++)
            {
                Semana[i][k][j]='*';
            }
        }
    }
    return Semana;
}

void ImprimirHorario (char*** Horario)
{
    cout<<endl;
    cout<<"HORAS\t\tLUNES   \t\tMARTES  \t\tMIERCOLES\t\tJUEVES  \t\tVIERNES ";
    cout<<"\t\tSABADO  \t\tDOMINGO "<<endl<<endl;
    for ( int hora=0; hora < 24; hora++)
    {
        if (hora<10)
        {
            cout<<'0'<<hora<<":00\t\t";
        }
        else
        {
            cout<<hora<<":00\t\t";
        }
        for (int dia = 0; dia<7;dia++)
        {
            for (int j = 0; j<9;j++)
            {
                cout<<Horario[dia][hora][j];
            }
            cout<<"\t\t";
        }
        cout<<endl;
    }
    cout<<endl<<endl<<"\tCONVENCIONES: '********': Hora programada para dormir,'--------': Hora libre,'+(Codigo de la materia)': Clase con docente de la materia (Codigo de la materia)";
    cout<<endl<<"\t\t\t'-(Codigo de la materia): Hora de estudio independiente para la materia (Codigo de la materia)."<<endl;
    cout<<endl<<endl;
}

void ImprimirNombreMateria (char*** Matriz, int Posicion)
{
    int j=0;
    while (Matriz[Posicion][0][j] != '\0')
    {
        cout<<Matriz[Posicion][0][j];
        j++;
    }
    cout<<endl;
}

void RegistrarClase (char*** Horario, int Dia, int HoraInicio, int HoraFinal, char Codigo[])
{
    int j;
    Horario[Dia][HoraInicio][0] = '+';
    Horario[Dia][HoraFinal-1][0] = '+';
    for ( int horas =HoraInicio;horas<HoraFinal; horas++ )
    {
        j = 1;
        Horario[Dia][horas][0]='+';
        for (int i=0; i<7;i++)
        {
            Horario[Dia][horas][j] = Codigo[i];
            j++;
        }
    }

}

void ImprimirDiasSemana()
{
    cout<<"1.Lunes    \t\t2.Martes"<<endl;
    cout<<"3.Miercoles\t\t4.jueves"<<endl;
    cout<<"5.Viernes  \t\t6.Sabado"<<endl;
    cout<<"\t7.Domingo "<<endl;
    cout<<endl;
}

void ImprimirConenciones (char*** Matriz, int Posiciones[], int Materias)
{
    int j=0;
    for (int i=0;i<Materias;i++)
    {
        j=0;
        while (Matriz[Posiciones[i]][1][j] != '\0')
        {
            cout<<Matriz[Posiciones[i]][1][j];
            j++;
        }
        cout<<":";
        j=0;
        while (Matriz[Posiciones[i]][0][j] != '\0')
        {
            cout<<Matriz[Posiciones[i]][0][j];
            j++;
        }
        cout<<"\t";
    }
    cout<<endl;
}

int ImportarCreditos (char*** Matriz, int Posicion)
{
    return Char2Int(Matriz[Posicion][4][0]);
}
