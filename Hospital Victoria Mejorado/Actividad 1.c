/*
	*********************LISTAS ENCADENADAS***********************
	Materia: ESTRUCTURA DE DATOS
	Actividad 1: IMPLEMENTAR LISTAS ENCADENADAS A PIA DE PROGRAMACION ESTRUCTURADA
	Grupo: 6
	Integrantes del equpo:
		.- Brayan Adrian Montoya Morales 1847284
		.- Alberto Carlos Almaguer Rodriguez 1877448
		.- Eduardo Alán Hernández Villasana 1941416
		.- Ian Mauricio Saucedo Aleman 1868954
		.- Susana Enriquez Godina 1841762
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <windows.h>
int nDoc=0,nPac=0,nPai=0,nCon=0;// nDoc,nPac y nPai guardan la ultima posicion de su arreglo de estructuras correspondiente
struct Doctores
{
	int id;
	char nombre [80];
	char especialidad[80];
	char email[80];
	char tel[80];
	unsigned int tarifa;
	int disponible;//1 es disponible, 0 no disponible, esta informacion no esta en el archivo, se utiliza para facilitar algunos procesos
	struct Doctores *siguiente_doctor;
}; //*Doc;//Las estructuras se guardaron como punteros, para 
typedef struct Doctores DOC;
typedef DOC *DOCSIG;
struct Paciente_Consulta
{
	int id;
	char nombre [80];
	char tel[80];
	char email[80];
	unsigned int nss;//Numero de seguro social
	char desc_enf[100];//Descripcion de la enfermedad
	struct Paciente_Consulta *siguiente_pac;
}; //*Pac;
typedef struct Paciente_Consulta PAC;
typedef PAC *PACSIG;
struct Paciente_Ingreso
{
	int id;
	char nombre [80];
	char tel[80];
	char email[80];
	unsigned int nss;//Numero de seguro social
	char enfermedad[80];
	int habitacion;
	char desc_enf[100];//Descripcion de la enfermedad
	struct Paciente_Ingreso *siguiente_pai;
};//*Pai;
typedef struct Paciente_Ingreso PAI;
typedef PAI *PAISIG;
struct Consultorio
{
	int id;
	int clave;
	long id_Doc;
	long id_Pac;
	struct Consultorio *siguiente_con;
};//*Con;
typedef struct Consultorio CON;
typedef CON *CONSIG;
int leer_Doc (DOCSIG *Doc) // LISTA IMPLEMENTADA	EXCELL IMPLEMENTADO
{
	DOCSIG nuevo, previo, actual;
	char c;
	char aux[80];
	int ba=0,i=0,j=0,k;
	FILE *fdoc=fopen("DOCTOR.xls","rb");/////////
	c=fgetc(fdoc);/////////
	nuevo = malloc(sizeof (DOC));
	while (c!=EOF)
	{
		if (c=='\n')//Si hay un enter, cambiara de posicion del arreglo de estructura
		{
			//Doc=(struct Doctores*) realloc(Doc,(j+2)*sizeof( *Doc)); //Aumenta 1 de casillas
			
			nuevo->siguiente_doctor = NULL;
			previo = NULL;
			actual = *Doc;
			while (actual != NULL)
			{
				previo = actual;
				actual = actual->siguiente_doctor;
			}
			if (previo == NULL)
			{
				nuevo->siguiente_doctor = *Doc;
				*Doc = nuevo;
			}
			else 
			{
				previo->siguiente_doctor = nuevo;
				nuevo->siguiente_doctor = actual;
			}
			j++;
			ba=0;
			nuevo = malloc(sizeof (DOC));
		}
		else
		{
			if (c=='\t')
			{
				i=0;
				switch (ba)// ba hace referencia es el tipo de dato de la estructura que se esta leyendo
				{
					case 0:
						nuevo->id=atoi(aux);
						break;
					case 1:
						strcpy(nuevo->nombre,aux);
						break;
					case 2:
						strcpy(nuevo->especialidad,aux);
						break;
					case 3:
						strcpy(nuevo->email,aux);
						break;
					case 4:
						strcpy(nuevo->tel,aux);
						break;
					case 5:
						nuevo->tarifa=atoi(aux);
						break;																								
				}
				for (k=0;k<sizeof(aux);k++)
				{
					aux[k]='\0';
				}
				ba++;
			}
			else if (c!='\r')
			{
				aux[i]=c;
				i++;
			}
		}
		c=fgetc(fdoc);
	}
	fclose(fdoc);
	return j;
}
int leer_Pac (PACSIG *Pac) // LISTA IMPLEMENTADA	EXCELL IMPLEMENTADO
{
	PACSIG nuevo, previo, actual;
	char c;
	char aux[100];
	int ba=0,i=0,j=0,k;
	FILE *fpac=fopen("PACIENTECONSULTA.xls","rb");/////////
	c=fgetc(fpac);/////////
	nuevo = malloc(sizeof (PAC));
	while (c!=EOF)
	{
		if (c=='\n')//Si hay un enter, cambiara de posicion del arreglo de estructura
		{
			//Pac=(struct Paciente_Consulta*) realloc(Pac,(j+2)*sizeof( *Pac)); //Aumenta 1 de casillas
			
			nuevo->siguiente_pac = NULL;
			previo = NULL;
			actual = *Pac;
			while (actual != NULL)
			{
				previo = actual;
				actual = actual->siguiente_pac;
			}
			if (previo == NULL) 
		  	{
				nuevo->siguiente_pac = *Pac;
				*Pac = nuevo;
		  	}
			else 
		  	{
				previo->siguiente_pac = nuevo;
				nuevo->siguiente_pac= actual;
		  	}
			j++;
			nuevo = malloc(sizeof (PAC));
			ba=0;
		}
		else
		{
			if (c=='\t')
			{
				i=0;
				switch (ba)// ba hace referencia es el tipo de dato de la estructura que se esta leyendo
				{
					case 0:
						nuevo->id=atoi(aux);
						break;
					case 1:
						strcpy(nuevo->nombre,aux);
						break;
					case 2:
						strcpy(nuevo->tel,aux);
						break;
					case 3:
						strcpy(nuevo->email,aux);
						break;
					case 4:
						nuevo->nss=atoi(aux);
						break;
					case 5:
						strcpy(nuevo->desc_enf,aux);
						break;																								
				}
				for (k=0;k<sizeof(aux);k++)
				{
					aux[k]='\0';
				}
				ba++;
			}
			else if (c!='\r')
			{
				aux[i]=c;
				i++;
			}
		}
		c=fgetc(fpac);
	}
	fclose(fpac);
	return j;
}
int leer_Pai (PAISIG *Pai) // LISTA IMPLEMENTADA	EXCELL IMPLEMENTADO
{
	char c;
	char aux[80];
	int ba=0,i=0,j=0,k;
	FILE *fpai=fopen("PACIENTEINGRESO.xls","rb");/////////
	c=fgetc(fpai);/////////
	PAISIG nuevo, previo, actual;
	nuevo = malloc(sizeof (PAI));
	while (c!=EOF)
	{
		if (c=='\n')//Si hay un enter, cambiara de posicion del arreglo de estructura
		{	
			
			//Pai=(struct Paciente_Ingreso*) realloc(Pai,(j+2)*sizeof( *Pai)); //Aumenta 1 de casillas
			nuevo->siguiente_pai = NULL;
			previo = NULL;
			actual = *Pai;
			while (actual != NULL)
			{
				previo = actual;
				actual = actual->siguiente_pai;
			}
			if (previo == NULL) 
		  	{
				nuevo->siguiente_pai = *Pai;
				*Pai = nuevo;
		  	}
			else 
		  	{
				previo->siguiente_pai = nuevo;
				nuevo->siguiente_pai = actual;
		  	}			
			j++;
			nuevo = malloc(sizeof (PAI));
			ba=0;
		}
		else
		{
			if (c=='\t')
			{
				i=0;
				switch (ba)// ba hace referencia es el tipo de dato de la estructura que se esta leyendo
				{
					case 0:
						nuevo->id=atoi(aux);
						break;
					case 1:
						strcpy(nuevo->nombre,aux);
						break;
					case 2:
						strcpy(nuevo->tel,aux);
						break;
					case 3:
						strcpy(nuevo->email,aux);
						break;
					case 4:
						nuevo->nss=atoi(aux);
						break;
					case 5:
						strcpy(nuevo->enfermedad,aux);
						break;
					case 6:
						nuevo->habitacion=atoi(aux);
						break;
					case 7:
						strcpy(nuevo->desc_enf,aux);
						break;																							
				}
				for (k=0;k<sizeof(aux);k++)
				{
					aux[k]='\0';
				}
				ba++;
			}
			else if (c!='\r')
			{
				aux[i]=c;
				i++;
			}
		}
		c=fgetc(fpai);
	}
	fclose(fpai);
	return j;
}
int leer_Con (CONSIG *Con, DOCSIG *Doc) // LISTA IMPLEMENTADA	EXCELL IMPLEMENTADO
{
	DOCSIG auxi;
	CONSIG nuevo, previo, actual;
	auxi = *Doc;
	char c;
	char aux[80];
	int ba=0,i=0,j=0,k,m;
	while (auxi != NULL) // Todos los doctores como disponibles
	{
		auxi->disponible = 1;
		auxi = auxi->siguiente_doctor;
	}
	FILE *fcon=fopen("CONSULTORIO.xls","rb");/////////
	c=fgetc(fcon);/////////
	nuevo = malloc(sizeof (CON));
	while (c!=EOF)
	{
		if (c=='\n')//Si hay un enter, cambiara de posicion del arreglo de estructura
		{
			//Con=(struct Consultorio*) realloc(Con,(j+2)*sizeof( *Con)); //Aumenta 1 de casillas
			nuevo->siguiente_con = NULL;
			previo = NULL;
			actual = *Con;
			while (actual != NULL)
			{
				previo = actual;
				actual = actual->siguiente_con;
			}
			if (previo == NULL) 
		  	{
				nuevo->siguiente_con = *Con;
				*Con = nuevo;
		  	}
			else 
		  	{
				previo->siguiente_con = nuevo;
				nuevo->siguiente_con = actual;
		  	}			
			j++;
			nuevo = malloc(sizeof (CON));
			ba=0;
		}
		else
		{
			if (c=='\t')
			{
				i=0;
				switch (ba)// ba hace referencia es el tipo de dato de la estructura que se esta leyendo
				{
					case 0:
						nuevo->id=atoi(aux);
						break;
					case 1:
						nuevo->clave=atoi(aux);
						break;
					case 2:
						nuevo->id_Doc=atoi(aux);
						if (nuevo->id_Doc!=0)
						{
							auxi = *Doc;
							while (auxi != NULL)
							{
								if (auxi->id == nuevo->id_Doc)
								{
									auxi->disponible = 0;
								}
								auxi = auxi->siguiente_doctor;
							}
						}
						break;
					case 3:
						nuevo->id_Pac=atoi(aux);
						break;																								
				}
				for (k=0;k<sizeof(aux);k++)
				{
					aux[k]='\0';
				}
				ba++;
			}
			else if (c!='\r')
			{
				aux[i]=c;
				i++;
			}
		}
		c=fgetc(fcon);
	}
	fclose(fcon);
	return j;
}
int menu ()
{
	int m;
	do
	{
		system ("cls");
		printf ("****HOSPITAL VICTORIA****\nOpciones.-\n1) Doctor\n2) Consulta General\n3) Ingreso\n4) Cuenta\n5) Busquedas\n6) Salir\n");
		scanf ("%d",&m);
		if (m<1||m>6)
		{
			printf ("Eliga una opcion valida...\n");
			Sleep(500);
		}
		system ("cls");
	}while (m<1||m>6);
	return m;
}
void nuevo_Doctor (int nDOC, DOCSIG *Doc) // LISTA IMPLEMENTADA	EXCELL IMPLEMENTADO
{
	DOCSIG nuevo, previo, actual;
	nuevo = malloc(sizeof(DOC));
	system ("cls");
	FILE *fdoc=fopen("DOCTOR.xls","a");
	fflush (stdin);
	printf ("Ingresa el nombre del doctor\n");
	scanf ("%[^\n]",nuevo->nombre);
	fflush(stdin);
	printf ("Ingresa la especialidad del doctor\n");
	scanf ("%[^\n]",nuevo->especialidad);
	fflush(stdin);
	printf ("Ingrese el correo electronico del doctor\n");
	scanf ("%[^\n]",nuevo->email);
	fflush(stdin);
	printf ("Ingrese el numero telefonico del doctor\n");
	scanf ("%[^\n]",nuevo->tel);
	fflush(stdin);
	printf ("Ingrese la tarifa por consulta del doctor\n");
	scanf ("%d",&nuevo->tarifa);
	fflush(stdin);
	nuevo->id=nDoc+1;
//	Doc=(struct Doctores*) realloc(Doc,(nDoc+2)*sizeof( *Doc));
	fprintf(fdoc,"%d\t%s\t%s\t%s\t%s\t%d\t\n",nDoc+1,nuevo->nombre,nuevo->especialidad,nuevo->email,nuevo->tel,nuevo->tarifa);
	fclose (fdoc);
	nuevo->siguiente_doctor = NULL;
	previo = NULL;
	actual = *Doc;
	while (actual != NULL)
	{
		previo = actual;
		actual = actual->siguiente_doctor;
	}
	if (previo == NULL)
	{
		nuevo->siguiente_doctor = *Doc;
		*Doc = nuevo;
	}
	else 
	{
		previo->siguiente_doctor = nuevo;
		nuevo->siguiente_doctor = actual;
	}
	
}
void asignar_Doctor (int d,int c, DOCSIG *Doc, CONSIG *Con) // LISTA IMPLEMENTADA	 EXCELL IMPLEMENTADO
{
	int i,j,id,n=0,idc;
	DOCSIG aux , docid;
	CONSIG auxcon, conid;
	do
	{
		docid = NULL;
		system ("cls");
		fflush(stdin);
		printf ("Doctores Disponibles:\n");
		aux = *Doc;
		while (aux != NULL)
		{
			if (aux->disponible==1)//Imprime los doctores que estan disponibles
			{
				printf ("Id: %d Nombre: %s\n////////////\n",aux->id,aux->nombre);
			}
			aux = aux->siguiente_doctor;
		}
		printf ("Ingresa el Id del doctor que desea asignar\n");
		scanf ("%d",&id);
		aux = *Doc;
		while (aux!=NULL && docid == NULL)
		{
			if (aux->id==id&&aux->disponible==1)//Busca su posicion en el arreglo para manejarlo
			{
				docid = aux;
			}
			aux = aux->siguiente_doctor;
		}
		if (docid == NULL)
		{
			printf ("Id ingresada no encontrada\n");
			system ("pause");
		}
	}while (docid == NULL);
	fflush (stdin);
	do
	{
		auxcon = *Con;
		system ("cls");	
		printf ("Consultorios Disponibles:\n");	
		while (auxcon != NULL)
		{
			if (auxcon->id_Doc==0)
			{
				printf ("Consultorio %d\n////////\n",j+1);
			}
			auxcon = auxcon->siguiente_con;
		}
		printf ("Ingrese el cuarto que desea asignar\n");
		scanf ("%d",&idc);
		idc--;
		auxcon = *Con;
		conid = NULL;
		while (auxcon != NULL && conid == NULL)
		{
			if (idc == auxcon->id_Doc)
			{
				conid = auxcon;
			}
			auxcon = auxcon->siguiente_con;
		}
		if (conid->id_Doc!=0)
		{
			printf ("La id proporcionada esta ocupada\n");
			system ("pause");
		}
	}while (conid->id_Doc!=0);
	conid->id_Doc=docid->id;
	//Actualizar el archivo
	int f=remove("CONSULTORIO.xls");
	FILE *fcon=fopen("CONSULTORIO.xls","a");
	auxcon = *Con;
	while (auxcon != NULL)
	{
		fprintf(fcon,"%d\t%d\t%d\t%d\t\n",auxcon->id,auxcon->clave,auxcon->id_Doc,auxcon->id_Pac);
		auxcon = auxcon->siguiente_con;
	}
	fclose (fcon);
}
void mostrar_Doctores (DOCSIG *Doc) // LISTA IMPLEMETADA
{
	DOCSIG aux;
	 while (aux != NULL)
	{
		printf ("Id: %d Nombre: %s\n",aux->id,aux->nombre);
		aux = aux->siguiente_doctor;
	}
}
void editar_Doctor(int d, DOCSIG *Doc) // LISTA IMPLEMETADA	EXCELL IMPLEMENTADO
{
	DOCSIG aux, docid;
	int m,n,i,ba,ba2;

	do
	{
		aux = *Doc;
		docid = NULL;
		system ("cls");
		mostrar_Doctores (&aux);
		printf ("Ingrese la id del doctor que desea editar\n");
		scanf ("%d",&m);
		while (aux != NULL && docid == NULL)
		{
			if (aux->id==m)
			{
				docid = aux;
			}
		}
		if (docid == NULL)
		{
			printf ("Id ingresada no encontrada\n");
			system ("pause");
		}
	}while (docid == NULL);
	do
	{
		system ("cls");
		printf ("1) Nombre: %s\n2) Especialidad: %s\n3) Correo electronico: %s\n",docid->nombre,docid->especialidad,docid->email);
		printf ("4) Telefono: %s\n5) Tarifa: %d\n6) Regresar al menu principal\nIngrese el numero de dato que quiere editar\n",docid->tel,docid->tarifa);
		scanf ("%d",&n);
		fflush(stdin);
		switch (n)
		{
			case 1:
				printf ("Ingrese Nombre del doctor\n");
				scanf ("%[^\n]",docid->nombre);
				break;
			case 2:
				printf ("Ingrese Especialidad del doctor\n");
				scanf ("%[^\n]",docid->especialidad);
				break;
			case 3:
				printf ("Ingrese correo electronico del doctor\n");
				scanf ("%[^\n]",docid->email);
				break;
			case 4:
				printf ("Ingrese telefono del doctor\n");
				scanf ("%[^\n]",docid->tel);
				break;
			case 5:
				printf ("Ingrese la tarifa de consulta del doctor\n");
				scanf ("%d",&i);
				docid->tarifa = i;
				break;
			case 6:
				break;
			default:
				printf ("Opcion ingresada no valida\n");
				Sleep(500);
		}
	}while (n<1||n>6);
	int f=remove("DOCTOR.xls");
	FILE *fdoc=fopen("DOCTOR.xls","a");
	aux = *Doc;
	while (aux != NULL)
	{
		fprintf(fdoc,"%d\t%s\t%s\t%s\t%s\t%d\t\n",aux->id,aux->nombre,aux->especialidad,aux->email,aux->tel,aux->tarifa);
		aux = aux->siguiente_doctor;
	}
	fclose (fdoc);
	fflush(stdin);
}
void consulta_General (int pac, PACSIG *Pac, DOCSIG *Doc, CONSIG *Con) // LISTA IMPLEMETADA	EXCELL IMPLEMENTADO
{
	int j,idc,i,aux;
	CONSIG conaux, conid;
	DOCSIG docaux, docid;
	PACSIG nuevo, previo, actual, pacaux;
	nuevo = malloc(sizeof (PAC));
	nuevo->siguiente_pac = NULL;
	system ("cls");
	///Pido los datos y los guardo en pa posicio  pac de la estructura
	nuevo->id=pac+1;
	fflush(stdin);
	printf ("Ingrese el nombre del paciente\n");
	scanf ("%[^\n]",nuevo->nombre);
	fflush(stdin);
	printf ("Ingrese el telefono del paciente\n");
	scanf ("%[^\n]",nuevo->tel);
	fflush(stdin);
	printf ("Ingrese el correo electronico del paciente\n");
	scanf ("%[^\n]",nuevo->email);
	fflush(stdin);
	printf ("Ingrese el numero de seguro social del paciente\n");
	scanf ("%d",&nuevo->nss);
	fflush(stdin);
	printf ("Ingrese una breve descripcion del padecimiento del paciente (No mas de 100 caracteres)\n");
	scanf ("%[^\n]",nuevo->desc_enf);
	fflush(stdin);
	do
	{
		system ("cls");	
		printf ("Consultorios Disponibles:\n");//Muestro consultorios disponibles y si tienen doctor asignado
		conaux = *Con;
		while (conaux != NULL)
		{
			if (conaux->id_Pac==0&&conaux->id_Doc!=0)
			{
				printf ("Consultorio: %d",conaux->id,j+1);
				if (conaux->id_Doc!=0)
				{
					docaux = *Doc;
					while (docaux != NULL)
					{
						if (conaux->id_Doc==docaux->id)
						{
							docid = docaux;
							i=nDoc;
						}
						docaux = docaux->siguiente_doctor;
					}
					printf ("| Doctor: %s\n////////\n",docid->nombre);
				}
				else
				{
					printf("\n///////\n");
				}
			}
			conaux = conaux->siguiente_con;
		}
		printf ("Ingrese el numero del cuarto que desea asignar al paciente\n");
		scanf ("%d",&idc);
		conaux = *Con;
		conid = NULL;
		while (conaux != NULL)
		{
			if (conaux->id == idc)
			{
				conid = conaux;
			}
			conaux = conaux->siguiente_con;
		}
		if (conid->id_Pac!=0)
		{
			printf ("La id proporcionada esta ocupada");
			Sleep(500);
		}
		if (conid->id_Doc==0)
		{
			printf ("No hay doctor en ese consultorio");
			Sleep (500);
		}
	}while (conid->id_Pac!=0||conid->id_Doc==0||conid == NULL);// Valida que el consultorio este disponible
	conid->id_Pac=nuevo->id;
	FILE *fpac=fopen ("PACIENTECONSULTA.xls","a");
	fprintf(fpac,"%d\t%s\t%s\t%s\t%d\t%s\t\n",nuevo->id,nuevo->nombre,nuevo->tel,nuevo->email,nuevo->nss,nuevo->desc_enf);
	fclose (fpac);
	//Pac=(struct Paciente_Consulta*) realloc(Pac,(pac+2)*sizeof( *Pac));
	// INSERTANDO EL NODO PAC
	previo = NULL;
	actual = *Pac;
	while (actual != NULL)
	{
		previo = actual;
		actual = actual->siguiente_pac;
	}
	if (previo == NULL)
	{
		nuevo->siguiente_pac = *Pac;
		*Pac = nuevo;
	}
	else 
	{
		previo->siguiente_pac = nuevo;
		nuevo->siguiente_pac = actual;
	}
	///Actualizo consultorios.xls
	int f=remove("CONSULTORIO.xls");
	FILE *fcon=fopen("CONSULTORIO.xls","a");
	conaux = *Con;
	while (conaux != NULL)
	{
		fprintf(fcon,"%d,%d,%d,%d,\n",conaux->id,conaux->clave,conaux->id_Doc,conaux->id_Pac);
		conaux = conaux->siguiente_con;
	}
	fclose (fcon);
	fflush(stdin);
}
void openfermedades() // NO NECESITA LISTA
{
	//La funcion enfermedades solamente sirve para imprimir las enfermedades que se tratan por piso
	printf("\n\t*****ENFERMEDADES*****");
	printf("\n\t1)Arritmia cardiaca\n\t2)Hipertensión Arterial\n\t3)Infarto Miocardio Agudo");
	printf("\n\t4)Asma\n\t5)Reflujo Gastroesofágico\n\t6)Neumonía\n\t7)Fractura\n\t8)Contusión ");
	printf("cerebral\n\t9)Traumatismo craneoencefálico\n\t10)Transplantes\n\t11)Fractura nasal\n");
	return;
}
void nomenfermedades(int numenf, PAISIG *Pai) // LISTA IMPLEMETADA
{
	PAISIG aux;
	aux = *Pai;
	//La tarea que realiza nomenfermedades es asignar el nombre de la enfermedad en un campo de la estructura dependiendo de la opción que se escogió en el menú
	switch(numenf){
		case 1: strcpy(aux->enfermedad,"Arritmia cardiaca");break;
		case 2: strcpy(aux->enfermedad,"Hipertensión arterial");break;
		case 3: strcpy(aux->enfermedad,"Infarto Miocardio Agudo");break;
		case 4: strcpy(aux->enfermedad,"Asma");break;
		case 5: strcpy(aux->enfermedad,"Reflujo Gastroesofágico");break;
		case 6: strcpy(aux->enfermedad,"Neumonía");break;
		case 7: strcpy(aux->enfermedad,"Fractura");break;
		case 8: strcpy(aux->enfermedad,"Contusión cerebral");break;
		case 9: strcpy(aux->enfermedad,"Traumatismo craneoencefálico");break;
		case 10: strcpy(aux->enfermedad,"Transplantes");break;
		case 11: strcpy(aux->enfermedad,"Fractura nasal");break;
	}
	return;
}
void rooms(int enfer,PAISIG *Pai, CONSIG *Con) // LISTA IMPLEMENTADA	EXCELL IMPLEMENTADO
{
	//La función rooms se encarga de mostrar las habitaciones disponibles en el piso que trata la enfermedad del paciente
	int piso,i,id;
	PAISIG paiaux;
	CONSIG conaux, conid;
	//depende de la de enfermedad que el paciente padece (indicadas con números del 1-9) en la estructura se guarda el piso en el que se encuentra
	if(enfer==1 || enfer==2 || enfer==3)
	{
		piso=1;
	}
	if(enfer==4 || enfer==5 || enfer==6)
	{
		piso=2;
	}
	if(enfer==7 || enfer==8 || enfer==9)
	{
		piso=3;
	}
	if(enfer==10 || enfer==11)
	{
		piso=4;
	}
	system ("cls");
	printf ("Habitaciones disponibles en el piso %d\n",piso+1);
	conaux = *Con;

	while (conaux != NULL)
	{
		if (conaux->id_Pac == 0 && conaux->id >= piso*10 && conaux->id < (piso+1)*10 )
		{
			printf ("Id: %d Habitacion: %d\n",conaux->id,(conaux->clave%10)+1);
		}
		conaux = conaux->siguiente_con;
	}
	do
	{
		printf ("Ingresa el numero de la habitacion que deseas\n");
		scanf ("%d",&id);
		id=piso*10+id-1;
		conaux = *Con;
		conid = NULL;
		while (conaux != NULL && conid == NULL)
		{
			if (conaux->id == id)
			{
				conid = conaux;
			}
			conaux->siguiente_con;
		}
		if (id>=(piso+1)*10||id<piso*10)
		{
			printf ("Id ingresada no es de este piso \n");
			Sleep (500);
		}
		if (conid->id_Pac!=0)
		{
			printf ("Habitacion ocupada, por favor eliga una disponible\n");
			Sleep (500);
		}
	}while (id>=(piso+1)*10||id<piso*10||conid->id_Pac!=0);
	conid->id_Pac=(*Pai)->id;
	(*Pai)->habitacion=id;
	int f=remove("CONSULTORIO.xls");
	FILE *fcon=fopen("CONSULTORIO.xls","a");///Actualizar consultorio
	conaux = *Con;
	while (conaux != NULL)
	{
		fprintf(fcon,"%d\t%d\t%d\t%d\t\n",conaux->id,conaux->clave,conaux->id_Doc,conaux->id_Pac);
		conaux = conaux->siguiente_con;
	}
	fclose (fcon);
	
}
void Ingreso (int pai, PAISIG *Pai, CONSIG *Con) // LISTA IMPLEMENTADA	EXCELL IMPLEMENTADO
{
	PAISIG nuevo, previo, actual;
	CONSIG conaux;
	nuevo = malloc (sizeof (PAI));
	nuevo->siguiente_pai = NULL;
	int i,j,k,openf;
	system("cls");
	fflush(stdin);
	nuevo->id=pai+1;
	printf ("Ingrese el nombre del Paciente a ingresar\n");
	scanf ("%[^\n]",nuevo->nombre);
	fflush(stdin);
	printf ("Ingrese el telefono del paciente a ingresar\n");
	scanf ("%[^\n]",nuevo->tel);
	fflush(stdin);
	printf ("Ingrese el correo electronico del paciente a ingresar\n");
	scanf ("%[^\n]",nuevo->email);
	fflush(stdin);
	printf ("Ingrese el numero de seguro social del paciente a ingresar\n");
	scanf ("%d",&nuevo->nss);
	fflush(stdin);
	do
	{
		system ("cls");
		openfermedades ();
		printf ("Ingrese la enfermedad que padece el paciente\n");
		scanf ("%d",&openf);
		if (openf<1||openf>11)
		{
			printf ("Opcion de enfermedad invalida\n");
			Sleep (500);
		}
	}while (openf<1||openf>11);
	nomenfermedades(openf,&nuevo);
	conaux = *Con;
	rooms(openf,&nuevo, &conaux);
	system ("cls");
	fflush(stdin);
	printf ("Ingrese una descripcion de la enfermedad que padece el paciente\n");
	scanf ("%[^\n]",nuevo->desc_enf);
	fflush(stdin);
	FILE *fpai=fopen ("PACIENTEINGRESO.xls","a");
	fprintf(fpai,"%d\t%s\t%s\t%s\t%d\t%s\t%d\t%s\t\n",nuevo->id,nuevo->nombre,nuevo->tel,nuevo->email,nuevo->nss,nuevo->enfermedad,nuevo->habitacion,nuevo->desc_enf);
	fclose (fpai);
	//Pai=(struct Paciente_Ingreso*) realloc(Pai,(pai+2)*sizeof( *Pai));
	previo = NULL;
	actual = *Pai;
	while (actual != NULL)
	{
		previo = actual;
		actual = actual->siguiente_pai;
	}
	if (previo == NULL)
	{
		nuevo->siguiente_pai = *Pai;
		*Pai = nuevo;
	}
	else 
	{
		previo->siguiente_pai = nuevo;
		nuevo->siguiente_pai = actual;
	}
}
void cuenta_Consulta_General (CONSIG *Con, DOCSIG *Doc, PACSIG *Pac) // LISTA IMPLEMENTADA	EXCELL IMPLEMENTADO
{
	CONSIG conaux, conid;
	DOCSIG docaux, docid;
	PACSIG pacaux, pacid;
	int cons,i,extra,error=0,pdoc,ppac,n;
	do
	{
		error=0;
		fflush (stdin);
		system ("cls");
		printf ("Ingrese el consultorio en que esta el paciente (del 1 al 10)\n ");
		scanf ("%d",&cons);
		fflush(stdin);
		if (cons>1&&cons<=10)
		{
			cons--;
			conaux = *Con;
			conid = NULL;
			while (conaux != NULL && conid == NULL)
			{
				if (conaux->id == cons)
				{
					conid = conaux;
				}
				conaux = conaux->siguiente_con;
			}
			if (conid->id_Pac==0)
			{
				printf ("El consultorio ingresado no tiene paciente\n");
				Sleep (500);
				error=1;
			}
		}
		else
		{
			printf ("Numero de consultorio ingresado no valido\n");
			error=1;
			Sleep (500);
		}
	}while (error==1);
	docaux = *Doc;
	docid = NULL;
	while (docaux != NULL)
	{
		if (docaux->id == conid->id_Doc)
		{
			docid = docaux;
		}
		docaux = docaux->siguiente_doctor;
	}
	do
	{
		error=0;
		printf ("Costo de consulta del doctor: $%d\nDesea agregar costo extra? (1)SI | (2)NO\n",docid->tarifa);
		scanf ("%d",&n);
		fflush(stdin);
		if (n!=1&&n!=2)
		{
			printf ("Opcion no valida");
			Sleep(500);
			error=1;
		}
		if (n==1)
		{
			do
			{
				printf ("Ingresa el monto\n");
				scanf ("%d",&extra);
				if (extra<0)
				{
					printf ("Ingresa monto valido\n");
					Sleep (500);
				}
			}while (extra<0);
		}
		if (n==2)
		{
			extra=0;
		}
	}while (error==1);
	pacaux = *Pac;
	pacid = NULL;
	while (pacaux != NULL && pacid == NULL)
	{
		if (pacaux->id == conid->id_Pac)
		{
			pacid = pacaux;
		}
		pacaux = pacaux->siguiente_pac;
	}
	system ("cls");
	printf ("****RECIBO****\nPaciente: %s\nDoctor: %s\nConsultorio: %d\nTarifa por consulta: $%d\nCosto Extra: $%d\nTotal: $%d\n",pacid->nombre,docid->nombre,cons,docid->tarifa,extra,docid->tarifa+extra);
	conid->id_Pac=0;
	int f=remove("CONSULTORIO.xls");
	FILE *fcon=fopen("CONSULTORIO.xls","a");///Actualizar consultorio
	conaux = *Con;
	while (conaux != NULL)
	{
		fprintf(fcon,"%d\t%d\t%d\t%d\t\n",conaux->id,conaux->clave,conaux->id_Doc,conaux->id_Pac);
		conaux = conaux->siguiente_con;
	}
	fclose (fcon);
	system("pause");
}
long procedimientos (int *r) // NO NECESITA LISTA
{
	int proc,precio;
	do
	{
		system ("cls");
		fflush(stdin);
		printf("*******PROCEDIMIENTOS*********\n1)Electrocardiograma\n2)Prueba de esfuerzo\n3)Apendicectomía\n4)Biopsias\n5)Bypass Gástrico\n");
		printf("6)Histerectomía\n7)Liposucción\n8)Transplante de córnea\n9)Ecocardiograma transesofágico\nIngrese el numero de procedimiento\n");
		scanf ("%d",&proc);
		if (proc<1||proc>9)
		{
			printf ("Opcion ingresada invalia\n");
			system ("pause");
		}
	}while (proc<1||proc>9);
	switch (proc){
		case 1: 
			precio=5000;
			*r=0;
			break;
		case 2: 
			precio=3500;
			*r=1;
			break;
		case 3: 
			precio=12600;
			*r=2;
			break;
		case 4: 
			precio=6000;
			*r=3;
			break;
		case 5: 
			precio=12000;
			*r=4;
			break;
		case 6: 
			precio=8000;
			*r=5;
			break;
		case 7: 
			precio=15000;
			*r=6;
			break;
		case 8: 
			precio=20000;
			*r=7;
			break;
		case 9: 
			precio=5000;
			*r=8;
			break;
	}
	return precio;
}
void cuenta_Ingreso (CONSIG *Con, PAISIG *Pai) // LISTA IMPLEMETADA	EXCELL IMPLEMENTADO
{
	CONSIG conaux, conid;
	PAISIG paiaux, paiid;
	int pi,nc,idc,op,i,j=0,pr[100],pdia,pp,k;
	long precio;
	char *proce [9]={"Electrocardiograma: $5000","Prueba de esfuerzo: $3500","Apendicectomía: $12600","Biopsias: $6000","Bypass Gástrico: $12000","Histerectomía: $8000","Liposucción: $2000","Transplante de cornea: $20000","Ecocardiograma transesofágico: $5000"};
	do
	{
		do
		{
			system ("cls");
			printf ("Ingrese el piso en donde esta el paciente (2-5)\n");
			scanf ("%d",&pi);
			if (pi<2||pi>5)
			{
				printf ("Por favor ingrese un piso valido");
				system ("pause");
			}
		}while(pi<2||pi>5);
		pi--;
		do
		{
			system ("cls");
			printf ("Ingrese el numero del cuarto en donde esta el paciente (1-10)\n");
			scanf ("%d",&nc);
			if (nc<1||nc>10)
			{
				printf ("Por favor ingrese un numero valido");
				system ("pause");
			}
		}while(nc<1||nc>10);
		nc--;
		idc=pi*10+nc;
		conaux = *Con;
		conid = NULL;
		while (conaux != NULL)
		{
			if (conaux->id = idc)
			{
				conid = conaux;
			}
			conaux = conaux->siguiente_con;
		}
		if (conid->id_Pac==0)
		{
			printf ("Esta habitacion esta vacia\n");
			system ("pause");
		}
	}while (conid->id_Pac==0);
	switch (pi)
	{
		case 1:
			precio=8000;
			break;
		case 2:
			precio=7000;
			break;
		case 3:
			precio=5000;
			break;
		case 4:
			precio=10000;
			break;						
	}
	do
	{
		printf ("Ingresar los dias que el paciente estuvo internado:\n");
		scanf ("%d",&pdia);
		if (pdia<1)
		{
			printf ("Dias ingresados invalidos\n");
			system ("pause");
		}
	}while (pdia<1);
	pp=precio;
	precio=precio*pdia;
	do
	{
		system ("cls");
		printf ("Se realizó algun procedimiento? (1) SI | (2) NO\n");
		scanf ("%d",&op);
		if (op!=2&&op!=1)
		{
			printf ("Ingrese una opcion valida");
			system ("cls");
		}
	}while (op!=2&&op!=1);
	if (op==1)
	{
		do
		{
			precio+=procedimientos(&pr[j]);
			j++;
			do
			{
				system("cls");
				printf ("Agregar otro procedimiento? (1) SI | (2) NO\n");
				scanf ("%d",&i);
				if (i!=1&&i!=2)
				{
					printf("Ingrese opcion valida\n");
					system("pause");
				}
			}while (i!=1&&i!=2);
		}while (i==1);
	}
	op=j;
	paiaux = *Pai;
	paiid = NULL;
	while (paiaux != NULL && paiid == NULL)
	{
		if (paiaux->id == conid->id_Pac)
		{
			paiid = paiaux;
		}
		paiaux = paiaux->siguiente_pai;
	}
	system ("cls");
	printf ("*********RECIBO ESTANCIA********* \nPaciente: %s \nEnfermedad: %s \nPiso %d a $ %d por %d dias Cuarto: %d\nProcedimientos:\n",paiid->nombre,paiid->enfermedad,pi+1,pp,pdia,nc+1);
	fflush(stdin);
	k=j;
	j=op;
	for (i=0;i<j;i++)
	{
		printf ("%s\n",proce[pr[i]]);
	}
	printf ("Total: $%d\n",precio);
	system ("pause");
	conid->id_Pac=0;
	paiid->id=0;
	int d=remove ("PACIENTEINGRESO.xls");
	FILE *fpai=fopen("PACIENTEINGRESO.xls","a");
	paiaux = *Pai;
	while (paiaux != NULL)
	{
		fprintf(fpai,"%d\t%s\t%s\t%s\t%d\t%s\t%d\t%s\t\n",paiaux->id,paiaux->nombre,paiaux->tel,paiaux->email,paiaux->nss,paiaux->enfermedad,paiaux->habitacion,paiaux->desc_enf);
		paiaux = paiaux->siguiente_pai;
	}
	fclose (fpai);
	int f=remove("CONSULTORIO.xls");
	FILE *fcon=fopen("CONSULTORIO.xls","a");///Actualizar consultorio
	conaux = *Con;
	while (conaux != NULL)
	{
		fprintf(fcon,"%d\t%d\t%d\t%d\t\n",conaux->id,conaux->clave,conaux->id_Doc,conaux->id_Pac);
		conaux = conaux->siguiente_con;
	}
	conaux = *Con;
	while (conaux != NULL)
	{
		fprintf(fcon,"%d\t%d\t%d\t%d\t\n",conaux->id,conaux->clave,conaux->id_Doc,conaux->id_Pac);
		conaux = conaux->siguiente_con;
	}
	fclose (fcon);
}
void habitaciones_Disponibles(CONSIG *Con) // LISTA IMPLEMENTADA
{
	CONSIG conaux;
	fflush(stdin);
	char *pisos[5]={"Piso 1: Consultas Generales","Piso 2: Cardiología","Piso 3: Pediatría","Piso 4: Urgencias","Piso 5: Cirugía"};
	int op,i,nd=0;
	printf ("****HABITACIONES DISPONIBLES POR PISOS****\n");
	for (i=0;i<5;i++)
	{
		printf("%s\n",pisos[i]);
	}
	printf("Ingrese el numero del piso que desea\n");
	scanf ("%d",&op);
	op--;
	system("cls");
	printf ("*********HOSPITAL VICTORIA*********\n%s\nHabitaciones disponibles\n",pisos[op]);
	conaux = *Con;
	i = 0;
	while (conaux != NULL)
	{
		if (conaux->id >= op*10 && conaux->id <(op+1)*10 && conaux->id_Pac == 0)
		{
			if (op==0)
			{
				printf("Consultorio: %d\n",i%10+1);
			}
			else
			{
				printf("Habitacion: %d\n",i%10+1);
			}
		}
		conaux = conaux->siguiente_con;
		i++;
	}
	system("pause");
	fflush(stdin);
}
void mostrar_Pacientes (int pcos, PAISIG *Pai) // LISTA IMPLEMENTADA
{
	PAISIG paiaux;
	char *enfermedades[11]={"Arritmia cardiaca","Hipertensión arterial","Infarto Miocardio Agudo","Asma","Reflujo Gastroesofágico","Neumonía","Fractura","Contusión cerebral","Traumatismo craneoencefálico","Transplantes","Fractura nasal"};
	int i,j,k=0;
	switch (pcos)
	{
		case 1:
			printf ("Piso 2: Cardiología\n");
			for (i=0;i<3;i++)
			{
				k=0;
				paiaux = *Pai;
				while (paiaux != NULL)
				{
					if (strcmp(paiaux->enfermedad,enfermedades[i])==0&&paiaux->id!=0)
					{
						k=1;
					}
					paiaux = paiaux->siguiente_pai;
				}
				if (k!=0)
				{
					printf("Enfermedad: %s\n%-35s	%-5s		%-11s	%-50s\n",enfermedades[i],"NOMBRE DEL PACIENTE","NSS","CONSULTORIO","DESCRIPCION");
					paiaux = *Pai;
					while (paiaux != NULL)
					{
						if (strcmp(paiaux->enfermedad,enfermedades[i])==0&&paiaux->id!=0)
						{
							printf ("%-35s	%-5d		%-11d	%-50s\n",paiaux->nombre,paiaux->nss,(paiaux->habitacion)%10,paiaux->desc_enf);
						}
						paiaux = paiaux->siguiente_pai;
					}
				}
			}
			break;
		case 2:
			printf ("Piso 3: Pediatria\n");
			for (i=3;i<6;i++)
			{
				k=0;
				paiaux = *Pai;
				while (paiaux != NULL)
				{
					if (strcmp(paiaux->enfermedad,enfermedades[i])==0&&paiaux->id!=0)
					{
						k=1;
					}
					paiaux = paiaux->siguiente_pai;
				}
				if (k!=0)
				{
					printf("Enfermedad: %s\n%-35s	%-5s		%-11s	%-50s\n",enfermedades[i],"NOMBRE DEL PACIENTE","NSS","CONSULTORIO","DESCRIPCION");
					paiaux = *Pai;
					while (paiaux != NULL)
					{
						if (strcmp(paiaux->enfermedad,enfermedades[i])==0&&paiaux->id!=0)
						{
							printf ("%-35s	%-5d		%-11d	%-50s\n",paiaux->nombre,paiaux->nss,(paiaux->habitacion)%10,paiaux->desc_enf);
						}
						paiaux = paiaux->siguiente_pai;
					}
				}
			}
			break;
		case 3:
			printf ("Piso 4: Urgencias\n");
			for (i=6;i<9;i++)
			{
				k=0;
				paiaux = *Pai;
				while (paiaux != NULL)
				{
					if (strcmp(paiaux->enfermedad,enfermedades[i])==0&&paiaux->id!=0)
					{
						k=1;
					}
					paiaux = paiaux->siguiente_pai;
				}
				if (k!=0)
				{
					printf("Enfermedad: %s\n%-35s	%-5s		%-11s	%-50s\n",enfermedades[i],"NOMBRE DEL PACIENTE","NSS","CONSULTORIO","DESCRIPCION");
					paiaux = *Pai;
					while (paiaux != NULL)
					{
						if (strcmp(paiaux->enfermedad,enfermedades[i])==0&&paiaux->id!=0)
						{
							printf ("%-35s	%-5d		%-11d	%-50s\n",paiaux->nombre,paiaux->nss,(paiaux->habitacion)%10,paiaux->desc_enf);
						}
						paiaux = paiaux->siguiente_pai;
					}
				}
			}
			break;
		case 4:
			printf ("Piso 5: Cirugísa\n");
			for (i=9;i<11;i++)
			{
				k=0;
				paiaux = *Pai;
				while (paiaux != NULL)
				{
					if (strcmp(paiaux->enfermedad,enfermedades[i])==0&&paiaux->id!=0)
					{
						k=1;
					}
					paiaux = paiaux->siguiente_pai;
				}
				if (k!=0)
				{
					printf("Enfermedad: %s\n%-35s	%-5s		%-11s	%-50s\n",enfermedades[i],"NOMBRE DEL PACIENTE","NSS","CONSULTORIO","DESCRIPCION");
					paiaux = *Pai;
					while (paiaux != NULL)
					{
						if (strcmp(paiaux->enfermedad,enfermedades[i])==0&&paiaux->id!=0)
						{
							printf ("%-35s	%-5d		%-11d	%-50s\n",paiaux->nombre,paiaux->nss,(paiaux->habitacion)%10,paiaux->desc_enf);
						}
						paiaux = paiaux->siguiente_pai;
					}
				}
			}
			break;
	}
	printf ("///////////////////////////////////////////////////////////////////////////////////\n");
}
void pacientes (PAISIG *Pai) // LISTA IMPLEMENTADA
{
	PAISIG pai;
	pai = *Pai;
	char *pisos[4]={"Piso 2: Cardiología","Piso 3: Pediatría","Piso 4: Urgencias","Piso 5: Cirugía"};
	int menu,i,j,k,ppi;
	do
	{
		printf ("***OPCIONES***\n1) Mostrar todos los pacientes\n2) Buscar pacientes por piso\n");
		scanf ("%d",&menu);
		if (menu!=1&&menu!=2)
		{
			printf ("Opcion elegida invalida\n");
			system ("pause");
		}
	}while (menu!=1&&menu!=2);
	system ("cls");
	if (menu==1)
	{
		printf ("*********HOSPITAL VICTORIA*********\n");
		for (i=0;i<4;i++)
		{
			ppi=i+1;
			mostrar_Pacientes(ppi,&pai);
		}
	}
	if (menu==2)
	{
		for (j=0;j<4;j++)
		{
			printf ("%s\n",pisos[j]);
		}
		printf ("Ingrese el piso que desea buscar\n");
		scanf ("%d",&i);
		system ("cls");
		printf ("*********HOSPITAL VICTORIA*********\n");
		mostrar_Pacientes(i-1, &pai);
	}
	system ("pause");
}
void lista_Doctores (DOCSIG *Doc) // LISTA IMPLEMENTADA
{
	DOCSIG docaux;
	int i;
	system ("cls");
	printf ("**********************************************************HOSPITAL VICTORIA*******************************************************************\n%-35s	%-25s		%-35s	%-15s	%-5s\n","Nombre del Doctor","Especialidad","Correo","Teléfono","Tarifa");
	docaux = *Doc;
	while (docaux != NULL)
	{
		printf ("%-35s	%-25s		%-35s	%-15s	 $%-5d\n\n",docaux->nombre,docaux->especialidad,docaux->email,docaux->tel,docaux->tarifa);
		docaux = docaux->siguiente_doctor;
	}
}
void reset_Doc(DOCSIG *Doc)
{
	DOCSIG previo, actual, temporal;
	previo = NULL;
	actual = *Doc;
	if (actual != NULL)
	{
		while (actual->siguiente_doctor != NULL) 
		  {
			while (actual->siguiente_doctor != NULL )
			  {
				previo = actual;
				actual = actual -> siguiente_doctor;
			  }
			temporal=actual;
			previo->siguiente_doctor = NULL;
			free(temporal);
			previo = NULL;
			actual = *Doc;
		  } 
		  *Doc = NULL;
	}
}
void reset_Con(CONSIG *Con)
{
	CONSIG previo, actual, temporal;
	previo = NULL;
	actual = *Con;
	if (actual != NULL)
	{
		while (actual->siguiente_con != NULL) 
		  {
			while (actual->siguiente_con != NULL )
			  {
				previo = actual;
				actual = actual -> siguiente_con;
			  }
			temporal=actual;
			previo->siguiente_con = NULL;
			free(temporal);
			previo = NULL;
			actual = *Con;
		  } 
		  *Con = NULL;
	}
}
void reset_Pac(PACSIG *Pac)
{
	PACSIG previo, actual, temporal;
	previo = NULL;
	actual = *Pac;
	if (actual != NULL)
	{
		while (actual->siguiente_pac != NULL) 
		  {
			while (actual->siguiente_pac != NULL )
			  {
				previo = actual;
				actual = actual -> siguiente_pac;
			  }
			temporal=actual;
			previo->siguiente_pac = NULL;
			free(temporal);
			previo = NULL;
			actual = *Pac;
		  } 
		  *Pac = NULL;
	}
}
void reset_Pai(PAISIG *Pai)
{
	PAISIG previo, actual, temporal;
	previo = NULL;
	actual = *Pai;
	if (actual != NULL)
	{
		while (actual->siguiente_pai != NULL) 
		  {
			while (actual->siguiente_pai != NULL )
			  {
				previo = actual;
				actual = actual -> siguiente_pai;
			  }
			temporal=actual;
			previo->siguiente_pai = NULL;
			free(temporal);
			previo = NULL;
			actual = *Pai;
		  } 
		  *Pai = NULL;
	}
}
int main ()
{
	int m,n,i,j;//Variables auxiliares, m es la opcion elegida del menu
	setlocale(LC_ALL,"");
	DOCSIG Doc = NULL;
	PACSIG Pac = NULL;
	PAISIG Pai = NULL;
	CONSIG Con = NULL;
	
	do
	{
		// ELIMINAR TODOS
		reset_Doc(&Doc);
		reset_Con(&Con);
		reset_Pac(&Pac);
		reset_Pai(&Pai);
		// LEER TODOS
		nDoc=leer_Doc(&Doc);
		nCon=leer_Con(&Con,&Doc);
		nPac=leer_Pac(&Pac);
		nPai=leer_Pai(&Pai);
		m=menu();
		switch (m)
		{
			case 1:
				do
				{
					system("cls");
					printf ("Opciones.-\n1) Nuevo Doctor\n2)Asignacion de doctor\n3)Editar\n4)Volver a menu principal\n");
					scanf ("%d",&n);
					switch (n)
					{
						case 1:
							nuevo_Doctor (nDoc, &Doc);
							nDoc++;
							break;
						case 2:
							asignar_Doctor (nDoc,nCon, &Doc, &Con);
							break;
						case 3:
							editar_Doctor (nDoc, &Doc);
							break;
						case 4:
							break;
						default:
							printf ("Opcion no valida\n");
					}
				}while(n<1||n>4);
				
				break;
			case 2:
				consulta_General(nPac, &Pac, &Doc, &Con);
				nPac++;
				break;
			case 3:
				Ingreso (nPai, &Pai, &Con);
				nPai++;
				break;
			case 4:
				do
				{
					system ("cls");
					printf ("*****CUENTA*****\n1) Cobro de consulta general\n2) Cobro de estancia\nEliga una opcion\n");
					scanf ("%d",&n);
					if (n!=1&&n!=2)
					{
						printf ("Opción ingresada invalida\n");
						Sleep (500);
					}
				} while (n!=1&&n!=2);
				if (n==1)
				{
					cuenta_Consulta_General (&Con, &Doc, &Pac);
				}
				else
				{
					cuenta_Ingreso (&Con, &Pai);
				}
				break;
			case 5:
				do
				{
					system ("cls");
					printf("Opciones.-\n1) Habitaciones disponibles\n2) Pacientes\n3) Doctores\n");
					scanf ("%d",&n);
					if (n<1||n>3)
					{
						printf ("Opcion ingresada no valida\n");
						system ("pause");
					}
				}while (n<1||n>3);
				system("cls");
				switch (n)
				{
					case 1:
						habitaciones_Disponibles(&Con);
						break;
					case 2:
						pacientes(&Pai);
						break;
					case 3:
						lista_Doctores(&Doc);
						system ("pause");
						break;
				}
				break;
				
		}
	}while (m!=6);
	return 0;
	system ("pause");
}
