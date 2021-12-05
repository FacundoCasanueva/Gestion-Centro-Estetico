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


struct Usuarios					//Sector del registro
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

struct Turnos
{
	int IdProfesional;
	Fecha FechaTurno;
	int DNIcliente;
	char DetalleDeAtencion[380];
	bool borrado;
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
int ComprobarNombreDeUsuarioUnicoEnArchivoProfesionales(FILE *archiprof, Usuarios regi, char UsuarioActual[10], Profesionales pros);
int ComprobarNombreDeUsuarioUnicoEnArchivoRecepcionistas(FILE *archirecep, Usuarios regi, char UsuarioActual[10]);
															//Seccion de prototipos de funciones para la creacion del nuevo usuario
bool VerificarContrasenia(Usuarios regi);						
bool ContraseniaMayusculaMinusculaNumero(Usuarios regi);
bool ContraseniaSignosEspeciales(Usuarios regi);
bool TresNumerosConsecutivos(Usuarios regi);
bool DosLetrasConsecutivas(Usuarios regi);

int VerificarCuantosTurnosPorProfesional(FILE *architurnos, int IDACTUAL, int MesActual);




void RegistrarProfesional(FILE *archiprof, FILE *archirecep)		//Registrar Profesionales en el archivo Profesionales.dat
{
	Usuarios profesionales;
	Profesionales pros;
	int ComparacionProf;
	int ComparacionRecep;
	
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
	
	archirecep = fopen("Recepcionistas.dat", "r+b");
	
	if (archirecep == NULL)
	{	
		archirecep = fopen("Recepcionistas.dat", "w+b");		//Abrir archivo Recepcionistas.dat
		
		if (archirecep == NULL)
		{
			printf("Error. No se pudo crear el archivo");
			exit(1);
		}
	}
	
	
	
		
	printf("Ingrese el nombre de Usuario del nuevo Profesional: ");
	_flushall();
	gets(profesionales.Usuario);
	char NombreUsuarioProfesionalActual[10];
	strcpy(NombreUsuarioProfesionalActual, "");
	strcpy(NombreUsuarioProfesionalActual, profesionales.Usuario);
	ComparacionProf = ComprobarNombreDeUsuarioUnicoEnArchivoProfesionales(archiprof, profesionales, NombreUsuarioProfesionalActual, pros);     //Estas dos funciones comparan el nombre
	ComparacionRecep = ComprobarNombreDeUsuarioUnicoEnArchivoRecepcionistas(archirecep, profesionales, NombreUsuarioProfesionalActual);  //de usuario actual con otro nombre de usuraio
																																		 //en cualquiera de los dos archivos
	while(!VerificarNombreDeUsuario(profesionales) or (ComparacionProf!=0) or (ComparacionRecep!=0))
	{
			printf("\nNombre de Usuario erroneo\n");
			printf("Un nombre de Usuario requiere lo siguiente: ");
			printf("\n\nDebe ser unico para cada profesional registrado");
			printf("\nDebe comenzar con una letra minuscula");
			printf("\nDebe contener al menos 2 letras mayusculas");
			printf("\nDebe contener como maximo 3 digitos");
			printf("\n\nIngrese un nuevo nombre de usuario: ");
			_flushall();
			gets(profesionales.Usuario);
			strcpy(NombreUsuarioProfesionalActual, "");
			strcpy(NombreUsuarioProfesionalActual, profesionales.Usuario);
			ComparacionProf = ComprobarNombreDeUsuarioUnicoEnArchivoProfesionales(archiprof, profesionales, NombreUsuarioProfesionalActual, pros);
			ComparacionRecep = ComprobarNombreDeUsuarioUnicoEnArchivoRecepcionistas(archirecep, profesionales, NombreUsuarioProfesionalActual);
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
		printf("\nNo debe contener mas de 3 numeros consecutivos");
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
	strcpy(pros.ApellidoyNombre, profesionales.ApellidoYNombre);
	
	printf("Ingrese el ID del Profesional: ");
	scanf("%d", &pros.IDProfesional);
	
	printf("Ingrese el DNI del Profesional: ");
	scanf("%d", &pros.DNIProfesional);
	
	printf("Ingrese el telefono del Profesional: ");
	_flushall();
	gets(pros.Telefono);
	
	
	
	
	
	fseek(archiprof, 0, SEEK_END);
	fwrite(&profesionales, sizeof(profesionales), 1, archiprof);
	fwrite(&pros, sizeof(pros), 1, archiprof);
	
	printf("\nNuevo Profesional agregado exitosamente..");
	
	fclose(archiprof);
	fclose(archirecep);
}

void RegistrarRecepcionista(FILE *archirecep, FILE *archiprof)   //Registrar Recepcionistas en el archivo Recepcionistas.dat
{
	Usuarios recepcionistas;
	Profesionales pros;
	int ComparacionProf;
	int ComparacionRecep;
	
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
	
	
	printf("Ingrese el nombre de usuario del nuevo recepcionista: ");
	_flushall();
	gets(recepcionistas.Usuario);
	char NombreUsuarioRecepcionistaActual[10];
	strcpy(NombreUsuarioRecepcionistaActual, "");
	strcpy(NombreUsuarioRecepcionistaActual, recepcionistas.Usuario);
	ComparacionProf = ComprobarNombreDeUsuarioUnicoEnArchivoProfesionales(archiprof, recepcionistas, NombreUsuarioRecepcionistaActual, pros);		//Estas dos funciones comparan el
	ComparacionRecep = ComprobarNombreDeUsuarioUnicoEnArchivoRecepcionistas(archirecep, recepcionistas, NombreUsuarioRecepcionistaActual);  //Nombre de usuario actual con los
																															                //existentes en los archivos
	while(!VerificarNombreDeUsuario(recepcionistas) or (ComparacionProf!=0) or (ComparacionRecep !=0))
	{
			printf("Nombre de Usuario erroneo\n");
			printf("Un nombre de Usuario requiere lo siguiente: ");
			printf("\n\nDebe ser unico para cada profesional registrado");
			printf("\nDebe comenzar con una letra minuscula");
			printf("\nDebe contener al menos 2 letras mayusculas");
			printf("\nDebe contener como maximo 3 digitos");
			printf("\n\nIngrese un nuevo nombre de usuario: ");
			_flushall();
			gets(recepcionistas.Usuario);
			strcpy(NombreUsuarioRecepcionistaActual, "");
			strcpy(NombreUsuarioRecepcionistaActual, recepcionistas.Usuario);
			ComparacionProf = ComprobarNombreDeUsuarioUnicoEnArchivoProfesionales(archiprof, recepcionistas, NombreUsuarioRecepcionistaActual, pros);
			ComparacionRecep = ComprobarNombreDeUsuarioUnicoEnArchivoRecepcionistas(archirecep, recepcionistas, NombreUsuarioRecepcionistaActual);
	}
	
	
	
	printf("Nombre de Usuario valido...\n");
	
	system("pause");
	system("cls");
	
	printf("Ingrese la contrasena del Usuario: ");
	_flushall();
	gets(recepcionistas.Contrasena);

	while(!VerificarContrasenia(recepcionistas))
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
		gets(recepcionistas.Contrasena);
	}
	
	printf("Contrasena valida...\n");
	
	system("pause");
	system("cls");
	
	printf("Ingrese Nombre y Apellido del recepcionista: ");
	_flushall();
	gets(recepcionistas.ApellidoYNombre);
	
	
	fseek(archirecep, 0, SEEK_END);
	fwrite(&recepcionistas, sizeof(recepcionistas), 1, archirecep);
	
	printf("Nuevo recepcionista agregado exitosamente..");
	
	fclose(archirecep);
	fclose(archiprof);
	
}

void AtencionesPorProfesionalEnMesEnCurso(FILE *architurnos, int MesActual)
{
	Turnos turno;
	int IDACTUAL;
	int TurnosPorProfesional = 0;
	
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
	
	printf("Indique el ID del profesional del que se quiere visualizar los turnos realizados en el mes en curso: ");
	scanf("%d", &IDACTUAL);
	
	TurnosPorProfesional = VerificarCuantosTurnosPorProfesional(architurnos, IDACTUAL, MesActual);
	
	printf("La cantidad de Turnos realizados por el profesional de ID (%d) son: %d", IDACTUAL, TurnosPorProfesional);
	
	
	fclose(architurnos);
}





main()										//Función Main
{
	int opc = 0;
	FILE *Profesionales;
	FILE *Recepcionistas;
	FILE *Turnos;
	
	int DiaActualidad;
	int MesActualidad;
	int AnoActualidad;
	
	
	printf("Bienvenido al sistema de Administracion\n\n");
	
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
						printf("Registrar Profesional\n\n");
						RegistrarProfesional(Profesionales, Recepcionistas);
						break;
					}
		
			case 2: {
						printf("Registrar Usuario Recepcionista\n\n");
						RegistrarRecepcionista(Recepcionistas, Profesionales);
						break;
					}

			case 3: {
						printf("Atenciones por Profesional\n");
						AtencionesPorProfesionalEnMesEnCurso(Turnos, MesActualidad);
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
		if(isdigit(regi.Contrasena[i]) && isdigit(regi.Contrasena[i+1]) && isdigit(regi.Contrasena[i+2]) && isdigit(regi.Contrasena[i+3]))
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

int ComprobarNombreDeUsuarioUnicoEnArchivoProfesionales(FILE* archi, Usuarios regi, char UsuarioActual[10], Profesionales pros)
{
	int comparacion;
	int Numero = 0;
	
	rewind(archi);
	
	fread(&regi, sizeof(regi), 1, archi);
	fread(&pros, sizeof(pros), 1, archi);
	
	while( !feof(archi) )
	{
		comparacion = strcmp(regi.Usuario, UsuarioActual);
		
		if (comparacion == 0)
		{
			Numero++;
			
		}
		fread(&regi, sizeof(regi), 1, archi);
		fread(&pros, sizeof(pros), 1, archi);
	}
	return Numero;
}

int ComprobarNombreDeUsuarioUnicoEnArchivoRecepcionistas(FILE* archi, Usuarios regi, char UsuarioActual[10])
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

int VerificarCuantosTurnosPorProfesional(FILE *architurnos, int IDACTUAL, int MesActual)
{
	Turnos turno;
	int TurnosFinalizados;
	
	rewind(architurnos);
	
	fread(&turno, sizeof(turno), 1, architurnos);
	
	while( !feof(architurnos) )
	{
		if(turno.borrado == true && turno.FechaTurno.mm == MesActual && IDACTUAL == turno.IdProfesional)
		{
			TurnosFinalizados++;
		}
		fread(&turno, sizeof(turno), 1, architurnos);
	}
	
	
	return TurnosFinalizados;
}

//Este código fue realizado por Casanueva Facundo Gabriel; comisión 1K2
