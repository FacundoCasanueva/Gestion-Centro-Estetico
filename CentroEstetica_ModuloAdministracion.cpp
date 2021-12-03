#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>


struct Usuarios					//Sector del registro
{
	char Usuario[10];
	char Contrasena[32];
	char ApellidoYNombre[60];
};

int Menu()					//Funcion del menú
{
	int opcion = 0;
	
	printf("Modulo Administracion");
	printf("\n=========================\n");
	printf("\n1.- Registrar Profesional");
	printf("\n2.- Registrar Usuario Recepcionista");
	printf("\n3.- Atenciones por Profesional");
	printf("\n4.- Ranking de profesionales por Atenciones");
	printf("\n");
	printf("\n5.- Cerrar Aplicacion");
	printf("\n\nIngrese una opcion: ");
	scanf("%d", &opcion);
	
	return opcion;
}

bool VerificarNombreDeUsuario(Usuarios regi);
bool ComienzaMinuscula(Usuarios regi);
bool ContieneDosMayusculas(Usuarios regi);
bool ContieneMaximoTresDigitos(Usuarios regi);
int ComprobarNombreDeUsuarioUnico(FILE *archi, Usuarios regi, char UsuarioActual[10]);
															//Seccion de prototipos de funciones para la creacion del nuevo usuario
bool VerificarContrasenia(Usuarios regi);						
bool ContraseniaMayusculaMinusculaNumero(Usuarios regi);
bool ContraseniaSignosEspeciales(Usuarios regi);
bool TresNumerosConsecutivos(Usuarios regi);
bool DosLetrasConsecutivas(Usuarios regi);

void RegistrarProfesional(FILE *archi)		//Registrar Profesionales en el archivo
{
	Usuarios profesionales;
	int Comparacion;
	
	archi = fopen("Profesionales.dat", "r+b");
	
	if (archi == NULL)
	{
		archi = fopen("Profesionales.dat", "w+b");
		
		if (archi == NULL)
		{
			printf("Error. No se pudo crear el archivo");
			exit(1);
		}
	}
	
		
	printf("Ingrese el nombre de Usuario del nuevo Profesional: ");
	_flushall();
	gets(profesionales.Usuario);
	char NombreUsuarioActual[10];
	strcpy(NombreUsuarioActual, "");
	strcpy(NombreUsuarioActual, profesionales.Usuario);
	Comparacion = ComprobarNombreDeUsuarioUnico(archi, profesionales, NombreUsuarioActual);
	

	while(!VerificarNombreDeUsuario(profesionales) or (Comparacion!=0))
	{
			printf("Nombre de Usuario erroneo\n");
			printf("Un nombre de Usuario requiere lo siguiente: ");
			printf("\n\nDebe ser unico para cada profesional registrado");
			printf("\nDebe comenzar con una letra minuscula");
			printf("\nDebe contener al menos 2 letras mayusculas");
			printf("\nDebe contener como maximo 3 digitos");
			printf("\n\nIngrese un nuevo nombre de usuario: ");
			_flushall();
			gets(profesionales.Usuario);
			strcpy(NombreUsuarioActual, "");
			strcpy(NombreUsuarioActual, profesionales.Usuario);
			Comparacion = ComprobarNombreDeUsuarioUnico(archi, profesionales, NombreUsuarioActual);
		
			
	}
	
	
	
	printf("Nombre de Usuario valido...\n");
	
	system("pause");
	system("cls");
	
	printf("Ingrese la contrasena del Usuario: ");
	_flushall();
	gets(profesionales.Contrasena);

	while(!VerificarContrasenia(profesionales))
	{
		printf("\nContrasena erronea\n");
		printf("Una contrasena valida requiere lo siguiente: ");
		printf("\n\nDebe contener al menos una letra mayuscula, una minuscula y un digito (0 a 9)");
		printf("\nNo debe contener signos especiales, solo caracteres alfanumericos");
		printf("\nDebe contener entre 6 y 32 caracteres");
		printf("\nNo debe contener 3 numeros consecutivos");
		printf("\nNo debe contener 2 letras consecutivas alfabeticamente");
		printf("\n\nIngrese una nueva contrasena: ");
		_flushall();
		gets(profesionales.Contrasena);
	}
	
	printf("Contrasena valida...\n");
	
	system("pause");
	system("cls");
	
	printf("Ingrese Nombre y Apellido del profesional: ");
	_flushall();
	gets(profesionales.ApellidoYNombre);
	
	
	fseek(archi, 0, SEEK_END);
	fwrite(&profesionales, sizeof(profesionales), 1, archi);
	
	printf("Nuevo Profesional agregado exitosamente..");
	
	fclose(archi);
}

main()										//Función Main
{
	int opc = 0;
	FILE *Profesionales;
	FILE *Recepcionistas;
	
	
	
	do 
	{
		system("cls");	
		opc = Menu();
		system("cls");	
		
		switch ( opc )
		{
			case 1: {
						printf("Registrar Profesional\n\n");
						RegistrarProfesional(Profesionales);
						break;
					}
		
			case 2: {
						printf("Registrar Usuario Recepcionista\n");
						break;
					}

			case 3: {
						printf("Atenciones por Profesional\n");
						break;
					}

			case 4: {
						printf("Ranking de profesionales por Atenciones");
						break;
					}
					
			case 5: {
						printf("Saliendo de la Aplicacion");
						break;
					}
		/*			
			case 8: {
						printf("Listar\n\n");
						
						break;
					}
*/
			default: {
						printf("Error. Opcion incorrecta...");
						break;
					}
			
		};
		
		printf("\n\n");
		system("pause");
	} while (opc != 5);
	
	
	
}



																//Desarrollo de Funciones usadas
bool VerificarContrasenia(Usuarios regi)
{
	bool resultado = false;
	int longitudContra = strlen(regi.Contrasena);
	
	resultado = ContraseniaMayusculaMinusculaNumero(regi) && ContraseniaSignosEspeciales(regi) && TresNumerosConsecutivos(regi) && DosLetrasConsecutivas(regi) && ((longitudContra >= 6) && (longitudContra <= 32));

	return resultado;	
}

bool ContraseniaMayusculaMinusculaNumero(Usuarios regi)
{
	int longitudContra = strlen(regi.Contrasena);
	int i;
	bool MayusculaPresente = false;
	bool MinusculaPresente = false;
	bool DigitoPresente = false;
	
	for(i=0; i<longitudContra; i++)
	{
		if(isupper(regi.Contrasena[i]))
		{
			MayusculaPresente = true;
		}
		
		if(islower(regi.Contrasena[i]))
		{
			MinusculaPresente = true;	
		}
		
		if(isdigit(regi.Contrasena[i]))
		{
			DigitoPresente = true;
		}
	}
	if(MayusculaPresente && MinusculaPresente && DigitoPresente)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool ContraseniaSignosEspeciales(Usuarios regi)
{
	int longitudContra = strlen(regi.Contrasena);
	int i;
	
	for(i=0; i<longitudContra; i++)
	{
		if(!isalnum(regi.Contrasena[i]))
		{
			return false;
		}
	}
	return true;
}

bool TresNumerosConsecutivos(Usuarios regi)
{
	int longitudContra = strlen(regi.Contrasena);
	int i;
	
	for(i=0; i<longitudContra; i++)
	{
		if(isdigit(regi.Contrasena[i]) && isdigit(regi.Contrasena[i+1]) && isdigit(regi.Contrasena[i+2]))
		return false;
	}
	return true;
}

bool DosLetrasConsecutivas(Usuarios regi)
{
	int longitudContra = strlen(regi.Contrasena);
	char ContraMinuscula[32];
	strcpy(ContraMinuscula, regi.Contrasena);
	strlwr(ContraMinuscula);
	int i;
	
	for(i=0; i<longitudContra; i++)
	{
		if(ContraMinuscula[i] - ContraMinuscula[i-1] != 1)
		{
			return true;
		}
	}
	return false;
}

bool VerificarNombreDeUsuario(Usuarios regi)
{
	bool resultado = false;
	int longitudNombre = strlen(regi.Usuario);
	
	resultado = ComienzaMinuscula(regi) && ContieneDosMayusculas(regi) && ContieneMaximoTresDigitos(regi) && ((longitudNombre >=6) && (longitudNombre <= 10));
	
	return resultado;
}

bool ComienzaMinuscula(Usuarios regi)
{
	if(islower(regi.Usuario[0]))
	{
		return true;
	}
	return false;
}

bool ContieneDosMayusculas(Usuarios regi)
{
	int longitudNombre = strlen(regi.Usuario);
	int i;
	int CantidadMayusculas = 0;
	
	for(i=0; i<longitudNombre; i++)
	{
		if(isupper(regi.Usuario[i]))
		{
			CantidadMayusculas++;
		}
	}
	if(CantidadMayusculas >= 2)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool ContieneMaximoTresDigitos(Usuarios regi)
{
	int longitudNombre = strlen(regi.Usuario);
	int i;
	int CantidadDigitos = 0;
	
	for(i=0; i<longitudNombre; i++)
	{
		if(isdigit(regi.Usuario[i]))
		{
			CantidadDigitos++;
		}
	}
	
	if(CantidadDigitos <= 3)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int ComprobarNombreDeUsuarioUnico(FILE* archi, Usuarios regi, char UsuarioActual[10])
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
			
		}
		fread(&regi, sizeof(regi), 1, archi);
	}
	return Numero;
}

//Este código fue realizado por Casanueva Facundo Gabriel; comisión 1K2
