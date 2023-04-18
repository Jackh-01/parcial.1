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
                Semana[i][j][k]='1';
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
                Semana[i][k][j]='0';
            }
        }
    }
    for (int i = 0; i < 7;i++)
    {
        for ( int k = 0;k < HorasNocturnas ; k++ )
        {
            for ( int j = 0; j<8; j++)
            {
                Semana[i][k][j]='0';
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
}
