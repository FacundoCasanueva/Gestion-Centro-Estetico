#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>

typedef char cadena[80];

struct Usuarios
{
	char Usuario[10];
	char Contrasena[32];
	char ApellidoYNombre[60];
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

void LeerNombreUsuario(FILE *archi, cadena Usuario, Usuarios regi);


void InicioDeSesion(FILE *archi)
{
	Usuarios regi;
	
	cadena NombreUsuario;
	cadena Contrasena;
		
	printf("Ingrese su nombre de usuario: ");
	_flushall();
	gets(NombreUsuario);
	
	LeerNombreUsuario(archi, NombreUsuario, regi);
	
	printf("Ingrese su contrasena: ");
	_flushall();
	gets(Contrasena);
	
	
	
	
	
}




main()
{	
	FILE *Profesionales;	
	
	int opc = 0;
	
	Profesionales = fopen("Profesionales.dat", "r+b");
	
	if (Profesionales == NULL)
	{
		Profesionales = fopen("Profesionales.dat", "w+b");
		
		if (Profesionales == NULL)
		{
			printf("Error. No se pudo crear el archivo");
			exit(1);
		}
	}
		
	do 
	{
		system("cls");	
		opc = Menu();
		system("cls");	
		
		switch ( opc )
		{
			case 1: {
						printf("Inicio de sesion\n\n");
						InicioDeSesion(Profesionales);
						break;
					}
		
			case 2: {
						printf("Visualizar Lista de Espera de Turnos(Informe)\n");
						break;
					}

			case 3: {
						printf("Registrar Evolucion del Tratamiento\n");
						
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


void LeerNombreUsuario(FILE *archi, cadena Usuario, Usuarios regi)
{
	rewind(archi);
	
	fread(&regi, sizeof(regi), 1, archi);
	
	while ( !feof(archi) )
	{
		while(Usuario != regi.Usuario)
		{
			printf("\nNo existe un profesional con ese nombre de usuario");
			printf("\nIngrese otro nombre de usuario: ");
			_flushall();
			gets(Usuario);
			
		}
		fread(&regi, sizeof(regi), 1, archi);
	}

}

