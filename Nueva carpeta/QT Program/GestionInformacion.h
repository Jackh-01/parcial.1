#ifndef GESTIONINFORMACION_H
#define GESTIONINFORMACION_H
#include <fstream>

int Char2Int( char letra);
char Int2Char(int numero);
char* Open_File ();
int Count_Chars(char Arreglo[]);
int Count_Subjects ( char Arreglo[]);
int* Positions_Signs ( char Arreglo[], int Subjects);
char*** Reserve_Matix_Group(int Posiciones[], int Subjects, int Arreglo[]);
void  Crear_Base(char*** Base,int Tamano[] , int Subjects, char Texto[]);
void CalcularHorasEstudioIndependiente (char*** Base,int Subjects);
void PrintBaseDatos(char*** Base,int Tamano[] , int Subjects);
void DeleteBaseDatos (char*** Base, int Subjects);

#endif // GESTIONINFORMACION_H
