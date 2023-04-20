#ifndef REGISTRARINFORMACION_H
#define REGISTRARINFORMACION_H
#include <fstream>


void leerArchivo();
void LetreroHorario();
void LetreroRegistro();
int contarCaracteres(char nombre[]) ;
char convertir_a_mayuscula(char caracter_minuscula);
bool ExisteMateria (char*** BaseDatos, char Codigo[], int Subjects);
int BuscarMateria (char*** BaseDatos, char Codigo[], int Subjects);
char*** CrearHorario (int Horas_Dormir, int Hora_Acostarse);
void ImprimirHorario (char*** Horario);
void ImprimirNombreMateria (char*** Matriz, int Posicion);
void RegistrarClase (char *** Matriz,char*** Horario, int Dia, int HoraInicio, int HoraFinal, char Codigo[], int Posicion);
void ImprimirDiasSemana();
void ImprimirConenciones (char*** Matriz, int Posiciones[], int Materias);
int ImportarCreditos (char*** Matriz, int Posicion);

#endif // REGISTRARINFORMACION_H
