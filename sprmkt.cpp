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
bool flag;
/////////////////////// Productos
int cveP, pu, ei, ea, smin, smax;
char nom[21], fam[21], um[21];
///////////////////// Movimientos
int cveM, cant;
char fecha[11], tipo[2], stipo[2];
///////////////////// Apuntadores
NodoP *nwP, *headP, *tailP, *currentP;
NodoM *nwM, *headM, *tailM, *currentM;

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++++++++++++++++++++++ TO DO +++++++++++++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// descarga_productos()
// descarga_movimientos()
// baja_productos()


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
                printf("Indica la opci%cn : ", 162); op = getchar(); fflush(stdin);  
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


        void descarga_productos() {
        }

        void descarga_movimientos() {

        }
        void alta_productos() {


            // cveP validation!
            flag = true;

            while (flag) {
                
                if (!busca_producto()) show_error( (char *) "La clave del producto se duplica en la base de datos.");
    
                else if ((cveP < 1) || (cveP > 99999)) show_error( (char *) "La clave del producto es mayor a 99,999 o menor a 1.");

                else flag = false;
            }

            // nombre validation!
            flag = true;

            while (flag) {
                
                printf("Indica Nombre del producto -> "); gets(nom);
                int l = strlen(nom);
                
                if ((l < 1) || (l > 20)) show_error( (char *) "El Nombre debe tener entre 1 y 20 caracteres.");

                else flag = false;
            }

            // fam validation!
            flag = true;

            while (flag) {
                
                printf("Indica Familia del producto -> "); gets(fam);
                int l = strlen(fam);
                
                if ((l < 1) || (l > 20)) show_error( (char *) "La Familia debe tener entre 1 y 20 caracteres.");

                else flag = false;
            }

            // um validation!
            flag = true;

            while (flag) {
                
                printf("Indica Unidad de Medida del producto -> "); gets(um);
                int l = strlen(um);
                
                if ((l < 1) || (l > 20)) show_error( (char *) "El Unidad de Medida debe tener entre 1 y 20 caracteres.");

                else flag = false;
            }

            // pu validation!
            flag = true;

            while (flag) {

                printf("Indica el Precio Unitario del producto ->"); scanf("%d", &pu); gets(falso);
                if ((pu < 1) || (pu > 999999)) show_error( (char *) "El Precio Unitario es mayor a 999,999 o menor a 1.");

                else flag = false;
            }

            
            // ei validation!
            flag = true;

            while (flag) {
                
                printf("Indica la Existencia Inicial del producto ->"); scanf("%d", &ei); gets(falso);

                if ((ei < 1) || (ei > 999999)) show_error( (char *) "La Existencia Inicial es mayor a 999,999 o menor a 1.");

                else flag = false;
            }

            // ea

            ea = ei;
            
            // smin validation!
            flag = true;

            while (flag) {
                
                printf("Indica el Stock M%cnimo del producto ->", 161); scanf("%d", &smin); gets(falso);

                if ((smin < 1) || (smin > 999999)) show_error( (char *) "El Stock Min. es mayor a 999,999 o menor a 1.");

                else flag = false;
            }

            // smax validation!
            flag = true;

            while (flag) {
                
                printf("Indica el Stock M%cximo del producto ->", 160); scanf("%d", &smax); gets(falso);

                if ((smax < 1) || (smax > 999999)) show_error( (char *) "El Stock Max. es mayor a 999,999 o menor a 1.");

                else flag = false;
            }
            //// Pointers 
            nwP = new NodoP;
            nwP -> nextP = NULL;
            tailP -> nextP = nwP;
            nwP -> prevP = tailP;

            //// INT Atributtes
            nwP -> cveP = cveP;
            nwP -> pu = pu;
            nwP -> ei = ei;
            nwP -> ea = ea;
            nwP -> smin = smin;
            nwP -> smax = smax;
            
            //// STR Atributtes
            strcpy(nwP -> nom, nom);
            strcpy(nwP -> fam, fam);
            strcpy(nwP -> um, um);
             
            tailP = nwP;

            descarga_productos();
            descarga_movimientos();

        }
        
        void show_error(char *mssg) {
            printf("\n");
            printf("[ERROR] ");
            printf(mssg);
            printf("[ENTER] para continuar ...");
            printf("\n");
            getchar(); fflush(stdin);
        }

        bool busca_producto() {
            // Searches for cveP in linked list, returns a bool depending on the search

            printf("Indica la clave del producto ->"); scanf("%d", &cveP); gets(falso);

            currentP = tailP;

            while (currentP != NULL) {

                if (cveP == currentP->cveP) return true;
                currentP = currentP -> prevP;
            }
            return false;
        }

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