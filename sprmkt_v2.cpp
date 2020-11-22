#include <conio.h>
#include <stdio.h>
#include <String.h>
#include <ctype.h> // tolower()
#include <fstream>
#include <time.h>

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
    char fecha[11];
    char tipo, stipo;
};


///////////////////////////////// Global Variables
char falso[2];
bool flag;
/////////////////////// Productos
int cveP, pu, ei, ea, smin, smax;
char nom[21], fam[21], um[21];
///////////////////// Movimientos
int cveM, cant;
char fecha[11];
char tipo, stipo;
///////////////////// Apuntadores
NodoP *nwP, *headP, *tailP, *currentP;
NodoM *nwM, *headM, *tailM, *currentM, *lastM;

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++++++++++++++++++++++ TO DO +++++++++++++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// done, tested, descarga_productos()
// done, NOT tested, descarga_movimientos()
// casting for pu needed
// la celebración ha terminado eliminar
// casting forzado de cve


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
                    case 'a': alta_productos(); break;
                    case 'b': baja_productos(); break;
                    case 'c': if (!busca_atributo_P("ConsultaCveP")) show_error("La clave NO pudo ser localizada"); break;
                    case 'd': if (!busca_atributo_P("ConsultaFamP")) show_error("La familia NO pudo ser localizada"); break;
                    case 'x': menuP(); break;

                    default: show_error("Opcion No Valida");
                    
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
                    case 'a':dec_movimiento(1); break;
                    case 'b':dec_movimiento(2); break;
                    case 'c':dec_movimiento(3); break;
                    case 'd':dec_movimiento(4); break;
                    case 'e':dec_movimiento(5); break;
                    case 'x': menuP(); break;
                    default: show_error("Opcion No Valida");
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
                    case 'a':ordenarp(1); break;
                    case 'b':ordenarp(2); break;
                    case 'c': if (!busca_atributo_P("ConsultaFamP")) show_error("La familia NO pudo ser localizada"); break;
                    case 'd':ordenarp(3); break;
                    case 'e':ordenarp(4); break;
                    case 'f':listadomf(); break;
                    case 'x': menuP(); break;
                    default: show_error("Opcion No Valida");
                }
            }while(op!='x');        
        }

        void menuP(){
            
            

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
                    default: show_error("Opcion No Valida");
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
                    headP -> nextP = NULL;
                    headP -> prevP = NULL;
                    tailP -> nextP = NULL;
                    tailP -> prevP = NULL;
                }
                else {
                    tailP -> nextP = nwP;
                    nwP -> prevP = tailP;
                    tailP = nwP;
                    nwP->nextP=NULL;
                }
            }
            archP.close();

            ifstream archM;
            archM.open("movimientos.txt", ios::in);

            while (archM >> cveM >> fecha >> cant >> tipo >> stipo) {
                nwM = new NodoM;
                nwM->cveM = cveM;
                strcpy(nwM->fecha, fecha);
                nwM->cant = cant;
                nwM->tipo= tipo;
                (nwM->stipo= stipo);
                
                nwM->nextM = NULL;
                nwM->prevM = NULL;

                if (headM == NULL) {
                    headM = nwM;
                    tailM = nwM;
                    headM -> nextM = NULL;
                    headM -> prevM = NULL;
                    tailM -> nextM = NULL;
                    tailM -> prevM = NULL;


                }
                else {
                    tailM -> nextM = nwM;
                    nwM -> prevM = tailM;
                    tailM = nwM;
                    nwM->nextM=NULL;
                }
            }
            archM.close();
        }

        void descarga_productos() {
            
            ofstream archP;
            archP.open("productos.txt", ios::out);
            
            //printf( "pre currentP->cve : %d \n",currentP->cveP);
            //printf( "pre headP currentP->cve : %d \n",headP->cveP);
            currentP = headP;
            //int times =1;
            //printf( "currentP->cve : %d \n",currentP->cveP);
            

            while(currentP != NULL){
                //printf("got in %d \n",times);
                //times = times+1;

                for(int i=0;i<(strlen(currentP->nom));i++) if (currentP->nom[i] == ' ') currentP->nom[i] ='_';
                for(int i=0;i<(strlen(currentP->fam));i++) if (currentP->fam[i] == ' ') currentP->fam[i] ='_';
                for(int i=0;i<(strlen(currentP->um));i++) if (currentP->um[i] == ' ') currentP->um[i] ='_';
                archP << currentP->cveP <<" "<< currentP->nom << " " << currentP->fam << " " <<currentP->um << " "<<currentP->pu<<" "<<currentP->ei<<" "<<currentP->ea<<" "<<currentP->smin<<" "<<currentP->smax<<"\n";
                currentP = currentP->nextP; 

            }
            archP.close();

        }

        void descarga_movimientos() {
            currentM = headM;
            ofstream archM;
            archM.open("movimientos.txt", ios::out);

            


            while(currentM != NULL){

                for(int i=0;i<(strlen(currentM->fecha));i++) if (currentM->fecha[i] == ' ') currentM->fecha[i] ='_';
                archM << currentM->cveM <<" "<<currentM->fecha<<" "<<currentM->cant<<" "<<currentM->tipo<<" "<<currentM->stipo<<"\n";
                currentM = currentM->nextM; 

            }
            archM.close();
        }
        
        void alta_productos() {


            // cveP validation!
            flag = true;

            while (flag) {
                
                if (busca_atributo_P("BuscaCveP")) show_error( (char *) "La clave del producto se duplica en la base de datos.");
    
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

                printf("Indica el Precio Unitario del producto -> "); scanf("%d", &pu); gets(falso);
                if ((pu < 1) || (pu > 999999)) show_error( (char *) "El Precio Unitario es mayor a 999,999 o menor a 1.");

                else flag = false;
            }

            
            // ei validation!
            flag = true;

            while (flag) {
                
                printf("Indica la Existencia Inicial del producto -> "); scanf("%d", &ei); gets(falso);

                if ((ei < 1) || (ei > 999999)) show_error( (char *) "La Existencia Inicial es mayor a 999,999 o menor a 1.");

                else flag = false;
            }

            // ea

            ea = ei;
            
            // smin validation!
            flag = true;

            while (flag) {
                
                printf("Indica el Stock M%cnimo del producto -> ", 161); scanf("%d", &smin); gets(falso);

                if ((smin < 1) || (smin > 999999)) show_error( (char *) "El Stock Min. es mayor a 999,999 o menor a 1.");

                else flag = false;
            }

            // smax validation!
            flag = true;

            while (flag) {
                
                printf("Indica el Stock M%cximo del producto -> ", 160); scanf("%d", &smax); gets(falso);

                if ((smax < 1) || (smax > 999999)) show_error( (char *) "El Stock Max. es mayor a 999,999 o menor a 1.");

                else flag = false;
                
            }

            nwP = new NodoP;

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
            
            //// Pointers
            nwP -> nextP = NULL;
            nwP -> prevP = NULL;
            
            // Case 1: List is empty
            if (headP == NULL)  {
                headP = nwP;
                tailP = nwP;

                headP -> nextP = NULL;
                headP -> prevP = NULL;
                tailP -> nextP = NULL;
                tailP -> prevP = NULL;
            }
            
            // Case 2: List is NOT empty
            else {
                tailP -> nextP = nwP;
                nwP -> prevP = tailP;
                tailP = nwP;
                nwP->nextP=NULL;
            }

            descarga_productos();
          //  descarga_movimientos();
            
        }

        void baja_productos(){
            
            ///int num_bajas;    


            if (!busca_atributo_P("BuscaCveP")) {
                show_error( (char *) "La clave del producto no existe.");
                
            }
            
            else{
                elimina_movimiento(currentP->cveP);
                
                if (currentP==headP){
                    if (headP==tailP){
                        headP=NULL;
                        tailP=NULL;
                        delete(currentP);
                    }
                    else{
                        currentP=headP;
                        headP=headP->nextP;
                        headP->prevP=NULL;
                        
                        delete(currentP);
                    }
			    }

                else{
                    if (currentP==tailP) {
                        if (headP==tailP){
                            headP=NULL;
                            tailP=NULL;
                            delete(currentP);
                        }
                        else{
                            currentP=tailP;
                            tailP=currentP->prevP;
                            tailP->nextP=NULL;
                            delete(currentP);
                        }
                        
                    }

                    else{
                        currentP->prevP->nextP = currentP->nextP;
                        currentP->nextP->prevP = currentP->prevP;
                        delete(currentP);
                    }                   

                }
            }

            descarga_productos();
            descarga_movimientos();

    






               
                    
            
        }
        
        void show_error(char *mssg) {
            printf("\n");
            printf("[ERROR] ");
            printf("%s\n", mssg);
            printf("[ENTER] para continuar ...");
            printf("\n");
            getchar(); fflush(stdin);
        }

        void show_message(char *mssg) {
            printf("\n");
            printf("%s\n", mssg);
            printf("[ENTER] para continuar ...");
            printf("\n");
            getchar(); fflush(stdin);
        }

        bool busca_atributo_P(char *op) {
            // Searches for op in Productos Linked List, returns a bool depending on the search
            bool encontrado = false;

            // 1. Defines currentP
            currentP = headP;

            // 2. Asks for attribute to search based on op

            if ((strcmp(op, "BuscaCveP") == 0) || (strcmp(op, "ConsultaCveP") == 0) || (strcmp(op, "ConsultaCvePM") ==0 )) {

                printf("Indica la clave del producto -> "); scanf("%d", &cveP); gets(falso);

            }

            if ((strcmp(op, "ConsultaFamP") == 0)) {

                printf("Indica la familia a consultar -> "); gets(fam);
                for(int i=0;i<(strlen(fam));i++) if (fam[i] == ' ') fam[i] ='_';

                printf("\n\n");
                printf("             FAMILIA | CLAVE |               NOMBRE |                   UM |     PU |     EI |     EA |   SMIN |   SMAX |\n");
                printf("-------------------------------------------------------------------------------------------------------------------------\n");
                 printf("-------------------------------------------------------------------------------------------------------------------------\n");

            }
            
            // 3. Loops through Productos Linked List
            while (currentP != NULL) {
            
                // 4. Checks for attributes based on op
                if ((strcmp(op, "BuscaCveP") == 0)) {
                    if (cveP == currentP->cveP) return true;
                }
    
                if ((strcmp(op, "ConsultaCveP") == 0)) {
                    
                    if (cveP == currentP->cveP) {


                        // Changes _ for visualization
                        for(int i=0;i<(strlen(currentP->nom));i++) if (currentP->nom[i] == '_') currentP->nom[i] =' ';
                        for(int i=0;i<(strlen(currentP->fam));i++) if (currentP->fam[i] == '_') currentP->fam[i] =' ';
                        for(int i=0;i<(strlen(currentP->um));i++) if (currentP->um[i] == '_') currentP->um[i] =' ';


                        // Prints search results
                        printf("\n\n");
                        printf("Clave               : %d\n", currentP->cveP);
                        printf("Nombre              : %s\n", currentP->nom);
                        printf("Famila              : %s\n", currentP->fam);
                        printf("Unidad de Medida    : %s\n", currentP->um);
                        printf("Precio Unitario     : %d\n", currentP->pu);
                        printf("Existencia Inicial  : %d\n", currentP->ei);
                        printf("Existencia Actual   : %d\n", currentP->ea);
                        printf("Stock M%cnimo        : %d\n", 161, currentP->smin);
                        printf("Stock M%cximo        : %d\n", 160, currentP->smax);

                        show_message("");
                        return true;
                    }
                }


                if ((strcmp(op, "ConsultaCvePM") == 0)) {
                    
                    if (cveP == currentP->cveP) {


                        // Changes _ for visualization
                        for(int i=0;i<(strlen(currentP->nom));i++) if (currentP->nom[i] == '_') currentP->nom[i] =' ';
                        for(int i=0;i<(strlen(currentP->fam));i++) if (currentP->fam[i] == '_') currentP->fam[i] =' ';
                        for(int i=0;i<(strlen(currentP->um));i++) if (currentP->um[i] == '_') currentP->um[i] =' ';


                        // Prints search results
                        printf("\n\n");
                        printf("Clave               : %d\n", currentP->cveP);
                        printf("Nombre              : %s\n", currentP->nom);
                        printf("Famila              : %s\n", currentP->fam);
                        
                        return(true);
                    }
                }                
                
                if ((strcmp(op, "ConsultaFamP") == 0)) {

                   
                    
                    if ((strcmp(fam, currentP->fam) == 0)) {


                        // Changes _ for visualization
                        for(int i=0;i<(strlen(currentP->nom));i++) if (currentP->nom[i] == '_') currentP->nom[i] =' ';
                        for(int i=0;i<(strlen(currentP->fam));i++) if (currentP->fam[i] == '_') currentP->fam[i] =' ';
                        for(int i=0;i<(strlen(currentP->um));i++) if (currentP->um[i] == '_') currentP->um[i] =' ';


                        // Prints search results
                        
                        printf("%20s | %5d | %20s | %20s | %6d | %6d | %6d | %6d | %6d \n", currentP->fam, currentP->cveP, currentP->nom,  currentP->um, currentP->pu, currentP->ei, currentP->ea, currentP->smin, currentP->smax);
                        printf("-------------------------------------------------------------------------------------------------------------------------\n");
                        
                        encontrado = true;
                    }
                }
                currentP = currentP -> nextP;
            
            }
            if ((strcmp(fam, currentP->fam) == 0)) show_message("La busqueda ha terminado");
            // 5. Iterates
            
            // 6. Returns results
            return encontrado;
        }

        void elimina_movimiento(int cvem) {
            // Searches for cveM in linked list, eliminates the nodeM
            
            currentM = headM;
            NodoM *aux;

            while (currentM != NULL) {

                if (cvem == currentM->cveM){

                    if (currentM == headM){
                        // cas if one node exists
                        if (headM == tailM){
                            headM = NULL;
                            tailM = NULL;
                            delete currentM;
                            currentM=NULL;
                        }

                        else{
                            headM=currentM->nextM;
                            currentM->nextM->prevM = NULL;
                            delete(currentM);
                            currentM=headM;
                            
                            


                        }
                        
                        

                    }
                    else{
                        if(currentM == tailM){

                            if(headM== tailM){
                            headM = NULL;
                            tailM = NULL;
                            delete currentM;
                            currentM=NULL;
                            }

                            else{
                                tailM=currentM->prevM;
                                currentM->prevM->nextM= NULL;
                                delete(currentM);
                                currentM=tailM;

                            }

                        }
                        else{
                            currentM->nextM->prevM = currentM->prevM;
                            currentM->prevM->nextM = currentM->nextM;
                            
                            aux=currentM; 
                            delete currentM;
                            
                            
                            
                            currentM=aux->nextM;
                            delete aux; 
                        }
                      
                    }



                }
                else{
                    
                    currentM = currentM -> nextM;

                }
                
            }
            
        }

        void alta_movimiento(int entradasc,int cveM,char *fecha, char tipo, char stipo){
            

            currentP->ea = currentP->ea + entradasc;
            descarga_productos();
            
            
            
            
            nwM = new NodoM;

            //// INT Atributtes
            nwM -> cveM = cveM;

            nwM -> cant = (-1)*entradasc;

            
            
            //// STR Atributtes
            nwM -> tipo= tipo;
            nwM -> stipo=stipo;
            strcpy(nwM -> fecha,fecha);
            
            //// Pointers
            nwM -> nextM = NULL;
            nwM -> prevM = NULL;
            
            // Case 1: List is empty
            if (headM == NULL)  {
                headM = nwM;
                tailM = nwM;

                headM -> nextM = NULL;
                headM -> prevM = NULL;
                tailM -> nextM = NULL;
                tailM -> prevM = NULL;
            }
            
            // Case 2: List is NOT emMty
            else {
                tailM -> nextM = nwM;
                nwM -> prevM = tailM;
                tailM = nwM;
            }

            descarga_movimientos();


        }

        void obtiene_fecha() {
            time_t tiempo;
            struct tm *tm;
            

            tiempo = time (NULL);
            tm = localtime(&tiempo);
            strftime(fecha, 11, "%d/%m/%Y", tm);
            
        }


        void dec_movimiento(int tipo){
            
            if(!busca_atributo_P("BuscaCveP")){
                show_error("La clave NO pudo ser localizada");
                
            } 
            

            else{

                
                int entradasc;
                printf("Indica cuantas unidades : "); scanf("%d",&entradasc); gets(falso);
                
                

                
                

                obtiene_fecha();
                


                
                
                switch(tipo){
                    case 1: alta_movimiento(entradasc,currentP->cveP,fecha,'E','C'); break;
                    case 2: alta_movimiento(entradasc,currentP->cveP,fecha,'E','D'); break;
                    case 3: entradasc = (-1)*entradasc; alta_movimiento(entradasc,currentP->cveP,fecha,'S','V'); break;
                    case 4: entradasc = (-1)*entradasc; alta_movimiento(entradasc,currentP->cveP,fecha,'S','P'); break;
                    case 5: entradasc = (-1)*entradasc; alta_movimiento(entradasc,currentP->cveP,fecha,'S','P'); break;
                }



                
            }
        }

    
    void ordenarp(int op){

        NodoP *currentPi, *currentPj, *auxP;

        currentPi = headP;
        auxP= new NodoP;
        while(currentPi != NULL){
            currentPj=currentPi->nextP;
            while(currentPj != NULL){
                if(op == 1 && (currentPi->cveP > currentPj->cveP) || \
                (op ==2 && (strcmp(currentPi->nom,currentPj->nom)==1)) || \
                (op == 3 && (currentPi->ea > currentPj->ea) && currentPi->ea <= currentPi->smin && currentPj->ea <= currentPj->smin) ||\
                (op== 4 && (currentPi->ea > currentPj->ea) && currentPi->ea >= currentPi->smax && currentPj->ea >= currentPj->smax)) {

                    auxP->cveP=currentPi->cveP;
                    strcpy(auxP->nom,currentPi->nom);
                    strcpy(auxP->fam,currentPi->fam);
                    strcpy(auxP->um,currentPi->um);
                    auxP->pu=currentPi->pu;
                    auxP->ei=currentPi->ei;                    
                    auxP->ea=currentPi->ea;
                    auxP->smin=currentPi->smin;
                    auxP->smax=currentPi->smax;
                    


                    //---------------------------------------------
                    currentPi->cveP=currentPj->cveP;
                    strcpy(currentPi->nom,currentPj->nom);
                    strcpy(currentPi->fam,currentPj->fam);
                    strcpy(currentPi->um,currentPj->um);
                    currentPi->pu=currentPj->pu;
                    currentPi->ei=currentPj->ei;                    
                    currentPi->ea=currentPj->ea;
                    currentPi->smin=currentPj->smin;
                    currentPi->smax=currentPj->smax;
	
                    //-----------------------------------------------
                    currentPj->cveP=auxP->cveP;
                    strcpy(currentPj->nom,auxP->nom);
                    strcpy(currentPj->fam,auxP->fam);
                    strcpy(currentPj->um,auxP->um);
                    currentPj->pu=auxP->pu;
                    currentPj->ei=auxP->ei;                    
                    currentPj->ea=auxP->ea;
                    currentPj->smin=auxP->smin;
                    currentPj->smax=auxP->smax;




                }
                currentPj=currentPj->nextP;
            }
            currentPi=currentPi->nextP;
        }

        listado_generalP(op);



    }




    void listado_generalP(int op){

        if (headP==NULL){
            show_error("La lista esta vacia");
        }
        else{
            currentP=headP;
            printf("\n\n");
            printf("CLAVE |              FAMILIA |               NOMBRE |                   UM |     PU |     EI |     EA |   SMIN |   SMAX |\n");
            printf("-------------------------------------------------------------------------------------------------------------------------\n");
            printf("-------------------------------------------------------------------------------------------------------------------------\n");

            while(currentP!=NULL){
                for(int i=0;i<(strlen(currentP->nom));i++) if (currentP->nom[i] == '_') currentP->nom[i] =' ';
                for(int i=0;i<(strlen(currentP->fam));i++) if (currentP->fam[i] == '_') currentP->fam[i] =' ';
                for(int i=0;i<(strlen(currentP->um));i++) if (currentP->um[i] == '_') currentP->um[i] =' ';                
                if( (op==3) && (currentP->ea <= currentP->smin)){
                    
                    printf("%5d | %20s | %20s | %20s | %6d | %6d | %6d | %6d | %6d \n", currentP->cveP, currentP->fam, currentP->nom,  currentP->um, currentP->pu, currentP->ei, currentP->ea, currentP->smin, currentP->smax);
                    printf("-------------------------------------------------------------------------------------------------------------------------\n");
                    currentP=currentP->nextP;
                    continue;                   
                }



                else if((op==4) && (currentP->ea >= currentP->smax)){
                    printf("%5d | %20s | %20s | %20s | %6d | %6d | %6d | %6d | %6d \n", currentP->cveP, currentP->fam, currentP->nom,  currentP->um, currentP->pu, currentP->ei, currentP->ea, currentP->smin, currentP->smax);
                    printf("-------------------------------------------------------------------------------------------------------------------------\n");
                    currentP=currentP->nextP;
                    continue; 

                }

                else if((op!=3) && (op!=4)){

                    printf("%5d | %20s | %20s | %20s | %6d | %6d | %6d | %6d | %6d \n", currentP->cveP, currentP->fam, currentP->nom,  currentP->um, currentP->pu, currentP->ei, currentP->ea, currentP->smin, currentP->smax);
                    printf("-------------------------------------------------------------------------------------------------------------------------\n");
                    
                
                    currentP=currentP->nextP;
                }
                


            }
        }
        show_message("");
 
 
    }


    void listadomf(){
        if (!busca_atributo_P("ConsultaCvePM")) show_error("La clave NO pudo ser localizada");

      
        currentM=headM;
        printf("\n\n");
        printf("FECHA      |   CANTIDAD | ENTRADA/SALIDA | SUB TIPO |\n");
        printf("-------------------------------------------------------------------------------------------------------------------------\n");
        printf("-------------------------------------------------------------------------------------------------------------------------\n"); 

        

        while(currentM!=NULL){
            if(currentM->cveM == currentP->cveP){
                printf("%10s | %6d     |              %c |    %c \n", currentM->fecha, currentM->cant,  currentM->tipo, currentM->stipo);
                printf("-------------------------------------------------------------------------------------------------------------------------\n");

            }

            
            
        
            currentM=currentM->nextM;
        }
        show_message("");   


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
    start.carga_archivos();
    start.menuP();
    return 0;
}