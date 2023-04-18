#ifndef REGISTRARINFORMACION_H
#define REGISTRARINFORMACION_H
#include <fstream>

bool ExisteMateria (char*** BaseDatos, char Codigo[], int Subjects);
int BuscarMateria (char*** BaseDatos, char Codigo[], int Subjects);
char*** CrearHorario (int Horas_Dormir, int Hora_Acostarse);
void ImprimirHorario (char*** Horario);
void ImprimirNombreMateria (char*** Matriz, int Posicion);
void RegistrarClase (char*** Horario, int Dia, int HoraInicio, int HoraFinal, char Codigo[]);
void ImprimirDiasSemana();
void ImprimirConenciones (char*** Matriz, int Posiciones[], int Materias);
int ImportarCreditos (char*** Matriz, int Posicion);

#endif // REGISTRARINFORMACION_H
