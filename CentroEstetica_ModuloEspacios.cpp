#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>

struct Fecha
{
	int dd;
	int mm;
	int aaaa;
};

struct Usuarios
{
	char Usuario[10];
	char Contrasena[32];
	char ApellidoYNombre[60];
};

struct Profesionales
{
	char ApellidoyNombre[60];
	int IDProfesional;
	int DNIProfesional;
	char Telefono[25];
};

struct Cliente
{
	char ApellidoYNombre[60];
	char Domicilio[60];
	int DNIcliente;
	char Localidad[60];
	Fecha FechaDeNacimiento;
	float Peso;
	char Telefono[25];
};

struct Turnos
{
	int IdProfesional;
	Fecha FechaTurno;
	int DNIcliente;
	char DetalleDeAtencion[380];
	bool borrado;
};


int Menu()
{
	int opcion = 0;
	
	printf("Modulo Espacios");
	printf("\n=========================\n");
	printf("\n1.- Iniciar Sesion");
	printf("\n2.- Visualizar Lista de Espera de Turnos (informe)");
	printf("\n3.- Registrar Evolucion del Tratamiento");
	printf("\n");
	printf("\n4.- Cerrar Aplicacion");
	printf("\n\nIngrese una opcion: ");
	scanf("%d", &opcion);
	
	return opcion;
}

int ComprobarNombreDeUsuarioUnicoEnArchivoProfesionales(FILE *archirecep, Usuarios regi, char UsuarioActual[10], char ContrasenaTarget[32], char NombreYApellido[60], Profesionales pros); 
int ExtraerDNICliente(FILE *architurnos, int DiaActual, int MesActual, int AnoActual);								//PROTOTIPO DE FUNCIONES
void ExtraerNombreYApellidoCliente(FILE *archiclient, char ApellidoYNombre[60], int DNICLIENTE);
int ExtraerIDProfesional(FILE *architurnos, int DiaActual, int MesActual, int AnoActual);
void ExtraerNombreProfesional(FILE *archiprof, Usuarios regi, Profesionales pros, Turnos turno, int IDPRO, char ApyNom[60]);




void IniciarSesionProfesionales(FILE *archiprof)
{
	Usuarios profesionales;
	Profesionales pros;
	char NombreUsuario[10];
	char ContrasenaTrgt[32];
	strcpy(ContrasenaTrgt, "");
	char Contrasena[32];
	char ApellidoYNombre[60];
	int ComparacionUsuario;
	int ComparacionContrasena;
	
	
	archiprof = fopen("Profesionales.dat", "r+b");
	
	if (archiprof == NULL)
	{
		archiprof = fopen("Profesionales.dat", "w+b");				//Abrir archivo Profesionales.dat
		
		if (archiprof == NULL)
		{
			printf("Error. No se pudo crear el archivo");
			exit(1);
		}
	}
	
	printf("Ingrese su nombre de Usuario: ");
	_flushall();
	gets(NombreUsuario);
	ComparacionUsuario = ComprobarNombreDeUsuarioUnicoEnArchivoProfesionales(archiprof, profesionales, NombreUsuario, ContrasenaTrgt, ApellidoYNombre, pros);
	
	while(ComparacionUsuario == 0)
	{
		printf("\nNombre de Usuario Incorrecto");
		printf("\nIngrese su nombre de Usuario: ");
		_flushall();
		gets(NombreUsuario);
		ComparacionUsuario = ComprobarNombreDeUsuarioUnicoEnArchivoProfesionales(archiprof, profesionales, NombreUsuario, ContrasenaTrgt, ApellidoYNombre, pros);
	}
	
	printf("\nNombre de Usuario correcto\n\n");
	
	system("pause");
	system("cls");
	
	printf("Ingrese su contrasena: ");
	_flushall();
	gets(Contrasena);
	ComparacionContrasena = strcmp(Contrasena, ContrasenaTrgt);
	
	while(ComparacionContrasena != 0)
	{
		printf("\nContrasena Incorrecta");
		printf("\nIngrese su Contrasena: ");
		_flushall();
		gets(Contrasena);
		ComparacionContrasena = strcmp(Contrasena, ContrasenaTrgt);
	}
	printf("\nContrasena Valida\n\n");
	
	printf("Bienvenido al sistema %s", ApellidoYNombre);
	
	fclose(archiprof);
}

void VisualizarListaDeEsperDeTurnos(FILE *architurnos, FILE *archiclient, int DiaActual, int MesActual, int AnoActual, char NombreyApellido[60])
{
	Turnos turno;
	Cliente clientes;
	int DNICLIENTE;
	
	
	architurnos = fopen("Turnos.dat", "r+b");
	
	if (architurnos == NULL)
	{
		architurnos = fopen("Turnos.dat", "w+b");		//Apertura del archivo Turnos.dat
		
		if (architurnos == NULL)
		{
			printf("Error. No se pudo crear el archivo");
			exit(1);
		}
	}
	
	archiclient = fopen("Clientes.dat", "r+b");
	
	if (archiclient == NULL)
	{
		archiclient = fopen("Clientes.dat", "w+b");		//Apertura del archivo Clienets.dat
		
		if (archiclient == NULL)
		{
			printf("Error. No se pudo crear el archivo");
			exit(1);
		}
	}
	
	DNICLIENTE = ExtraerDNICliente(architurnos, DiaActual, MesActual, AnoActual);
	
	if(DNICLIENTE != 0)
	{
		ExtraerNombreYApellidoCliente(archiclient, NombreyApellido, DNICLIENTE);
	
		printf("\nEl cliente con turno en el dia (%d/%d/%d) es: %s", DiaActual, MesActual, AnoActual, NombreyApellido);
	}
	else
	{
		printf("\nNo hay un cliente con turno para esta fecha");
	}
	
	
	fclose(architurnos);
	fclose(archiclient);
	
}
	
void RegistrarEvolucionDeTratamiento(FILE *architurnos, FILE *archiclient, FILE *archiprof, char NombreyApellido[60], int DiaActual, int MesActual, int AnoActual)
{
	Turnos turno;
	Cliente clientes;
	Usuarios usuario;
	Profesionales pros;
	
	char ClienteActual[60];
	strcpy(ClienteActual, "");
	int Comparacion;
	int DNICLIENTE;
	int IDPRO = 0;
	
	architurnos = fopen("Turnos.dat", "r+b");
	
	if (architurnos == NULL)
	{
		architurnos = fopen("Turnos.dat", "w+b");		//Apertura del archivo Turnos.dat
		
		if (architurnos == NULL)
		{
			printf("Error. No se pudo crear el archivo");
			exit(1);
		}
	}
	
	archiclient = fopen("Clientes.dat", "r+b");
	
	if (archiclient == NULL)
	{
		archiclient = fopen("Clientes.dat", "w+b");		//Apertura del archivo Clienets.dat
		
		if (archiclient == NULL)
		{
			printf("Error. No se pudo crear el archivo");
			exit(1);
		}
	}
	
	archiprof = fopen("Profesionales.dat", "r+b");
	
	if (archiprof == NULL)
	{
		archiprof = fopen("Profesionales.dat", "w+b");				//Abrir archivo Profesionales.dat
		
		if (archiprof == NULL)
		{
			printf("Error. No se pudo crear el archivo");
			exit(1);
		}
	}
	
	
	printf("\nIngrese el nombre del cliente al que va a llamar para ser atendido: ");
	_flushall();
	gets(ClienteActual);
	
	Comparacion	= strcmp(ClienteActual, NombreyApellido);
	
	while(Comparacion != 0)
	{
		printf("\nNo existe un cliente con ese nombre para ser atendido en el dia de hoy");
		printf("\nIngrese el nombre del cliente al que va a llamar para ser atendido: ");
		_flushall();
		gets(ClienteActual);
		Comparacion	= strcmp(ClienteActual, NombreyApellido);
	}
	
	DNICLIENTE = ExtraerDNICliente(architurnos, DiaActual, MesActual, AnoActual);
	
	printf("\nCliente encontrado\n");
	
	system("pause"),
	system("cls");
	
	rewind(architurnos);
	
	fread(&turno, sizeof(turno), 1, architurnos);
	
	while( !feof(architurnos) )
	{
		if(DNICLIENTE == turno.DNIcliente)
		{
			printf("\nIngrese la evolucion del tratamiento: ");
			_flushall();
			gets(turno.DetalleDeAtencion);
			
			turno.borrado = true;
			
			fseek(architurnos, (long) -sizeof(turno), SEEK_CUR);
			fwrite(&turno, sizeof(turno), 1, architurnos);
			break;
		}
		fread(&turno, sizeof(turno), 1, architurnos);
	}
	
	
	printf("\n\n");
	system("pause");
	system("cls");
	
	strcpy(NombreyApellido, "");
	IDPRO =	ExtraerIDProfesional(architurnos, DiaActual, MesActual, AnoActual);
	
	ExtraerNombreProfesional(archiprof, usuario, pros, turno, IDPRO, NombreyApellido);
	
	
	
	printf("El profesional que atendio al cliente fue: %s\n", NombreyApellido);
	printf("\nla fecha de atencion fue: %d/%d/%d\n", DiaActual, MesActual, AnoActual);
	printf("\nEl redacto de la evolucion del tratamiento fue:\n");
	printf("%s", turno.DetalleDeAtencion);
	
	
	fclose(architurnos);
	fclose(archiclient);
	
}
	
	



main()
{	
	FILE *Profesionales;
	FILE *Turnos;
	FILE *Clientes;	
	
	int opc = 0;
	
	int DiaActualidad;
	int MesActualidad;
	int AnoActualidad;
	
	char NombreyApellido[60];
	
	
	
	printf("Bienvenido al sistema de Espacios\n\n");
	
	printf("Ingrese la fecha actual");
	printf("\ndd: ");
	scanf("%d", &DiaActualidad);
	printf("mm: ");
	scanf("%d", &MesActualidad);
	printf("aaaa: ");
	scanf("%d", &AnoActualidad);
	
	
	
	do 
	{
		system("cls");	
		opc = Menu();
		system("cls");	
		
		switch ( opc )
		{
			case 1: {
						printf("Inicio de sesion\n\n");
						IniciarSesionProfesionales(Profesionales);
						break;
					}
		
			case 2: {
						printf("Visualizar Lista de Espera de Turnos(Informe)\n");
						VisualizarListaDeEsperDeTurnos(Turnos, Clientes, DiaActualidad, MesActualidad, AnoActualidad, NombreyApellido);
						break;
					}

			case 3: {
						printf("Registrar Evolucion del Tratamiento\n");
						RegistrarEvolucionDeTratamiento(Turnos, Clientes, Profesionales, NombreyApellido, DiaActualidad, MesActualidad, AnoActualidad);
						break;
					}

			case 4: {
						printf("Saliendo de la Aplicacion");
						break;
					}

			default: {
						printf("Error. Opcion incorrecta...");
						break;
					}
			
		};
		
		printf("\n\n");
		system("pause");
	} while (opc != 4);
	
}


int ComprobarNombreDeUsuarioUnicoEnArchivoProfesionales(FILE *archiprof, Usuarios regi, char UsuarioActual[10], char ContrasenaTarget[32], char NombreYApellido[60], Profesionales pros)
{
	int comparacion;
	int Numero = 0;
	
	rewind(archiprof);
	
	fread(&regi, sizeof(regi), 1, archiprof);
	
	
	while( !feof(archiprof) )
	{
		comparacion = strcmp(regi.Usuario, UsuarioActual);
		
		if (comparacion == 0)
		{
			Numero++;
			strcpy(ContrasenaTarget, regi.Contrasena);
			strcpy(NombreYApellido, regi.ApellidoYNombre);
			
		}
		fread(&regi, sizeof(regi), 1, archiprof);
		
		
	}
	return Numero;
}

int ExtraerDNICliente(FILE *architurnos, int DiaActual, int MesActual, int AnoActual)
{
	Turnos turno;
	int DNICLIENTE;
	
	
	rewind(architurnos);
	
	fread(&turno, sizeof(turno), 1, architurnos);
	
	while( !feof(architurnos) )
	{
		if((turno.borrado == false && turno.FechaTurno.dd == DiaActual) && (turno.FechaTurno.mm == MesActual) && (turno.FechaTurno.aaaa == AnoActual))   //Extraer DNI del cliente 
		{																													   //Que tiene turno ese dia
			DNICLIENTE = turno.DNIcliente;
		}
		
		fread(&turno, sizeof(turno), 1, architurnos);
	}
	
	return DNICLIENTE;
}

void ExtraerNombreYApellidoCliente(FILE *archiclient, char ApellidoYNombre[60], int DNICLIENTE)
{
	Cliente clientes;
	
	rewind(archiclient);
	
	fread(&clientes, sizeof(clientes), 1, archiclient);
	
	while( !feof(archiclient) )
	{
		if(DNICLIENTE == clientes.DNIcliente)
		{
			strcpy(ApellidoYNombre, clientes.ApellidoYNombre);
		}
		
		fread(&clientes, sizeof(clientes), 1, archiclient);
	}
}

int ExtraerIDProfesional(FILE *architurnos, int DiaActual, int MesActual, int AnoActual)
{
	Turnos turno;
	int IDPROFESIONAL = 0;
	
	rewind(architurnos);
	
	fread(&turno, sizeof(turno), 1, architurnos);
	
	while ( !feof(architurnos) )
	{
		if((turno.borrado == false && turno.FechaTurno.dd == DiaActual) && (turno.FechaTurno.mm == MesActual) && (turno.FechaTurno.aaaa == AnoActual))
		{
			IDPROFESIONAL = turno.IdProfesional;
		}
		fread(&turno, sizeof(turno), 1, architurnos);
	}
	return IDPROFESIONAL;
}


void ExtraerNombreProfesional(FILE *archiprof, Usuarios regi, Profesionales pros, Turnos turno, int IDPRO, char ApyNom[60])
{
	rewind(archiprof);
	
	fread(&regi, sizeof(regi), 1, archiprof);
	fread(&pros, sizeof(pros), 1, archiprof);
	
	while( !feof(archiprof) )
	{
		if(IDPRO == pros.IDProfesional)
		{
			strcpy(ApyNom, pros.ApellidoyNombre);
		}
		fread(&regi, sizeof(regi), 1, archiprof);
		fread(&pros, sizeof(pros), 1, archiprof);
	}
}

//Este código fue realizado por Casanueva Facundo Gabriel; comisión 1K2
