#ifndef REGISTRARINFORMACION_H
#define REGISTRARINFORMACION_H
#include <fstream>

bool ExisteMateria (char*** BaseDatos, char Codigo[], int Subjects);
int BuscarMateria (char*** BaseDatos, char Codigo[], int Subjects);
char*** CrearHorario (int Horas_Dormir, int Hora_Acostarse);
void ImprimirHorario (char*** Horario);

#endif // REGISTRARINFORMACION_H
