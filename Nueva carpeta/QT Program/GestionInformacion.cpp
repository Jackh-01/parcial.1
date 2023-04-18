#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>

using namespace std;

int Char2Int( char letra)
{
    return int(letra)-48;
}

char Int2Char(int numero)
{
    return char(numero+48);
}

char* Open_File ()
{
    std::ifstream archivo("Plan de Estudios.txt", std::ios::in | std::ios::ate);
    int tamano = archivo.tellg();
    archivo.seekg(0);
    char* contenido = new char[tamano];
    archivo.read(contenido, tamano);
    return contenido;
}

int Count_Chars(char Arreglo[])
{
    int Count = 0;
    while (Arreglo[Count] != '\0')
    {
        Count++;
    }
    return Count;
}

int Count_Subjects ( char Arreglo[])
{
    int Longitud = Count_Chars(Arreglo);
    int Count=0;
    for ( int i=0;i<Longitud;i++)
    {
        if (Arreglo[i]=='.') Count++;
    }
    return Count;
}

int* Positions_Signs ( char Arreglo[], int Subjects)
{
    int Longitud = Count_Chars(Arreglo);
    int* Posiciones = new int [Subjects*4];
    int Contador=0;
    for (int i=0; i<Longitud; i++)
    {
        if (Arreglo[i]=='.' || Arreglo[i]==',')
        {
            Posiciones[Contador]=i;
            Contador++;
        }
    }
    return Posiciones;
}


char*** Reserve_Matix_Group(int Posiciones[], int Subjects, int Arreglo[])
{
    char*** Matrix_Group= new char**[Subjects];
    int contador=0,posicion=0;
    for (int i=0; i<Subjects; i++)
    {
        Matrix_Group[i]=new char*[5];
    }
    for (int i=0; i<Subjects; i++)
    {
        for (int j=0;j<5;j++)
        {
            if (contador==0)
            {
                Matrix_Group[i][j]= new char[Posiciones[0]+1];
                Matrix_Group[i][j][Posiciones[0]] = '\0';
                Arreglo[posicion]=Posiciones[0];
                contador++;
                posicion++;
            }
            else if (j == 3)
            {
                Matrix_Group[i][j]= new char[2];
                Matrix_Group[i][j][1]='\0';
                Arreglo[posicion]=1;
                posicion++;
            }
            else
            {
                Matrix_Group[i][j]= new char[Posiciones[contador]-Posiciones[contador-1]];
                Matrix_Group[i][j][(Posiciones[contador]-Posiciones[contador-1])-1]='\0';
                Arreglo[posicion]=(Posiciones[contador]-Posiciones[contador-1])-1;
                contador++;
                posicion++;
            }
        }

    }
    return Matrix_Group;
}

void  Crear_Base(char*** Base,int Tamano[] , int Subjects, char Texto[])
{
    int Posicion_Tamano=0, Posicion_Texto=0;
    for (int i=0; i<Subjects; i++)
    {
        for (int j=0;j<Tamano[Posicion_Tamano];j++)
        {
            Base[i][0][j]=Texto[Posicion_Texto];
            Posicion_Texto++;
        }
        Posicion_Tamano++;
        Posicion_Texto++;
        for (int j=0;j<Tamano[Posicion_Tamano];j++)
        {
            Base[i][1][j]=Texto[Posicion_Texto];
            Posicion_Texto++;
        }
        Posicion_Tamano++;
        Posicion_Texto++;
        for (int j=0;j<Tamano[Posicion_Tamano];j++)
        {
            Base[i][2][j]=Texto[Posicion_Texto];
            Posicion_Texto++;
        }
        Posicion_Tamano++;
        Posicion_Texto++;
        Posicion_Tamano++;
        for (int j=0;j<Tamano[Posicion_Tamano];j++)
        {
            Base[i][4][j]=Texto[Posicion_Texto];
            Posicion_Texto++;
        }
        Posicion_Tamano++;
        Posicion_Texto++;
    }
}

void CalcularHorasEstudioIndependiente (char*** Base,int Subjects)
{
    int creditos, docente, independiente;
    for (int i=0; i<Subjects; i++)
    {
        creditos=Char2Int(Base[i][4][0]);
        docente=Char2Int(Base[i][2][0]);
        independiente = ((creditos*48)/16)-docente;
        if (independiente<0) independiente = 0;
        Base[i][3][0]=Int2Char(independiente);
    }
}

void PrintBaseDatos(char*** Base,int Tamano[] , int Subjects)
{
    int Posicion_Tamano=0;
    for (int i=0; i<Subjects; i++)
    {
        cout<<endl<<"***** MATERIA "<<i+1<<" *****"<<endl;
        cout<<"Nombre de la materia: ";
        for (int j=0;j<Tamano[Posicion_Tamano];j++)
        {
            cout<<Base[i][0][j];
        }
        cout<<endl;
        Posicion_Tamano++;
        cout<<"Codigo de la materia: ";
        for (int j=0;j<Tamano[Posicion_Tamano];j++)
        {
            cout<<Base[i][1][j];
        }
        cout<<endl;
        Posicion_Tamano++;
        cout<<"Horas con docente: ";
        for (int j=0;j<Tamano[Posicion_Tamano];j++)
        {
            cout<<Base[i][2][j];
        }
        cout<<endl;
        Posicion_Tamano++;
        cout<<"Horas de estudio independiente: ";
        cout<<Base[i][3][0];
        cout<<endl;
        Posicion_Tamano++;
        cout<<"Creditos: ";
        for (int j=0;j<Tamano[Posicion_Tamano];j++)
        {
            cout<<Base[i][4][j];
        }
        cout<<endl;
        Posicion_Tamano++;
        cout<<"****************"<<endl;
    }
}

void DeleteBaseDatos (char*** Base, int Subjects)
{
    for (int i=0; i<Subjects; i++)
    {
        for(int j=0; j<5;j++)
        {
            delete[] Base[i][j];
        }
    }
}

