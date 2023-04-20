#include <iostream>
#include "GestionInformacion.h"

using namespace std;

void leerArchivo()
{
    ifstream archivo("MenuPrincipal.txt");
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

void LetreroHorario()
{
    ifstream archivo("Horario.txt");
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

void LetreroRegistro()
{
    ifstream archivo("RegistroInformacion.txt");
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


int contarCaracteres(char nombre[])
{
    int contador = 0;
    while (nombre[contador] != '\0') {
        contador++;
    }
    return contador;
}

char convertir_a_mayuscula(char caracter_minuscula)
{
    if (caracter_minuscula >= 'a' && caracter_minuscula <= 'z')
    {
        return caracter_minuscula - 32;
    } else
    {
        return caracter_minuscula;
    }
}

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
    cout<<"\t\t\t\t\t\tMateria no registrada en el Pensum. ";
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
    LetreroHorario();
    cout<<endl;
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
    cout<<endl<<endl<<"\t\tCONVENCIONES: '********': Hora programada para dormir,'--------': Hora libre,'(Nombre de la materia en mayuscula)': Clase con docente";
    cout<<endl<<"\t\t\t\t\t'-(Nombre de la materia): Hora de estudio independiente."<<endl;
    cout<<"***************************************************************************************************************************************************************************"<<endl;
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

void RegistrarClase ( char *** Matriz, char*** Horario, int Dia, int HoraInicio, int HoraFinal, char Codigo[], int Posicion)
{
    int j;
    Horario[Dia][HoraInicio][0] = '+';
    Horario[Dia][HoraFinal-1][0] = '+';
    for ( int horas =HoraInicio;horas<HoraFinal; horas++ )
    {
        for (int i=0; i<8;i++)
        {
            Horario[Dia][horas][i] = convertir_a_mayuscula(Matriz[Posicion][0][i]);
        }
    }

}

void ImprimirDiasSemana()
{
    cout<<"\t\t\t\t\t\t\t1.Lunes    \t\t\t2.Martes"<<endl;
    cout<<"\t\t\t\t\t\t\t3.Miercoles\t\t\t4.jueves"<<endl;
    cout<<"\t\t\t\t\t\t\t5.Viernes  \t\t\t6.Sabado"<<endl;
    cout<<"\t\t\t\t\t\t\t\t\t7.Domingo "<<endl;
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


void DeleteHorario (char*** Semana)
{
    for ( int i = 0; i<7 ; i++)
    {
        for ( int j = 0; i<24 ; j++)
        {
            delete[] Semana[i][j];
        }
    }
}
