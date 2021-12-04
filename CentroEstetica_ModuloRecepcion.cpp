#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>

struct Fecha
{
	int dd;
	int mm;
	int aaaa;
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
	Fecha Fechaactual;
	int DNIcliente;
	char DetalleDeAtencion[380];
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

int Menu()					//Funcion del menú
{
	int opcion = 0;
	
	printf("Modulo del recepcionista");
	printf("\n=========================\n");
	printf("\n1.- Iniciar Sesion");
	printf("\n2.- Registrar Cliente");
	printf("\n3.- Registrar Turno");
	printf("\n4.- Listado de atenciones por Profesional y Fecha");
	printf("\n");
	printf("\n5.- Cerrar Aplicacion");
	printf("\n\nIngrese una opcion: ");
	scanf("%d", &opcion);
	
	return opcion;
}

int ComprobarNombreDeUsuarioUnicoEnArchivoRecepcionistas(FILE *archirecep, Usuarios regi, char UsuarioActual[10], char ContrasenaTarget[32], char NombreYApellido[60]);
																																											//PROTOTIPO DE FUNCIONES

void IniciarSesionRecepcionista(FILE *archirecep) //Inicio de sesion
{
	Usuarios recepcionistas;
	char NombreUsuario[10];
	char ContrasenaTrgt[32];
	strcpy(ContrasenaTrgt, "");
	char Contrasena[32];
	char ApellidoYNombre[60];
	int ComparacionUsuario;
	int ComparacionContrasena;
	
	archirecep = fopen("Recepcionistas.dat", "r+b");
	
	if (archirecep == NULL)
	{
		archirecep = fopen("Recepcionistas.dat", "w+b");		//Apertura del archivo recepcionistas.dat
		
		if (archirecep == NULL)
		{
			printf("Error. No se pudo crear el archivo");
			exit(1);
		}
	}
	
	printf("Ingrese su Nombre de Usuario: ");
	_flushall();
	gets(NombreUsuario);	
	ComparacionUsuario = ComprobarNombreDeUsuarioUnicoEnArchivoRecepcionistas(archirecep, recepcionistas, NombreUsuario, ContrasenaTrgt, ApellidoYNombre);
	
	while(ComparacionUsuario == 0)
	{
		printf("\nNombre de Usuario Incorrecto");
		printf("\nIngrese su nombre de Usuario: ");
		_flushall();
		gets(NombreUsuario);
		ComparacionUsuario = ComprobarNombreDeUsuarioUnicoEnArchivoRecepcionistas(archirecep, recepcionistas, NombreUsuario, ContrasenaTrgt, ApellidoYNombre);
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
		printf("\nIngrese su contrasena: ");
		_flushall();
		gets(Contrasena);
		ComparacionContrasena = strcmp(Contrasena, ContrasenaTrgt);
	}
	printf("\nContrasena valida\n\n");
	
	
	printf("Bienvenido al sistema %s", ApellidoYNombre);	
}

void RegistrarClientes(FILE *archiclient)//Registro De Clientes
{
	Cliente clientes;
	
	archiclient = fopen("Clientes.dat", "r+b");
	
	if (archiclient == NULL)
	{
		archiclient = fopen("Clientes.dat", "w+b");		//Apertura del archivo recepcionistas.dat
		
		if (archiclient == NULL)
		{
			printf("Error. No se pudo crear el archivo");
			exit(1);
		}
	}
	
	printf("\nIngrese el Nombre y Apellido del cliente: ");
	_flushall();
	gets(clientes.ApellidoYNombre);
	
	printf("\nIngrese el Domicilio del Cliente: ");
	_flushall();
	gets(clientes.Domicilio);
	
	printf("\nIngrese el DNI del cliente (sin puntos): ");
	scanf("%d", &clientes.DNIcliente);
	
	printf("\nIngrese la localidad de residencia del Cliente: ");
	_flushall();
	gets(clientes.Localidad);
	
	printf("\nIngrese la fecha de naciemiento del cliente: ");
	printf("\ndd: ");
	scanf("%d", &clientes.FechaDeNacimiento.dd);
	printf("mm: ");
	scanf("%d", &clientes.FechaDeNacimiento.mm);
	printf("aaaa: ");
	scanf("%d", &clientes.FechaDeNacimiento.aaaa);
	
	printf("\nIngrese el peso del cliente: ");
	scanf("%f", &clientes.Peso);
	
	printf("\nIngrese el telefono del cliente: ");
	_flushall();
	gets(clientes.Telefono);
	
	fseek(archiclient, 0, SEEK_END);
	fwrite(&clientes, sizeof(clientes), 1, archiclient);
	
	fclose(archiclient);
}

void RegistrarTurnos(FILE *architurnos)
{
	Turnos turnos;
	
	architurnos = fopen("Turnos.dat", "r+b");
	
	if (architurnos == NULL)
	{
		architurnos = fopen("Turnos.dat", "w+b");		//Apertura del archivo recepcionistas.dat
		
		if (architurnos == NULL)
		{
			printf("Error. No se pudo crear el archivo");
			exit(1);
		}
	}
	
	
	
	
	
}



main()
{
	int opc = 0;
	FILE *Recepcionistas;
	FILE *Clientes;
	FILE *Turnos;
	
	
	do 
	{
		system("cls");	
		opc = Menu();
		system("cls");	
		
		switch ( opc )
		{
			case 1: {
						printf("Iniciar Sesion\n\n");
						IniciarSesionRecepcionista(Recepcionistas);
						break;
					}
		
			case 2: {
						printf("Registrar Cliente\n\n");
						RegistrarClientes(Clientes);
						break;
					}

			case 3: {
						printf("Registrar Turno\n\n");
						RegistrarTurnos(Turnos);
						break;
					}

			case 4: {
						printf("Listado de atenciones por Profesional y Fecha\n\n");
						break;
					}
					
			case 5: {
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
	} while (opc != 5);
}

int ComprobarNombreDeUsuarioUnicoEnArchivoRecepcionistas(FILE* archi, Usuarios regi, char UsuarioActual[10], char ContrasenaTarget[32], char NombreYApellido[60])
{
	int comparacion;
	int Numero = 0;
	
	rewind(archi);
	
	fread(&regi, sizeof(regi), 1, archi);
	
	while( !feof(archi) )
	{
		comparacion = strcmp(regi.Usuario, UsuarioActual);
		
		if (comparacion == 0)
		{
			Numero++;
			strcpy(ContrasenaTarget, regi.Contrasena);
			strcpy(NombreYApellido, regi.ApellidoYNombre);
			
		}
		fread(&regi, sizeof(regi), 1, archi);
	}
	return Numero;
}

int ComprobarIDProfesional(FILE *archi, Usuarios usu, Profesionales pros, int IDActual)
{
	
}









