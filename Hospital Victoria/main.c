#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <windows.h>
//int habitaciones [4][10];//[pisos][habitaciones]
int nDoc=0,nPac=0,nPai=0,nCon=0;// nDoc,nPac y nPai guardan la ultima posicion de su arreglo de estructuras correspondiente
struct Doctores
{
	int id;
	char nombre [80];
	char especialidad[80];
	char email[80];
	char tel[80];
	unsigned int tarifa;
	int disponible;//1 es disponible, 0 no disponible
} *Doc;
struct Paciente_Consulta
{
	int id;
	char nombre [80];
	char tel[80];
	char email[80];
	unsigned int nss;//Numero de seguro social
	char desc_enf[100];//Descripcion de la enfermedad
} *Pac;
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
}*Pai;
struct Consultorio
{
	int id;
	int clave;
	long id_Doc;
	long id_Pac;
}*Con;
int leer_Doc ()
{
	char c;
	char aux[80];
	int ba=0,i=0,j=0,k;
	FILE *fdoc=fopen("DOCTOR.txt","rb");/////////
	c=fgetc(fdoc);/////////
	while (c!=EOF)
	{
		if (c=='\n')//Si hay un enter, cambiara de posicion del arreglo de estructura
		{
			Doc=(struct Doctores*) realloc(Doc,(j+2)*sizeof( *Doc)); //Aumenta 1 de casillas
			j++;
			ba=0;
		}
		else
		{
			if (c==',')
			{
				i=0;
				switch (ba)// ba hace referencia es el tipo de dato de la estructura que se esta leyendo
				{
					case 0:
						Doc[j].id=atoi(aux);
						break;
					case 1:
						strcpy(Doc[j].nombre,aux);
						break;
					case 2:
						strcpy(Doc[j].especialidad,aux);
						break;
					case 3:
						strcpy(Doc[j].email,aux);
						break;
					case 4:
						strcpy(Doc[j].tel,aux);
						break;
					case 5:
						Doc[j].tarifa=atoi(aux);
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
int leer_Pac ()
{
	char c;
	char aux[100];
	int ba=0,i=0,j=0,k;
	FILE *fpac=fopen("PACIENTECONSULTA.txt","rb");/////////
	c=fgetc(fpac);/////////
	while (c!=EOF)
	{
		if (c=='\n')//Si hay un enter, cambiara de posicion del arreglo de estructura
		{
			Pac=(struct Paciente_Consulta*) realloc(Pac,(j+2)*sizeof( *Pac)); //Aumenta 1 de casillas
			j++;
			ba=0;
		}
		else
		{
			if (c==',')
			{
				i=0;
				switch (ba)// ba hace referencia es el tipo de dato de la estructura que se esta leyendo
				{
					case 0:
						Pac[j].id=atoi(aux);
						break;
					case 1:
						strcpy(Pac[j].nombre,aux);
						break;
					case 2:
						strcpy(Pac[j].tel,aux);
						break;
					case 3:
						strcpy(Pac[j].email,aux);
						break;
					case 4:
						Pac[j].nss=atoi(aux);
						break;
					case 5:
						strcpy(Pac[j].desc_enf,aux);
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
int leer_Pai ()
{
	char c;
	char aux[80];
	int ba=0,i=0,j=0,k;
	FILE *fpai=fopen("PACIENTEINGRESO.txt","rb");/////////
	c=fgetc(fpai);/////////
	while (c!=EOF)
	{
		if (c=='\n')//Si hay un enter, cambiara de posicion del arreglo de estructura
		{
			Pai=(struct Paciente_Ingreso*) realloc(Pai,(j+2)*sizeof( *Pai)); //Aumenta 1 de casillas
			j++;
			ba=0;
		}
		else
		{
			if (c==',')
			{
				i=0;
				switch (ba)// ba hace referencia es el tipo de dato de la estructura que se esta leyendo
				{
					case 0:
						Pai[j].id=atoi(aux);
						break;
					case 1:
						strcpy(Pai[j].nombre,aux);
						break;
					case 2:
						strcpy(Pai[j].tel,aux);
						break;
					case 3:
						strcpy(Pai[j].email,aux);
						break;
					case 4:
						Pai[j].nss=atoi(aux);
						break;
					case 5:
						strcpy(Pai[j].enfermedad,aux);
						break;
					case 6:
						Pai[j].habitacion=atoi(aux);
						break;
					case 7:
						strcpy(Pai[j].desc_enf,aux);
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
int leer_Con ()
{
	char c;
	char aux[80];
	int ba=0,i=0,j=0,k,m;
	for (m=0;m<nDoc;m++)
	{
		Doc[m].disponible=1;
	}
	FILE *fcon=fopen("CONSULTORIO.txt","rb");/////////
	c=fgetc(fcon);/////////
	while (c!=EOF)
	{
		if (c=='\n')//Si hay un enter, cambiara de posicion del arreglo de estructura
		{
			Con=(struct Consultorio*) realloc(Con,(j+2)*sizeof( *Con)); //Aumenta 1 de casillas
			j++;
			ba=0;
		}
		else
		{
			if (c==',')
			{
				i=0;
				switch (ba)// ba hace referencia es el tipo de dato de la estructura que se esta leyendo
				{
					case 0:
						Con[j].id=atoi(aux);
						break;
					case 1:
						Con[j].clave=atoi(aux);
						break;
					case 2:
						Con[j].id_Doc=atoi(aux);
						if (Con[j].id_Doc!=0)
						{
							for (m=0;m<nDoc;m++)
							{
								if (Con[j].id_Doc==Doc[m].id)
								{
									Doc[m].disponible=0;
								}
							}
						}
						break;
					case 3:
						Con[j].id_Pac=atoi(aux);
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
void nuevo_Doctor (int nDoc)
{
	system ("cls");
	FILE *fdoc=fopen("DOCTOR.txt","a");
	fflush (stdin);
	printf ("Ingresa el nombre del doctor\n");
	scanf ("%[^\n]",Doc[nDoc].nombre);
	fflush(stdin);
	printf ("Ingresa la especialidad del doctor\n");
	scanf ("%[^\n]",Doc[nDoc].especialidad);
	fflush(stdin);
	printf ("Ingrese el correo electronico del doctor\n");
	scanf ("%[^\n]",Doc[nDoc].email);
	fflush(stdin);
	printf ("Ingrese el numero telefonico del doctor\n");
	scanf ("%[^\n]",Doc[nDoc].tel);
	fflush(stdin);
	printf ("Ingrese la tarifa por consulta del doctor\n");
	scanf ("%d",&Doc[nDoc].tarifa);
	fflush(stdin);
	Doc[nDoc].id=nDoc+1;
	Doc=(struct Doctores*) realloc(Doc,(nDoc+2)*sizeof( *Doc));
	fprintf(fdoc,"%d,%s,%s,%s,%s,%d,\n",nDoc+1,Doc[nDoc].nombre,Doc[nDoc].especialidad,Doc[nDoc].email,Doc[nDoc].tel,Doc[nDoc].tarifa);
	fclose (fdoc);
}
void asignar_Doctor (int d,int c)
{
	int i,j,id,n=0,idc;
	do
	{
		system ("cls");
		fflush(stdin);
		printf ("Doctores Disponibles:\n");
		for (i=0;i<d;i++)
		{
			if (Doc[i].disponible==1)//Imprime los doctores que estan disponibles
			{
				printf ("Id: %d Nombre: %s\n////////////\n",Doc[i].id,Doc[i].nombre);
			}
		}
		printf ("Ingresa el Id del doctor que desea asignar\n");
		scanf ("%d",&id);
		for (i=0;i<d;i++)
		{
			if (Doc[i].id==id&&Doc[i].disponible==1)//Busca su posicion en el arreglo para manejarlo
			{
				n=i;
				i=d+1;
			}
		}
		if (i==d)
		{
			printf ("Id ingresada no encontrada\n");
			system ("pause");
		}
	}while (i==d);
	fflush (stdin);
	do
	{
		system ("cls");	
		printf ("Consultorios Disponibles:\n");
		for (i=0;i<5;i++)
		{
			for (j=0;j<10;j++)
			{
				if (Con[i*10+j].id_Doc==0)
				{
					printf ("Id: %d Piso: %d Numero de cuarto: %d\n////////\n",Con[i*10+j].id,i,j);
				}
			}
		}
		printf ("Ingrese id del cuarto que desea asignar al doctor\n");
		scanf ("%d",&idc);
		if (Con[idc].id_Doc!=0)
		{
			printf ("La id proporcionada esta ocupada");
			system ("pause");
		}
	}while (Con[idc].id_Doc!=0);
	Con[idc].id_Doc=Doc[n].id;
	//Actualizar el archivo
	int f=remove("CONSULTORIO.txt");
	FILE *fcon=fopen("CONSULTORIO.txt","a");
	for (i=0;i<c;i++)
	{
		fprintf(fcon,"%d,%d,%d,%d,\n",Con[i].id,Con[i].clave,Con[i].id_Doc,Con[i].id_Pac);
	}
	fclose (fcon);
}
void mostrar_Doctores (int d)
{
	int i;
	for (i=0;i<d;i++)
	{
		printf ("Id: %d Nombre: %s\n",Doc[i].id,Doc[i].nombre);
	}
}
void editar_Doctor(int d)
{
	int m,n,i,ba,ba2;
	do
	{
		system ("cls");
		mostrar_Doctores (d);
		printf ("Ingrese la id del doctor que desea editar\n");
		scanf ("%d",&m);
		for (i=0;i<d;i++)
		{
			if (Doc[i].id==m)
			{
				ba=i;
				i=d+1;
			}
		}
		if (i==d)
		{
			printf ("Id ingresada no encontrada\n");
			system ("pause");
		}
	}while (i==d);
	do
	{
		system ("cls");
		printf ("1) Nombre: %s\n2) Especialidad: %s\n3) Correo electronico: %s\n",Doc[ba].nombre,Doc[ba].especialidad,Doc[ba].email);
		printf ("4) Telefono: %s\n5) Tarifa: %d\n6) Regresar al menu principal\nIngrese el numero de dato que quiere editar\n",Doc[ba].tel,Doc[ba].tarifa);
		scanf ("%d",&n);
		fflush(stdin);
		switch (n)
		{
			case 1:
				printf ("Ingrese Nombre del doctor\n");
				scanf ("%[^\n]",Doc[ba].nombre);
				break;
			case 2:
				printf ("Ingrese Especialidad del doctor\n");
				scanf ("%[^\n]",Doc[ba].especialidad);
				break;
			case 3:
				printf ("Ingrese correo electronico del doctor\n");
				scanf ("%[^\n]",Doc[ba].email);
				break;
			case 4:
				printf ("Ingrese telefono del doctor\n");
				scanf ("%[^\n]",Doc[ba].tel);
				break;
			case 5:
				printf ("Ingrese la tarifa de consulta del doctor\n");
				scanf ("%d",&Doc[ba].tarifa);
				break;
			case 6:
				break;
			default:
				printf ("Opcion ingresada no valida\n");
				Sleep(500);
		}
	}while (n<1||n>6);
	int f=remove("DOCTOR.txt");
	FILE *fdoc=fopen("DOCTOR.txt","a");
	for (i=0;i<d;i++)
	{
		fprintf(fdoc,"%d,%s,%s,%s,%s,%d,\n",Doc[i].id,Doc[i].nombre,Doc[i].especialidad,Doc[i].email,Doc[i].tel,Doc[i].tarifa);
	}
	fclose (fdoc);
	fflush(stdin);
}
void consulta_General (int pac)
{
	int j,idc,i,aux;
	system ("cls");
	///Pido los datos y los guardo en pa posicio  pac de la estructura
	Pac[pac].id=pac+1;
	fflush(stdin);
	printf ("Ingrese el nombre del paciente\n");
	scanf ("%[^\n]",Pac[pac].nombre);
	fflush(stdin);
	printf ("Ingrese el telefono del paciente\n");
	scanf ("%[^\n]",Pac[pac].tel);
	fflush(stdin);
	printf ("Ingrese el correo electronico del paciente\n");
	scanf ("%[^\n]",Pac[pac].email);
	fflush(stdin);
	printf ("Ingrese el numero de seguro social del paciente\n");
	scanf ("%d",&Pac[pac].nss);
	fflush(stdin);
	printf ("Ingrese una breve descripcion del padecimiento del paciente (No mas de 100 caracteres)\n");
	scanf ("%[^\n]",Pac[pac].desc_enf);
	fflush(stdin);
	do
	{
		system ("cls");	
		printf ("Consultorios Disponibles:\n");//Muestro consultorios disponibles y si tienen doctor asignado
		for (j=0;j<10;j++)
		{
			if (Con[j].id_Pac==0&&Con[j].id_Doc!=0)
			{
				printf ("Consultorio: %d",Con[j].id,j+1);
				if (Con[j].id_Doc!=0)
				{
					
					for (i=0;i<nDoc;i++)
					{
						if (Con[j].id_Doc==Doc[i].id)
						{
							aux=i;
							i=nDoc;
						}
					}
					printf ("| Doctor: %s\n////////\n",Doc[aux].nombre);
				}
				else
				{
					printf("\n///////\n");
				}
			}
		}
		printf ("Ingrese el numero del cuarto que desea asignar al paciente\n");
		scanf ("%d",&idc);
		if (Con[idc].id_Pac!=0)
		{
			printf ("La id proporcionada esta ocupada");
			Sleep(500);
		}
		if (Con[idc].id_Doc==0)
		{
			printf ("No hay doctor en ese consultorio");
			Sleep (500);
		}
	}while (Con[idc].id_Pac!=0||Con[idc].id_Doc==0);// Valida que el consultorio este disponible
	Con[idc].id_Pac=Pac[pac].id;
	FILE *fpac=fopen ("PACIENTECONSULTA.txt","a");
	fprintf(fpac,"%d,%s,%s,%s,%d,%s,\n",Pac[pac].id,Pac[pac].nombre,Pac[pac].tel,Pac[pac].email,Pac[pac].nss,Pac[pac].desc_enf);
	fclose (fpac);
	Pac=(struct Paciente_Consulta*) realloc(Pac,(pac+2)*sizeof( *Pac));
	///Actualizo consultorios.txt
	int f=remove("CONSULTORIO.txt");
	FILE *fcon=fopen("CONSULTORIO.txt","a");
	for (i=0;i<nCon;i++)
	{
		fprintf(fcon,"%d,%d,%d,%d,\n",Con[i].id,Con[i].clave,Con[i].id_Doc,Con[i].id_Pac);
	}
	fclose (fcon);
	fflush(stdin);
}
void openfermedades()
{
	//La funcion enfermedades solamente sirve para imprimir las enfermedades que se tratan por piso
	printf("\n\t*****ENFERMEDADES*****");
	printf("\n\t1)Arritmia cardiaca\n\t2)Hipertensión Arterial\n\t3)Infarto Miocardio Agudo");
	printf("\n\t4)Asma\n\t5)Reflujo Gastroesofágico\n\t6)Neumonía\n\t7)Fractura\n\t8)Contusión ");
	printf("cerebral\n\t9)Traumatismo craneoencefálico\n\t10)Transplantes\n\t11)Fractura nasal\n");
	return;
}
void nomenfermedades(int numenf, int pos)
{
	//La tarea que realiza nomenfermedades es asignar el nombre de la enfermedad en un campo de la estructura dependiendo de la opción que se escogió en el menú
	switch(numenf){
		case 1: strcpy(Pai[pos].enfermedad,"Arritmia cardiaca");break;
		case 2: strcpy(Pai[pos].enfermedad,"Hipertensión arterial");break;
		case 3: strcpy(Pai[pos].enfermedad,"Infarto Miocardio Agudo");break;
		case 4: strcpy(Pai[pos].enfermedad,"Asma");break;
		case 5: strcpy(Pai[pos].enfermedad,"Reflujo Gastroesofágico");break;
		case 6: strcpy(Pai[pos].enfermedad,"Neumonía");break;
		case 7: strcpy(Pai[pos].enfermedad,"Fractura");break;
		case 8: strcpy(Pai[pos].enfermedad,"Contusión cerebral");break;
		case 9: strcpy(Pai[pos].enfermedad,"Traumatismo craneoencefálico");break;
		case 10: strcpy(Pai[pos].enfermedad,"Transplantes");break;
		case 11: strcpy(Pai[pos].enfermedad,"Fractura nasal");break;
	}
	return;
}
void rooms(int enfer,int pos)
{
	//La función rooms se encarga de mostrar las habitaciones disponibles en el piso que trata la enfermedad del paciente
	int piso,i,id;
	//depende de la de enfermedad que el paciente padece (indicadas con números del 1-9) en la estructura se guarda el piso en el que se encuentra
	if(enfer==1 || enfer==2 || enfer==3)
	{
		piso=1;
	}
	if(enfer==4 || enfer==5 || enfer==6){
		piso=2;
	}
	if(enfer==7 || enfer==8 || enfer==9){
		piso=3;
	}
	if(enfer==10 || enfer==11){
		piso=4;
	}
	system ("cls");
	printf ("Habitaciones disponibles en el piso %d\n",piso+1);
	for (i=piso*10;i<(piso+1)*10;i++)
	{
		if (Con[i].id_Pac==0)
		{
			printf ("Id: %d Habitacion: %d\n",Con[i].id,(Con[i].clave%10)+1);
		}
	}
	do
	{
		printf ("Ingresa el numero de la habitacion que deseas\n");
		scanf ("%d",&id);
		id=piso*10+id-1;
		if (id>=(piso+1)*10||id<piso*10)
		{
			printf ("Id ingresada no es de este piso \n");
			Sleep (500);
		}
		if (Con[id].id_Pac!=0)
		{
			printf ("Habitacion ocupada, por favor eliga una disponible\n");
			Sleep (500);
		}
	}while (id>=(piso+1)*10||id<piso*10||Con[id].id_Pac!=0);
	Con[id].id_Pac=Pai[pos].id;
	Pai[pos].habitacion=id;
	int f=remove("CONSULTORIO.txt");
	FILE *fcon=fopen("CONSULTORIO.txt","a");///Actualizar consultorio
	for (i=0;i<50;i++)
	{
		fprintf(fcon,"%d,%d,%d,%d,\n",Con[i].id,Con[i].clave,Con[i].id_Doc,Con[i].id_Pac);
	}
	fclose (fcon);
	
}
void Ingreso (pai)
{
	int i,j,k,openf;
	system("cls");
	fflush(stdin);
	Pai[pai].id=pai+1;
	printf ("Ingrese el nombre del Paciente a ingresar\n");
	scanf ("%[^\n]",Pai[pai].nombre);
	fflush(stdin);
	printf ("Ingrese el telefono del paciente a ingresar\n");
	scanf ("%[^\n]",Pai[pai].tel);
	fflush(stdin);
	printf ("Ingrese el correo electronico del paciente a ingresar\n");
	scanf ("%[^\n]",Pai[pai].email);
	fflush(stdin);
	printf ("Ingrese el numero de seguro social del paciente a ingresar\n");
	scanf ("%d",&Pai[pai].nss);
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
	nomenfermedades(openf,pai);
	rooms(openf,pai);
	system ("cls");
	fflush(stdin);
	printf ("Ingrese una descripcion de la enfermedad que padece el paciente\n");
	scanf ("%[^\n]",Pai[pai].desc_enf);
	fflush(stdin);
	FILE *fpai=fopen ("PACIENTEINGRESO.txt","a");
	fprintf(fpai,"%d,%s,%s,%s,%d,%s,%d,%s,\n",Pai[pai].id,Pai[pai].nombre,Pai[pai].tel,Pai[pai].email,Pai[pai].nss,Pai[pai].enfermedad,Pai[pai].habitacion,Pai[pai].desc_enf);
	fclose (fpai);
	Pai=(struct Paciente_Ingreso*) realloc(Pai,(pai+2)*sizeof( *Pai));
}
void cuenta_Consulta_General ()
{
	int cons,i,extra,error=0,pdoc,ppac,n;
	do
	{
		error=0;
		fflush (stdin);
		system ("cls");
		printf ("Ingrese el consultorio en que esta el paciente (del 1 al 10)\n ");
		scanf ("%d",&cons);
		fflush(stdin);
		if (cons>1&&cons<10)
		{
			cons--;
			if (Con[cons].id_Pac==0)
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
	for (i=0;i<nDoc;i++)
	{
		if (Doc[i].id==Con[cons].id_Doc)
		{
			pdoc=i;
			i=nDoc+1;
		}
	}
	do
	{
		error=0;
		printf ("Costo de consulta del doctor: $%d\nDesea agregar costo extra? (1)SI | (2)NO\n",Doc[pdoc].tarifa);
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
	for (i=0;i<nPac;i++)
	{
		if (Pac[i].id==Con[cons].id_Pac)
		{
			ppac=i;
			i=nPac+1;
		}
	}
	system ("cls");
	printf ("****RECIBO****\nPaciente: %s\nDoctor: %s\nConsultorio: %d\nTarifa por consulta: $%d\nCosto Extra: $%d\nTotal: $%d\n",Pac[ppac].nombre,Doc[pdoc].nombre,cons,Doc[pdoc].tarifa,extra,Doc[pdoc].tarifa+extra);
	Con[cons].id_Pac=0;
	int f=remove("CONSULTORIO.txt");
	FILE *fcon=fopen("CONSULTORIO.txt","a");///Actualizar consultorio
	for (i=0;i<50;i++)
	{
		fprintf(fcon,"%d,%d,%d,%d,\n",Con[i].id,Con[i].clave,Con[i].id_Doc,Con[i].id_Pac);
	}
	fclose (fcon);
	system("pause");
}
long procedimientos (int *r)
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
void cuenta_Ingreso ()
{
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
		if (Con[idc].id_Pac==0)
		{
			printf ("Esta habitacion esta vacia\n");
			system ("pause");
		}
	}while (Con[idc].id_Pac==0);
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
	for (k=0;k<nPai;k++)
	{
		if (Pai[k].id==Con[idc].id_Pac)
		{
			j=k;
			k=nPai+1;
		}
	}
	system ("cls");
	printf ("%d\n",j);
	printf ("*********RECIBO ESTANCIA********* \nPaciente: %s \nEnfermedad: %s \nPiso %d a $ %d por %d dias Cuarto: %d\nProcedimientos:\n",Pai[j].nombre,Pai[j].enfermedad,pi+1,pp,pdia,nc+1);
	fflush(stdin);
	j=op;
	for (i=0;i<j;i++)
	{
		printf ("%s\n",proce[pr[i]]);
	}
	printf ("Total: $%d\n",precio);
	system ("pause");
	Con[idc].id_Pac=0;
	int f=remove("CONSULTORIO.txt");
	FILE *fcon=fopen("CONSULTORIO.txt","a");///Actualizar consultorio
	for (i=0;i<50;i++)
	{
		fprintf(fcon,"%d,%d,%d,%d,\n",Con[i].id,Con[i].clave,Con[i].id_Doc,Con[i].id_Pac);
	}
	fclose (fcon);
}
void habitaciones_Disponibles()
{
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
	for (i=op*10;i<(op+1)*10;i++)
	{
		if (Con[i].id_Pac==0&&op!=0)
		{
			printf("Habitacion: %d\n",i%10+1);
		}
		if (Con[i].id_Pac==0&&op==0)
		{
			printf("Consultorio: %d\n",i%10+1);
		}
	}
	system("pause");
	fflush(stdin);
}
int main ()
{
	int m,n,i,j;//Variables auxiliares, m es la opcion elegida del menu
	setlocale(LC_ALL,"");
	Doc = (struct Doctores*) malloc(sizeof(*Doc)); //Reserva un espacio de memoria
	Pac = (struct Paciente_Consulta*) malloc(sizeof(*Pac));
	Pai = (struct Paciente_Ingreso*) malloc(sizeof(*Pai));
	Con = (struct Consultorio*) malloc(sizeof(*Con));
	do
	{
		nDoc=leer_Doc();
		nCon=leer_Con();
		nPac=leer_Pac();
		nPai=leer_Pai();
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
							nuevo_Doctor (nDoc);
							nDoc++;
							break;
						case 2:
							asignar_Doctor (nDoc,nCon);
							break;
						case 3:
							editar_Doctor (nDoc);
							break;
						case 4:
							break;
						default:
							printf ("Opcion no valida\n");
					}
				}while(n<1||n>4);
				
				break;
			case 2:
				consulta_General(nPac);
				nPac++;
				break;
			case 3:
				Ingreso (nPai);
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
					cuenta_Consulta_General ();
				}
				else
				{
					cuenta_Ingreso ();
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
				switch (n)
				{
					case 1:
						habitaciones_Disponibles();
						break;
					case 2:
						break;
					case 3:
						break;
				}
				break;
				
		}
	}while (m!=6);
	return 0;
	system ("pause");
}
