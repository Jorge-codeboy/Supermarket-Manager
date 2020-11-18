#include <conio.h>
#include <stdio.h>
#include <String.h>
#include <ctype.h> // tolower()
#include <fstream>

using namespace std;

///////////////////////// Estructura productos.txt
/*
|  FIELD             |  TYPE  |   SIZE  |  NAME  |
|--------------------|--------|---------|--------|
| Clave              | int    | 5       | cveP   |
| Nombre             | char   | 20      | nom    |
| Familia            | char   | 20      | fam    |
| Unidad de Medida   | char   | 20      | um     |
| Precio Unitario    | int    | 6       | pu     |
| Existencia Inicial | int    | 6       | ei     |
| Existencia Actual  | int    | 6       | ea     |
| Stock Minimo       | int    | 6       | smin   |
| Stock Maximo       | int    | 6       | smax   |
*/


/////////////////////// Estructura movimientos.txt
/*
|  FIELD             |  TYPE  |   SIZE  |  NAME  |
|--------------------|--------|---------|--------|
| Clave              | int    | 5       | cveM   |
| Fecha              | char   | 10      | fecha  |
| Cantidad           | int    | 6       | cant   |
| Tipo de Movimiento | char   | 1       | tipo   |
| Sub-tipo de Mov.   | char   | 1       | stipo  |
*/

//////////////////////////////// Nodo de Productos
struct NodoP {
    NodoP *prevP, *nextP;
    int cveP, pu, ei, ea, smin, smax;
    char nom[21], fam[21], um[21];
};


////////////////////////////// Nodo de Movimientos
struct NodoM {
    NodoM *prevM, *nextM;
    int cveM, cant;
    char fecha[11], tipo[2], stipo[2];
};


///////////////////////////////// Global Variables
char falso[2];
/////////////////////// Productos
int cveP, pu, ei, ea, smin, smax;
char nom[21], fam[21], um[21];
///////////////////// Movimientos
int cveM, cant;
char fecha[11], tipo[2], stipo[2];
///////////////////// Apuntadores
NodoP *nwP, *headP, *tailP;
NodoM *nwM, *headM, *tailM;




class sprmkt {
    public:
        void menuArchivosP() {
            char op;
            
            do{
                printf("\n\n");
                printf("---------------------------------------------------\n");
                printf("--------------MENU ARCHIVO DE PRODUCTOS------------\n");
                printf("---------------------------------------------------\n");
                printf("a) Alta productos nuevos\n");
                printf("b) Baja productos obsoletos\n");
                printf("c) Consulta productos por clave\n");
                printf("d) Consulta productos por familia\n");
                printf("x) Terminar\n");
                printf("---------------------------------------------------\n");
                printf("Indica la opci%cn : ",162); op=getchar(); fflush(stdin);  
                printf("---------------------------------------------------\n");
                op = tolower( (int) op);
                switch(op){
                    case 'a': alta_productos(); getchar(); break;
                    //case 'b':muestra(); break;
                    //case 'c':promedio(1); break;
                    case 'x': menuP(); break;
                    
                }
            }while(op !='x');        
        }

        void menuES(){
            char op;
            
            do{
                printf("\n\n");
                printf("------------------------------------------------------------\n");
                printf("--------------MENU ENTRADAS/SALIDAS DE PRODUCTOS------------\n");
                printf("------------------------------------------------------------\n");
                printf("a) Entradas por compras\n");
                printf("b) Entradas por devolucion de clientes\n");
                printf("c) Salidas por ventas\n");
                printf("d) Salidas por devolucion a provedores\n");
                printf("e) Salidas por mermas\n");
                printf("x) Terminar\n");
                printf("-----------------------------------------------------------\n");
                printf("Indica la opci%cn : ",162); op=getchar(); fflush(stdin);
                printf("-----------------------------------------------------------\n");
                op = tolower( (int) op);
                switch(op){
                    case 'a':printf("aaaaaa"); getchar(); break;
                    //case 'b':muestra(); break;
                    //case 'c':promedio(1); break;
                    case 'x': menuP(); break;
                }
            }while(op!='x');        
        }    

        void menuReportes(){
            char op;
            
            do{
                printf("\n\n");
                printf("---------------------------------------------------\n");
                printf("--------------MENU REPORTES------------------------\n");
                printf("---------------------------------------------------\n");
                printf("a) General de productos ordenado por clave\n");
                printf("b) General de productos ordenado por nombre\n");
                printf("c) Productos por familia\n");
                printf("d) Productos a ordenar por existencia\n");
                printf("e) Productos a ofertar por existencia\n");
                printf("f) Listado de movimientos de un producto por fecha\n");
                printf("x) Terminar\n");
                printf("---------------------------------------------------\n");
                printf("Indica la opci%cn : ",162); op=getchar(); fflush(stdin);
                printf("---------------------------------------------------\n");
                op = tolower( (int) op);
                switch(op){
                    case 'a':printf("aaaaaa"); getchar(); break;
                    //case 'b':muestra(); break;
                    //case 'c':promedio(1); break;
                    
                }
            }while(op!='x');        
        }


        void menuP(){
            
            carga_archivos();

            char op;
            
            do{
                printf("\n\n");
                printf("---------------------------------------------------\n");
                printf("-------------------MENU PRINCIPAL------------------\n");
                printf("---------------------------------------------------\n");
                printf("a) Archivos Productos\n");
                printf("b) Entradas/Salidas de Producto\n");
                printf("c) Reportes\n");
                printf("x) Terminar\n");
                printf("---------------------------------------------------\n");
                printf("Indica la opci%cn : ",162); op=getchar(); fflush(stdin);
                printf("---------------------------------------------------\n");
                op = tolower( (int) op);
                switch(op) {
                    case 'a':menuArchivosP(); break;
                    case 'b':menuES(); break;
                    case 'c':menuReportes(); break;
                    case 'x':exit(0); break;
                }
                        
            } while(op!='x');

        }

        void carga_archivos() {
            ifstream archP;
            archP.open("productos.txt", ios::in);

            while (archP >> cveP >> nom >> fam >> um >> pu >> ei >> ea >> smin >> smax) {
                nwP = new NodoP;
                nwP->cveP = cveP;
                strcpy(nwP->nom, nom);
                strcpy(nwP->fam, fam);
                strcpy(nwP->um, um);
                nwP->pu = pu;
                nwP->ei = ei;
                nwP->ea = ea;
                nwP->smin = smin;
                nwP->smax = smax;
                
                nwP->nextP = NULL;
                nwP->prevP = NULL;

                if (headP == NULL) {
                    headP = nwP;
                    tailP = nwP;
                }
                else {
                    tailP -> nextP = nwP;
                    nwP -> prevP = tailP;
                    tailP = nwP;
                }
            }
            ifstream archM;
            archP.open("movimientos.txt", ios::in);

            while (archM >> cveM >> fecha >> cant >> tipo >> stipo) {
                nwM = new NodoM;
                nwM->cveM = cveM;
                strcpy(nwM->fecha, fecha);
                nwM->cant = cant;
                strcpy(nwM->tipo, tipo);
                strcpy(nwM->stipo, stipo);
                
                nwM->nextM = NULL;
                nwM->prevM = NULL;

                if (headM == NULL) {
                    headM = nwM;
                    tailM = nwM;
                }
                else {
                    tailM -> nextM = nwM;
                    nwM -> prevM = tailM;
                    tailM = nwM;
                }
            }
        }

        void alta_productos() {}
        
        void busca_producto() {}

};

int main() {

////////////////////////// Opens and closes files   
    ofstream archP;
    archP.open("productos.txt", ios::app);
    archP.close();

    ofstream archM;
    archM.open("movimientos.txt", ios::app);
    archM.close();

///////////////////////////// Starts the program  
    sprmkt start;
    start.menuP();
    return 0;
}