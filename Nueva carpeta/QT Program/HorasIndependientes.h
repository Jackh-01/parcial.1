#ifndef HORASINDEPENDIENTES_H
#define HORASINDEPENDIENTES_H
#include <fstream>

int CalcularEstudioIndependiente (char*** Matriz, int Posiciones[],int Materias);
int CalcularEstudioProfesor (char*** Matriz, int Posiciones[],int Materias);
void HorasClaseDia (char*** Semana, int ClasesPorDia[]);
void HorasLibresDia (char*** Semana, int HorasLibresPorDia[]);
void RepartirHorasEstudio (char*** Matriz, int Posiciones[], int Materias,int HorasRepartidas[] );
void HorasEstudioAutomatico ( char*** Matriz, char*** Horario, int Posiciones[], int Materias, int Horaslibres[],int HorasSemana);
char*** CargarHorario(char nombreArchivo[]) ;
int ContarHoras ( int Arreglo[] );
int PosicionMayor (int Arreglo[] );
void DisminuirHoras (int Arreglo[], int HorasSemana);
void AumentarHoras (int Arreglo[], int HorasSemana);
int roundnumber(double num) ;
void distribucionProporcional(int horasEstudio, int horasLibres[], int diasSemana) ;

#endif // HORASINDEPENDIENTES_H
