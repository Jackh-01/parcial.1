#include <iostream>
#include "GestionInformacion.h"
#include "RegistrarInformacion.h"
#include "HorasIndependientes.h"


using namespace std;

int main()
{
    /* FASE 1: IMPORTAR INFORMACIÓN */

    char* Informacion;
    int* Posiciones;
    char*** Matriz;
    Informacion = Open_File();
    int materias = Count_Subjects(Informacion);
    Posiciones = Positions_Signs(Informacion,materias);
    int* Tamano_materias = new int [materias*5];
    Matriz = Reserve_Matix_Group(Posiciones,materias,Tamano_materias );
    Crear_Base(Matriz,Tamano_materias, materias, Informacion);
    CalcularHorasEstudioIndependiente ( Matriz,materias);
    /*PrintBaseDatos(Matriz,Tamano_materias, materias);*/
    cout<<endl;


    /* FASE 2: REGISTRAR INFORMACIÓN */

    leerArchivo();
    char* UserName_1 = new char[20];
    cout <<endl<<endl<<endl<< "\t\t\t\t\t Ingrese su nombre de usuario (@udea.edu.co): ";
    cin >> UserName_1;
    int cantidad = contarCaracteres(UserName_1);
    char UserName[cantidad+5];
    for ( int i = 0; i<cantidad;i++)
    {
        UserName[i]=UserName_1[i];
    }
    UserName[cantidad] = '.';UserName[cantidad+1] = 't';UserName[cantidad+2] = 'x';UserName[cantidad+3] = 't';UserName[cantidad+4] = '\0';
    delete[] UserName_1;
    std::ifstream input_file(UserName);
    if (input_file)
    {
        char*** HorarioCreado;
        HorarioCreado = CargarHorario( UserName) ;
        ImprimirHorario(HorarioCreado);
    }
    else
    {
        cout<<endl;
        cout<<endl;
        LetreroRegistro();
        cout<<endl;
        cout<<endl;
        int n,n_aux, PosicionMateria,i=0, HorasDormir,HoraAcostarse, ClasesSemana,DiaClase, HoraInicio, Horafinal, j=0;
        char* CodigoMateria = new char[7];
        char*** Horario;
        cout << "\t\t\t\t\t ¿ Cuantas horas diarias quiere dormir ? ( Recomendado 8 ): ";
        cin >> HorasDormir;
        while (HorasDormir<0 || HorasDormir>11)
        {
            cout << "\t\t\t\t\t ¿ Cuantas horas diarias quiere dormir ? ( Recomendado 8 ): ";
            cin >> HorasDormir;
        }
        cout<<endl;
        int CreditosMaximos = ((7*24)-(HorasDormir*7))/(48/16);
        cout << "\t\t\t\t\t ¿ A que horas desea acostarse ? (Formato de 24 horas) : ";
        cin >> HoraAcostarse;
        while (HoraAcostarse<0 || HoraAcostarse>23)
        {
            cout << "\t\t\t\t\t ¿ A que horas desea acostarse ? (Formato de 24 horas) : ";
            cin >> HoraAcostarse;
        }
        cout<<endl;
        cout<<endl<<endl<<"\t\t\t\t\t\t Usted solo puede registrar maximo "<<CreditosMaximos<<" creditos."<<endl;
        Horario = CrearHorario(HorasDormir,HoraAcostarse );
        ImprimirHorario(Horario);
        cout << "\t\t\t\t\t\t\t ¿ Cuantas materias matriculo ? ";
        cin >> n;
        cout<<endl;
        n_aux = n;
        int* MateriasMatriculadas = new int [n];
        int P_M = 0, Creditos_Acumulados=0;
        while(i<n)
        {
            cout << "\t\t\t\t\t\t\t Ingrese el codigo de la materia "<<i+1<<": ";
            cin >> CodigoMateria;
            cout<<endl;
            if (n==0) n = n_aux;
            while(!ExisteMateria(Matriz,CodigoMateria,materias))
            {
                cout << " Ingrese el codigo de la materia "<<i+1<<": ";
                cin >> CodigoMateria;
                cout<<endl;
            }
            PosicionMateria = BuscarMateria(Matriz,CodigoMateria,materias);
            MateriasMatriculadas[P_M]=PosicionMateria;
            P_M++;
            Creditos_Acumulados+=ImportarCreditos(Matriz,PosicionMateria);
            if (Creditos_Acumulados>=CreditosMaximos)
            {
                cout<<"\t\t\t\t\t *****ALERTA: LIMITE DE CREDITOS EXCEDIDOS, NO PODRA REGISTAR MAS MATERIAS.*****"<<endl;
                break;
            }
            cout<<"\t\t\t\t\t\t\t La materia que matriculo es ";
            ImprimirNombreMateria(Matriz,PosicionMateria);
            cout<<endl<<"\t\t\t\t\t\t\t Usted lleva "<<Creditos_Acumulados<<" creditos matriculados."<<endl<<endl;
            cout << "\t\t\t\t\t\t ¿ Cuantas clases de esta materia  recibe a la semana ? : ";
            cin >> ClasesSemana;
            cout<<endl;
            j=0;
            while (j<ClasesSemana)
            {
                cout << "\t\t\t\t\t\t\t ¿ Que dia ve la clase "<<j+1<<" ?  : "<<endl<<endl;
                ImprimirDiasSemana();
                DiaClase = 0;
                while (DiaClase<=0 || DiaClase>7 )
                {
                    cout << "\t\t\t\t\t\t\t Ingrese una opcion : ";
                    cin >> DiaClase;
                    cout<<endl;
                }
                HoraInicio = 0;
                while (HoraInicio<6 || HoraInicio>20 )
                {
                    cout << "\t\t\t\t\t (Formato de 24 horas) ¿ A que horas inicia la clase ?  : ";
                    cin >> HoraInicio;
                    cout<<endl;
                }
                Horafinal = 0;
                while (Horafinal<8 || Horafinal>22 || Horafinal<HoraInicio )
                {
                    cout << "\t\t\t\t\t (Formato de 24 horas) ¿ A que horas finaliza la clase ?  : ";
                    cin >> Horafinal;
                    cout<<endl;
                }
                RegistrarClase(Matriz,Horario,DiaClase-1,HoraInicio,Horafinal,CodigoMateria,PosicionMateria);
                ImprimirHorario(Horario);
                j++;
            }
            i++;
        }

        cout<<endl;
        ImprimirHorario(Horario);
        ImprimirConenciones(Matriz,MateriasMatriculadas, n_aux);


       /*             PROGRAMAR HORAS DE ESTUDIO                            */
        cout<<endl;
        cout<<endl;
        LetreroHorasEstudio();
        cout<<endl;
        cout<<endl;
        int opcion_3;
        cout<<endl<<endl<<"\t\t\t\t\t\t 1. Asignar horas de estudio automaticamente."<<endl<<"\t\t\t\t\t\t 2. Asignar horas de estudio manualmente."<<endl<<endl<<"\t\t\t\t\t\t Seleccione una opcion: ";
        cin>>opcion_3;
        cout<<endl;
        while (opcion_3<1 || opcion_3>2)
        {
            cout<<"\t\t\t\t\t Opcion invalida. Seleccione una opcion: ";
            cin>>opcion_3;
            cout<<endl;
        }
        int* HorasLibres = new int[7];
        int *ClasesDia = new int[7];
        int HorasEstudio ;
        HorasEstudio = CalcularEstudioIndependiente(Matriz,MateriasMatriculadas,n_aux);
        if (opcion_3 == 1)
        {

            HorasClaseDia(Horario,ClasesDia);
            HorasLibresDia (Horario, HorasLibres);
            distribucionProporcional(HorasEstudio, HorasLibres, 7);
            if (ContarHoras(HorasLibres)>HorasEstudio)
                {
                    DisminuirHoras(HorasLibres,HorasEstudio);
                }
                else if (ContarHoras(HorasLibres)<HorasEstudio)
                {
                    AumentarHoras(HorasLibres,HorasEstudio);
                }
            HorasEstudioAutomatico(Matriz,Horario,MateriasMatriculadas,n_aux,HorasLibres,HorasEstudio);
        }
        else
        {
            HorasEstudioManual(Matriz,Horario,MateriasMatriculadas,n_aux,HorasEstudio);

        }
        delete[] HorasLibres;
        delete[] ClasesDia;
        DeleteBaseDatos (Matriz,materias);
        delete[] Tamano_materias;
        std::ofstream output_file(UserName, std::ofstream::out | std::ofstream::trunc);
        if (output_file) {
            for (int i = 0; i < 7; i++)
            {
                for (int j = 0; j < 24; j++)
                {
                    for (int k = 0; k < 8; k++)
                    {
                        output_file << Horario[i][j][k];
                    }
                }
            }
        } else
        {
          cout << "No se pudo crear el archivo '" << UserName << ".txt'.\n";
        }
        output_file.close();
        DeleteHorario(Horario);
        delete[] CodigoMateria;

    }
}
