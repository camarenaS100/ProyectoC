#include <stdio.h>
#include <stdlib.h>
#include <string.h>

                                                                         // Definición de tipos                                          
typedef struct {                                                        //. {
    int dia;                                                            //.    
    char mes[50];                                                       //.
    int anio;                                                           //. }
}FECHA;                                                                  // FECHA
                                                                        //.--------(^)
typedef struct {                                                        //. {
    char nombre[150];                                                   //. 
    char categoria[150];                                                //.
    int codigo;                                                         //.
    int existencia;                                                     //.         
    double precio_compra;                                               //.   
    double precio_venta;                                                //.   
    FECHA caducidad;                                                    //. }
}PRODUCTO;                                                               // PRODUCTO
                                                                        //.---------(^)
struct {                                                                //. {   
    PRODUCTO *productos;                                                //.   
    int N;                                                              //. }  
}BD;                                                                     // BASE DE DATOS
                                                                        //.---------(^)
void prueba() {                                                          // PRUEBAS  
    for (int i = 0; i < BD.N; i++) {                                    //. {          
        printf("%s\n", BD.productos[i].nombre);                         //.           
    }                                                                   //.  
}                                                                       //. } 
// Funciones auxiliares                                                 //.---------(^)       
void showData(int n, PRODUCTO producto) {                                // IMPRIMIR PRODUCTO
    printf("-----PRODUCTO-%i:\n", n);                                   //. {
    printf("%s\n", producto.nombre );                                   //.   
    printf("%s\n", producto.categoria);                                 //.       
    printf("%i\n", producto.codigo);                                    //.   
    printf("%i\n", producto.existencia);                                //.   
    printf("%lf\n", producto.precio_compra);                            //.   
    printf("%lf\n", producto.precio_venta);                             //.       
    printf("---CADUCIDAD\n");                                           //.       
    printf("%i\n", producto.caducidad.dia);                             //.       
    printf("%s\n", producto.caducidad.mes);                             //.           
    printf("%i\n", producto.caducidad.anio);                            //.
}                                                                       //. }
                                                                        //.----------(^)
void showAllData(int n, PRODUCTO data[]) {                               // IMPRIMIR TODOS LOS PRODUCTOS
    for(int i = 0; i < n; i++) {                                        //. {          
        showData(i+1, data[i]);                                         //.   
    }                                                                   //.   
}                                                                       //.       
                                                                        //.----------(^)

void readBinFile() {                                                    //. Leer Datos de la DB
	FILE *file;                                                         //. {  
	file = fopen("Data.bin", "r+b");                                    //.           
                                                                        //.   
	fread(&BD.N, sizeof(int), 1, file);                                 //.   
	BD.productos = malloc(sizeof(PRODUCTO)*BD.N);                       //.
	fread(BD.productos, sizeof(PRODUCTO), BD.N, file);                  //.   
	fclose(file);                                                       //.   
}                                                                       //. } 
                                                                        //.-----------(^)  
void addProduct(PRODUCTO product) {                                      // AGREGAR PRODUCTO
    PRODUCTO *tmp;                                                      //. {      
    BD.N++;                                                             //.
    tmp = realloc(BD.productos, sizeof(PRODUCTO)*BD.N);                 //.           
    BD.productos = tmp;                                                 //.   
    BD.productos[BD.N-1] = product;                                     //.       
}                                                                       //. }  
                                                                        //. ----------(^)  
void deleteProduct(int id) {                                             // BORRAR PRODUCTO
    PRODUCTO *newData;                                                  //. {
    newData = malloc(sizeof(PRODUCTO)*BD.N-1);                          //.   
    int aux = 0;                                                        //.   
    for(int i = 0; i < BD.N; i++) {                                     //.
        if(id != BD.productos[i].codigo) {                              //.
            newData[aux] = BD.productos[i];                             //.
            aux++;                                                      //.
        }                                                               //.       
    }                                                                   //.   
    BD.N--;                                                             //.   
    BD.productos = newData;                                             //.       
}                                                                       //. }
                                                                        //. ----------(^)
void searchProductById(int id) {                                         // BUSCAR PRODUCTO ID
    for(int i = 0; i < BD.N; i++) {                                     //. {  
        if(id == BD.productos[i].codigo) {                              //.       
            showData(i+1, BD.productos[i]);                             //.   
            break;                                                      //.   
        }                                                               //.   
    }                                                                   //.       
}                                                                       //. } 
                                                                        //. ----------(^)      
void searchProductByName(char name[150]) {                               // BUSCAR PRODUCTO NOMBRE
    for(int i = 0; i < BD.N; i++) {                                     //.
        if(strcmp(name, BD.productos[i].nombre) == 0) {                 //.
            showData(i+1, BD.productos[i]);                             //.       
            break;                                                      //.       
        }                                                               //.   
    }                                                                   //.
}                                                                       //.
                                                                        //.-----------(^)
// Crear una instancia de los structs                                    // CREAR PRODUCTO
PRODUCTO createAProduct(char n[150], char cat[150], int cod, int e, double pc, double pv, FECHA date) {
    PRODUCTO product = { "", "", cod, e, pc, pv, date.dia, "", date.anio };
    strcpy(product.nombre, n);                                          //.   
    strcpy(product.categoria, cat);                                     //.
    strcpy(product.caducidad.mes, date.mes);                            //.
    return product;                                                     //.   
}                                                                       //.
                                                                        //.-----------(^)   
FECHA createADate(int day, char month[50], int year) {                   // CREAR FECHA
    FECHA date = { day, "", year };                                     //. {              
    strcpy(date.mes, month);                                            //.   
    return date;                                                        //.       
}                                                                       //. }   
                                                                        //.-----------(^)
 
double* totalcapitalpp()		// 7 ¿Cual es el capital invertido en los productos de la tienda?    Capital invertido en cada producto, y total de inversión
{
	double *total = malloc(sizeof(double)*BD.N);
    for(int i=0; i<BD.N; i++)
    {
        total[i] = BD.productos[i].precio_compra*BD.productos[i].existencia; 
    }
    return total;
}

/*(int totalcapitalpt()		
{
	int i;
    int totalc[i];
    for(i=1; i<=BD.N; i++)
    {
        totalc[i] = total[0] + total[i]; 
    }
}*/

double* ganancia() 						// 8 ¿Cual es la ganancia total de los productos en la tienda?		Capital ganado 
{   //double *total = malloc(sizeof(double)*BD.N);
    double *winnings = malloc(sizeof(double)*BD.N);
	 for(int i=0; i<BD.N; i++)
    {			//	  [(	 precio de venta	 )-(  precio de compra	       )](							)
        winnings[i] = (BD.productos[i].precio_venta-BD.productos[i].precio_compra)*BD.productos[i].existencia;
	}
    return winnings;
}

int main(void) {                                                         // MAIN   
    readBinFile();                                                      //. {  
    /*FECHA fecha = createADate(20, "Agosto", 2020);                      //.   
    PRODUCTO producto = createAProduct("Seven-up", "bebidas", 2139013, 10, 10.00, 12.00, fecha);
    addProduct(producto);                                               //.           
    deleteProduct(22911095);                                            //.
    prueba();*/     
    double* arr = totalcapitalpp();                                                      //.
	for (int i = 0; i<BD.N ; i++)
	{
		printf("%lf ", arr[i]);
	}
	free(arr);

    double* arre = ganancia();                                                      //.
	for (int i = 0; i<BD.N ; i++)
	{
		printf("%lf ", arre[i]);
	}
	free(arre);


	//int total = totalcapitalpp();
    //totalcapitalpt(total);                                                                    //.   
    return 0;                                                           //.   
}                                                                       //. }  
                                                                        //.-----------(^) 