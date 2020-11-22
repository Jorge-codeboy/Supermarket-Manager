# include <stdio.h>
# include <conio.h>
# include <String.h>
# include <fstream>

using namespace std;
int clave;
char titulo[26], autor[26], cont[26], falso[2];
    
struct Libro{
	int clave;
	char titulo[26];
	char autor[26];
	char cont[26];
	Libro *next,*prev;
};


Libro *primero, *ultimo, *actual, *nuevo, *previo;

void cargarArch()
{
    ifstream arch;
    arch.open("biblioteca.txt",ios::in);
    int clave;
    char titulo[26], autor[26], cont[26];
	printf("PASA 1");
    while(!arch.eof()){
    	printf("PASA 2");
        arch >>clave >>titulo >>autor >>cont;
        printf("PASA 3");
        if(!arch.eof()){
            nuevo= new Libro;

            nuevo->clave = clave;
       
            
            strcpy(nuevo->titulo,titulo);

            
            strcpy(nuevo->autor,autor);

            
            strcpy(nuevo->cont,cont);

            
            nuevo->next= NULL;

            
            nuevo->prev = NULL;

            
            if(primero == NULL){              
                primero = nuevo;

                
                ultimo = nuevo;

            }
            else{
                ultimo->next= nuevo;

                
                nuevo->prev = ultimo;
 

                ultimo= nuevo;

            }
        }
    }
    arch.close();
}

void descargarLibros(){
    actual= primero;
    ofstream arch;
    arch.open("biblioteca.txt",ios::out);
    while(actual != NULL){
		for (int i=0;i<strlen(actual->autor);i++) if (actual->autor[i]==' ') actual->autor[i]='_';
		for (int i=0;i<strlen(actual->titulo);i++) if (actual->titulo[i]==' ') actual->titulo[i]='_';
		for (int i=0;i<strlen(actual->cont);i++) if (actual->cont[i]==' ') actual->cont[i]='_';
        arch << actual->clave <<" "<<actual->autor<<" "<<actual->titulo<<" "<< actual->cont<<"\n";
        actual=actual->next;
    }
    arch.close();


}

void pausa(){
	printf("[[ENTER PARA CONTINUAR]]\n");
	getche();
}

void inserta_fin(){
	if (primero==NULL){
		primero=nuevo;
		ultimo=nuevo;		
	}
	else{
		ultimo->next=nuevo;
		nuevo->prev=ultimo;
		ultimo=nuevo;
	}
	descargarLibros();
	
}


void pide_datos(){
	printf("Indica la clave de libro      : "); scanf("%d",&clave);gets(falso);
	printf("Indica el T%ctulo del libro    : ",161); gets(titulo);
	printf("Indica el Autor del libro     : "); gets(autor);
	printf("Indica el contenido del libro : "); gets(cont);
	nuevo= new Libro;
	nuevo->clave=clave;
	strcpy(nuevo->titulo,titulo);
	strcpy(nuevo->autor,autor);
	strcpy(nuevo->cont,cont);
	nuevo->next=NULL;
	nuevo->prev=NULL;
	inserta_fin();
	
}

bool busca_nodo(){
	if (primero==NULL){
		printf("ERROR, la lista est%c vac%a \n",160,161);
	}
	else{
		printf("Indica la clave : "); scanf("%d",&clave); gets(falso);
		actual=primero;
		while(actual!=NULL){
			if (actual->clave==clave) return(true);
			actual=actual->next;
		}
		return(false);
	}
	
}
void consulta_nodo(){
	if (!busca_nodo()){
		printf("Error, libro inexistente en la lista \n");
	}
	else{
		printf("Clave     :%d\n",actual->clave);
		printf("T%ctulo   :%s\n",161,actual->titulo);
		printf("Autor     :%s\n",actual->autor);
		printf("Contenido :%s\n",actual->cont);
	}
	pausa();
	
}

void elimina_especifico(){
	Libro *anterior,*siguiente;
	if (primero==NULL){
		printf("ERROR, la lista est%c vac%ca \n",160,161);
		pausa();
	}
	else{
		if (!busca_nodo()){
			printf("Error, libro inexistente en la lista \n");
			pausa();
		}
		else{
			if (actual==primero){
				if (primero==ultimo){
					primero=NULL;
					ultimo=NULL;
				}
				else{
					actual=primero;
					primero=primero->next;
					primero->prev=NULL;
					delete(actual);
				}
			}
			else{
				if (actual==ultimo) {
					if (primero==ultimo){
						primero=NULL;
						ultimo=NULL;
					}
					else{
						actual=ultimo;
						ultimo=actual->prev;
						ultimo->next=NULL;
						delete(actual);
					}
					
				}
				else{
					anterior=actual->prev;
					siguiente=actual->next;
					anterior->next=siguiente;
					siguiente->prev=anterior;
					delete(actual);
				}
			}	
		}
	}
}


void listado_general(){
	if (primero==NULL){
		printf("ERROR, la lista est%c vac%ca \n",160,161);
	}
	else{
		actual=primero;
		while(actual!=NULL){
			printf("%d   %s   %s   %s\n",actual->clave,actual->titulo,actual->autor,actual->cont);
			actual=actual->next;
			
		}
	}
	pausa();
}


void ordenar_listas(int opi){
	Libro *actual_i,*actual_j,*auxiliar;
	actual_i=primero;
	auxiliar=new Libro;
	while (actual_i!=NULL){
		actual_j=actual_i->next;
		while (actual_j!=NULL){
		//char mat[10], nom[21], ap[21], car[4];
			if ((opi==1 && (actual_i->clave>actual_j->clave)) || (opi==2 && (strcmp(actual_i->titulo,actual_j->titulo)==1)) || (opi==3 && (strcmp(actual_i->autor,actual_j->autor)==1)) || (opi==4 && (strcmp(actual_i->cont,actual_j->cont)==1)) ){
				
				auxiliar->clave=actual_i->clave;
				strcpy(auxiliar->titulo,actual_i->titulo);
				strcpy(auxiliar->autor,actual_i->autor);
				strcpy(auxiliar->cont,actual_i->cont);

				//---------------------------------------------
				actual_i->clave=actual_j->clave;
				strcpy(actual_i->titulo,actual_j->titulo);
				strcpy(actual_i->autor,actual_j->autor);
				strcpy(actual_i->cont,actual_j->cont);	
				//-----------------------------------------------
				actual_j->clave=auxiliar->clave;
				strcpy(actual_j->titulo,auxiliar->titulo);
				strcpy(actual_j->autor,auxiliar->autor);
				strcpy(actual_j->cont,auxiliar->cont);		
				
			}
			actual_j=actual_j->next;
			
		}
		actual_i=actual_i->next;
		
		
	}
	listado_general();
	
}

void menu(){
	int op=0;
	while (op!=8){
		printf("\n\n*******\n");
		printf("1) Agregar Libro\n");  //LISTO
		printf("2) Consultar Libros\n"); //LISTO
		printf("3) Bajas de Libros\n"); //LISTO
		printf("4) Listado general de Libros\n"); //LISTO
		printf("5) Listado por t%ctulo\n",161);
		printf("6) Listado por autor\n");
		printf("7) Listado por contenido\n");
		printf("8) Terminar\n");
		printf("Indica la opci%cn deseada :"); scanf("%d",&op); gets(falso);
		if (op==1) pide_datos();
		if (op==2) consulta_nodo();
		if (op==3) elimina_especifico();
		if (op==4) ordenar_listas(1);
		if (op==5) ordenar_listas(2);
		if (op==6) ordenar_listas(3);
		if (op==7) ordenar_listas(4);
	}
}

main(){
	cargarArch();
	menu();
}