#include <conio.h>
#include <stdio.h>
#include <String.h>

class SprmktUI{
    public:
    void menuArchivosP(){
        char op;
        
        do{
            printf("---------------------------------------------------\n");
            printf("--------------MENU ARCHIVO DE PRODUCTOS------------\n");
            printf("---------------------------------------------------\n");
            printf("a) Alta productos nuevoss\n");
            printf("b) Baja productos obsoletos\n");
            printf("c) Consulta productos por clave\n");
            printf("d) Consulta productos por familia\n");
            printf("x) terminar\n");
            printf("---------------------------------------------------\n");
            printf("Indica la opci%cn : ",162); op=getche(); printf("\n");
            printf("---------------------------------------------------\n");
            switch(op){
                case 'a':printf("aaaaaa"); getche(); break;
                //case 'b':muestra(); break;
                //case 'c':promedio(1); break;
                
            }
        }while(op!='x');        
    }

    void menuES(){
        char op;
        
        do{
            printf("------------------------------------------------------------\n");
            printf("--------------MENU ENTRADAS/SALIDAS DE PRODUCTOS------------\n");
            printf("------------------------------------------------------------\n");
            printf("a) Entradas por compras\n");
            printf("b) Entradas por devolucion de clientes\n");
            printf("c) Salidas por ventas\n");
            printf("d) Salidas por devolucion a provedores\n");
            printf("e) Salidas por mermas\n");
            printf("x) terminar\n");
            printf("---------------------------------------------------\n");
            printf("Indica la opci%cn : ",162); op=getche(); printf("\n");
            printf("---------------------------------------------------\n");
            switch(op){
                case 'a':printf("aaaaaa"); getche(); break;
                //case 'b':muestra(); break;
                //case 'c':promedio(1); break;
                
            }
        }while(op!='x');        
    }    

    void menuReportes(){
        char op;
        
        do{
            printf("---------------------------------------\n");
            printf("--------------MENU REPORTES------------\n");
            printf("---------------------------------------\n");
            printf("a) General de productos ordenado por clave\n");
            printf("b) General de productos ordenado por nombre\n");
            printf("c) Productos por familia\n");
            printf("d) Productos a ordenar por existencia\n");
            printf("e) Productos a ofertar por existencia\n");
            printf("f) Listado de movimientos de un producto por fecha\n");
            printf("x) terminar\n");
            printf("---------------------------------------------------\n");
            printf("Indica la opci%cn : ",162); op=getche(); printf("\n");
            printf("---------------------------------------------------\n");
            switch(op){
                case 'a':printf("aaaaaa"); getche(); break;
                //case 'b':muestra(); break;
                //case 'c':promedio(1); break;
                
            }
        }while(op!='x');        
    }    

    void menuP(){
        
        char op;
        
        do{
            printf("---------------------------------------------------\n");
            printf("-------------------MENU PRINCIPAL-------------------\n");
            printf("---------------------------------------------------\n");
            printf("1) Archivos Productos\n");
            printf("2) Entradas/Salidas de Producto\n");
            printf("3) Reportes\n");
            printf("4) terminar\n");
            printf("---------------------------------------------------\n");
            printf("Indica la opci%cn : ",162); op=getche(); printf("\n");
            printf("---------------------------------------------------\n");
            switch(op){
                case 'a':this->menuArchivosP(); getche(); break;
                case 'b':this->menuES(); break;
                case 'c':this->menuReportes(); break;
                
            }
        }while(op!='x');
    }




};

main(){
    SprmktUI p;
    p.menuP();
}