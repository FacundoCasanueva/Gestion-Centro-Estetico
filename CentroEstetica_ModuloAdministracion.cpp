#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>

struct Usuarios
{
	char Usuario[10];
	char Contrasena[32];
	char ApellidoYNombre[60];
};

int Menu()
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


void RegistrarProfesional(FILE *Profesionales)
{
	Usuarios profesionales;
	int longitudNombreUsuario;
	int longitudContrasena;
	int CantidadMayusculasNombreUsuario;
	int CantidadDigitosNombreUsuario;
	char cadenaMinuscula[32];
	int i = 0;
	int j = 0;
	int k = 0;
	int l = 0;
	int p = 0;
	int u = 0;
	
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
	
	
	printf("Ingrese nombre de usuario de nuevo profesional: ");
	_flushall();
	gets(profesionales.Usuario);
	longitudNombreUsuario = strlen(profesionales.Usuario);
	while((longitudNombreUsuario < 6) || (longitudNombreUsuario > 10))
	{
		printf("\nEl nombre de usuario debe contener entre 6 y 10 caracteres");
		printf("\nIngrese otro nombre de usuario: ");
		_flushall();
		gets(profesionales.Usuario);
		longitudNombreUsuario = strlen(profesionales.Usuario);
	}
	
	if(!islower(profesionales.Usuario[0]))
	{
		printf("\nEl nombre de usuario debe empezar con una letra minuscula");
		printf("\nIngrese otro nombre de usuario: ");
		_flushall();
		gets(profesionales.Usuario);
		longitudNombreUsuario = strlen(profesionales.Usuario);
	}
	
	
	while(profesionales.Usuario[i] != '\0')
	{
		if(isupper(profesionales.Usuario[i]))
		{
			CantidadMayusculasNombreUsuario++;
			
		}
	i++;
	}
	
	while(CantidadMayusculasNombreUsuario < 2)
	{
		printf("\nEl nombre de usuario debe tener al menos dos letras mayusculas");
		printf("\nIngrese otro nombre de usuario: ");
		_flushall();
		gets(profesionales.Usuario);
		longitudNombreUsuario = strlen(profesionales.Usuario);
		i = 0;
		
		while(profesionales.Usuario[i] != '\0')
		{
		if(isupper(profesionales.Usuario[i]))
		{
			CantidadMayusculasNombreUsuario++;
		}
		i++;
		}
	}
		
	while(profesionales.Usuario[j] != '\0')
	{
		if(isdigit(profesionales.Usuario[j]))
		{
			CantidadDigitosNombreUsuario++;
		}
	j++;
	}
	
	while(CantidadDigitosNombreUsuario > 3)
	{
		printf("\nEl nombre de usuario debe tener como maximo 3 digitos");
		printf("\nIngrese otro nombre de usuario: ");
		_flushall();
		gets(profesionales.Usuario);
		longitudNombreUsuario = strlen(profesionales.Usuario);
		j = 0;
		
		while(profesionales.Usuario[j] != '\0')
		{
			if(isdigit(profesionales.Usuario[j]))
			{
				CantidadDigitosNombreUsuario++;
			}
	j++;
		}
		
	}
	printf("\nNombre de usuario valido");
	
	
	printf("\nIngrese la contrasena del usuario: ");
	_flushall();
	gets(profesionales.Contrasena);
	longitudContrasena = strlen(profesionales.Contrasena);
	strcpy(cadenaMinuscula, profesionales.Contrasena);
	strlwr(cadenaMinuscula);
	
	while(cadenaMinuscula[k] != '\0')
	{
		if(cadenaMinuscula[k] == 97 && cadenaMinuscula[k+1] == 98) 
		{
			printf("La contrasena no puede tener dos letras consecutivas ascendentemente");
			printf("\nIngrese otra contrasena: ");
			_flushall();
			gets(profesionales.Contrasena);
			strcpy(cadenaMinuscula, profesionales.Contrasena);
			strlwr(cadenaMinuscula);
			longitudContrasena = strlen(profesionales.Contrasena);
		}
		else
		{
			break;
		}
		if(cadenaMinuscula[k] == 98 && cadenaMinuscula[k+1] == 99) 
		{
			printf("La contrasena no puede tener dos letras consecutivas ascendentemente");
			printf("\nIngrese otra contrasena: ");
			_flushall();
			gets(profesionales.Contrasena);
			strcpy(cadenaMinuscula, profesionales.Contrasena);
			strlwr(cadenaMinuscula);
			longitudContrasena = strlen(profesionales.Contrasena);
		}
		if(cadenaMinuscula[k] == 99 && cadenaMinuscula[k+1] == 100) 
		{
			printf("La contrasena no puede tener dos letras consecutivas ascendentemente");
			printf("\nIngrese otra contrasena: ");
			_flushall();
			gets(profesionales.Contrasena);
			strcpy(cadenaMinuscula, profesionales.Contrasena);
			strlwr(cadenaMinuscula);
			longitudContrasena = strlen(profesionales.Contrasena);
		}
		if(cadenaMinuscula[k] == 100 && cadenaMinuscula[k+1] == 101) 
		{
			printf("La contrasena no puede tener dos letras consecutivas ascendentemente");
			printf("\nIngrese otra contrasena: ");
			_flushall();
			gets(profesionales.Contrasena);
			strcpy(cadenaMinuscula, profesionales.Contrasena);
			strlwr(cadenaMinuscula);
			longitudContrasena = strlen(profesionales.Contrasena);
		}
		if(cadenaMinuscula[k] == 101 && cadenaMinuscula[k+1] == 102) 
		{
			printf("La contrasena no puede tener dos letras consecutivas ascendentemente");
			printf("\nIngrese otra contrasena: ");
			_flushall();
			gets(profesionales.Contrasena);
			strcpy(cadenaMinuscula, profesionales.Contrasena);
			strlwr(cadenaMinuscula);
			longitudContrasena = strlen(profesionales.Contrasena);
		}
		if(cadenaMinuscula[k] == 102 && cadenaMinuscula[k+1] == 103) 
		{
			printf("La contrasena no puede tener dos letras consecutivas ascendentemente");
			printf("\nIngrese otra contrasena: ");
			_flushall();
			gets(profesionales.Contrasena);
			strcpy(cadenaMinuscula, profesionales.Contrasena);
			strlwr(cadenaMinuscula);
			longitudContrasena = strlen(profesionales.Contrasena);
		}
		if(cadenaMinuscula[k] == 103 && cadenaMinuscula[k+1] == 104) 
		{
			printf("La contrasena no puede tener dos letras consecutivas ascendentemente");
			printf("\nIngrese otra contrasena: ");
			_flushall();
			gets(profesionales.Contrasena);
			strcpy(cadenaMinuscula, profesionales.Contrasena);
			strlwr(cadenaMinuscula);
			longitudContrasena = strlen(profesionales.Contrasena);
		}
		if(cadenaMinuscula[k] == 104 && cadenaMinuscula[k+1] == 105) 
		{
			printf("La contrasena no puede tener dos letras consecutivas ascendentemente");
			printf("\nIngrese otra contrasena: ");
			_flushall();
			gets(profesionales.Contrasena);
			strcpy(cadenaMinuscula, profesionales.Contrasena);
			strlwr(cadenaMinuscula);
			longitudContrasena = strlen(profesionales.Contrasena);
		}
		if(cadenaMinuscula[k] == 105 && cadenaMinuscula[k+1] == 106) 
		{
			printf("La contrasena no puede tener dos letras consecutivas ascendentemente");
			printf("\nIngrese otra contrasena: ");
			_flushall();
			gets(profesionales.Contrasena);
			strcpy(cadenaMinuscula, profesionales.Contrasena);
			strlwr(cadenaMinuscula);
			longitudContrasena = strlen(profesionales.Contrasena);
		}
		if(cadenaMinuscula[k] == 106 && cadenaMinuscula[k+1] == 107) 
		{
			printf("La contrasena no puede tener dos letras consecutivas ascendentemente");
			printf("\nIngrese otra contrasena: ");
			_flushall();
			gets(profesionales.Contrasena);
			strcpy(cadenaMinuscula, profesionales.Contrasena);
			strlwr(cadenaMinuscula);
			longitudContrasena = strlen(profesionales.Contrasena);
		}
		if(cadenaMinuscula[k] == 107 && cadenaMinuscula[k+1] == 108) 
		{
			printf("La contrasena no puede tener dos letras consecutivas ascendentemente");
			printf("\nIngrese otra contrasena: ");
			_flushall();
			gets(profesionales.Contrasena);
			strcpy(cadenaMinuscula, profesionales.Contrasena);
			strlwr(cadenaMinuscula);
			longitudContrasena = strlen(profesionales.Contrasena);
		}
		if(cadenaMinuscula[k] == 108 && cadenaMinuscula[k+1] == 109) 
		{
			printf("La contrasena no puede tener dos letras consecutivas ascendentemente");
			printf("\nIngrese otra contrasena: ");
			_flushall();
			gets(profesionales.Contrasena);
			strcpy(cadenaMinuscula, profesionales.Contrasena);
			strlwr(cadenaMinuscula);
			longitudContrasena = strlen(profesionales.Contrasena);
		}
		if(cadenaMinuscula[k] == 109 && cadenaMinuscula[k+1] == 110) 
		{
			printf("La contrasena no puede tener dos letras consecutivas ascendentemente");
			printf("\nIngrese otra contrasena: ");
			_flushall();
			gets(profesionales.Contrasena);
			strcpy(cadenaMinuscula, profesionales.Contrasena);
			strlwr(cadenaMinuscula);
			longitudContrasena = strlen(profesionales.Contrasena);
		}
		if(cadenaMinuscula[k] == 110 && cadenaMinuscula[k+1] == 111) 
		{
			printf("La contrasena no puede tener dos letras consecutivas ascendentemente");
			printf("\nIngrese otra contrasena: ");
			_flushall();
			gets(profesionales.Contrasena);
			strcpy(cadenaMinuscula, profesionales.Contrasena);
			strlwr(cadenaMinuscula);
			longitudContrasena = strlen(profesionales.Contrasena);
		}
		if(cadenaMinuscula[k] == 111 && cadenaMinuscula[k+1] == 112) 
		{
			printf("La contrasena no puede tener dos letras consecutivas ascendentemente");
			printf("\nIngrese otra contrasena: ");
			_flushall();
			gets(profesionales.Contrasena);
			strcpy(cadenaMinuscula, profesionales.Contrasena);
			strlwr(cadenaMinuscula);
			longitudContrasena = strlen(profesionales.Contrasena);
		}
		if(cadenaMinuscula[k] == 112 && cadenaMinuscula[k+1] == 113) 
		{
			printf("La contrasena no puede tener dos letras consecutivas ascendentemente");
			printf("\nIngrese otra contrasena: ");
			_flushall();
			gets(profesionales.Contrasena);
			strcpy(cadenaMinuscula, profesionales.Contrasena);
			strlwr(cadenaMinuscula);
			longitudContrasena = strlen(profesionales.Contrasena);
		}
		if(cadenaMinuscula[k] == 113 && cadenaMinuscula[k+1] == 114) 
		{
			printf("La contrasena no puede tener dos letras consecutivas ascendentemente");
			printf("\nIngrese otra contrasena: ");
			_flushall();
			gets(profesionales.Contrasena);
			strcpy(cadenaMinuscula, profesionales.Contrasena);
			strlwr(cadenaMinuscula);
			longitudContrasena = strlen(profesionales.Contrasena);
		}
		if(cadenaMinuscula[k] == 114 && cadenaMinuscula[k+1] == 115) 
		{
			printf("La contrasena no puede tener dos letras consecutivas ascendentemente");
			printf("\nIngrese otra contrasena: ");
			_flushall();
			gets(profesionales.Contrasena);
			strcpy(cadenaMinuscula, profesionales.Contrasena);
			strlwr(cadenaMinuscula);
			longitudContrasena = strlen(profesionales.Contrasena);
		}
		if(cadenaMinuscula[k] == 115 && cadenaMinuscula[k+1] == 116) 
		{
			printf("La contrasena no puede tener dos letras consecutivas ascendentemente");
			printf("\nIngrese otra contrasena: ");
			_flushall();
			gets(profesionales.Contrasena);
			strcpy(cadenaMinuscula, profesionales.Contrasena);
			strlwr(cadenaMinuscula);
			longitudContrasena = strlen(profesionales.Contrasena);
		}
		if(cadenaMinuscula[k] == 116 && cadenaMinuscula[k+1] == 117) 
		{
			printf("La contrasena no puede tener dos letras consecutivas ascendentemente");
			printf("\nIngrese otra contrasena: ");
			_flushall();
			gets(profesionales.Contrasena);
			strcpy(cadenaMinuscula, profesionales.Contrasena);
			strlwr(cadenaMinuscula);
			longitudContrasena = strlen(profesionales.Contrasena);
		}
		if(cadenaMinuscula[k] == 117 && cadenaMinuscula[k+1] == 118) 
		{
			printf("La contrasena no puede tener dos letras consecutivas ascendentemente");
			printf("\nIngrese otra contrasena: ");
			_flushall();
			gets(profesionales.Contrasena);
			strcpy(cadenaMinuscula, profesionales.Contrasena);
			strlwr(cadenaMinuscula);
			longitudContrasena = strlen(profesionales.Contrasena);
		}
		if(cadenaMinuscula[k] == 118 && cadenaMinuscula[k+1] == 119) 
		{
			printf("La contrasena no puede tener dos letras consecutivas ascendentemente");
			printf("\nIngrese otra contrasena: ");
			_flushall();
			gets(profesionales.Contrasena);
			strcpy(cadenaMinuscula, profesionales.Contrasena);
			strlwr(cadenaMinuscula);
			longitudContrasena = strlen(profesionales.Contrasena);
		}
		if(cadenaMinuscula[k] == 119 && cadenaMinuscula[k+1] == 120) 
		{
			printf("La contrasena no puede tener dos letras consecutivas ascendentemente");
			printf("\nIngrese otra contrasena: ");
			_flushall();
			gets(profesionales.Contrasena);
			strcpy(cadenaMinuscula, profesionales.Contrasena);
			strlwr(cadenaMinuscula);
			longitudContrasena = strlen(profesionales.Contrasena);
		}
		if(cadenaMinuscula[k] == 120 && cadenaMinuscula[k+1] == 121) 
		{
			printf("La contrasena no puede tener dos letras consecutivas ascendentemente");
			printf("\nIngrese otra contrasena: ");
			_flushall();
			gets(profesionales.Contrasena);
			strcpy(cadenaMinuscula, profesionales.Contrasena);
			strlwr(cadenaMinuscula);
			longitudContrasena = strlen(profesionales.Contrasena);
		}
		if(cadenaMinuscula[k] == 121 && cadenaMinuscula[k+1] == 122) 
		{
			printf("La contrasena no puede tener dos letras consecutivas ascendentemente");
			printf("\nIngrese otra contrasena: ");
			_flushall();
			gets(profesionales.Contrasena);
			strcpy(cadenaMinuscula, profesionales.Contrasena);
			strlwr(cadenaMinuscula);
			longitudContrasena = strlen(profesionales.Contrasena);
		}
	}
	
	while(profesionales.Contrasena[l] != '\0')
	{
		while(isdigit(profesionales.Contrasena[l]) && isdigit(profesionales.Contrasena[l+1]) && isdigit(profesionales.Contrasena[l+2] && isdigit(profesionales.Contrasena[l+3])))
		{
			printf("\nLa contrasena no puede contener mas de 3 digitos consecutivos");
			printf("\nIngrese otra contrasena: ");
			_flushall();
			gets(profesionales.Contrasena);
			longitudContrasena = strlen(profesionales.Contrasena);
			l = 0;
		}
		l++;	
	}
	
	while((longitudContrasena < 6) || (longitudContrasena > 32))
	{
		printf("\nLa contrasena debe contener entre 6 y 32 caracteres");
		printf("\nIngrese otra contrasena: ");
		_flushall();
		gets(profesionales.Contrasena);
		longitudContrasena = strlen(profesionales.Contrasena);

	}
	
	while(profesionales.Contrasena[p] != '\0')
	{
		while(!isalnum(profesionales.Contrasena[p]))
		{
			printf("\nLa contrasena no puede contener digitos no alfa-numericos");
			printf("\nIngrese otra contrasena: ");
			_flushall();
			gets(profesionales.Contrasena);
			longitudContrasena = strlen(profesionales.Contrasena);
			p++;
		}
	}
	
	while(profesionales.Contrasena[u] != '\0')
	{
		if(!isupper(profesionales.Contrasena[u]))
		{
			printf("\nLa contrasena debe contener al menos una mayuscula");
			printf("\nIngrese otra contrasena: ");
			_flushall();
			gets(profesionales.Contrasena);
			longitudContrasena = strlen(profesionales.Contrasena);
			u++;
		}
		
	}
	
	
	fseek(Profesionales,0,SEEK_END);
	fwrite(&profesionales, sizeof(profesionales),1,Profesionales);
	
	
	fclose(Profesionales);
}

main()
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

			default: {
						printf("Error. Opcion incorrecta...");
						break;
					}
			
		};
		
		printf("\n\n");
		system("pause");
	} while (opc != 5);
}
