#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Definición de tipos
typedef struct {
    int dia;
    char mes[50];
    int anio;
}FECHA;

typedef struct {
    char nombre[150];
    char categoria[150];
    int codigo;
    int existencia;
    double precio_compra;
    double precio_venta;
    FECHA caducidad;
}PRODUCTO;

typedef struct {
    PRODUCTO *productos;
    int N;
}BD;


// Funciones auxiliares
BD BDConstructor() {
    BD bd;
    return bd;
}

int chartoint (char* month, char months[][15]);

        // meses lee los registros de la base de datos dentro de FECHA pero especificamente mes, y compara igualando mes con nombre a un valor numérico
        // regresa cuál mes es mayor entre dos comparaciones y cuántos días tiene cada mes

/*
int meses (BD *bd, PRODUCTO producto){
    char month[50] = producto.caducidad.mes[];
    char monthtwo[50] = producto.caducidad.mes[];

    /*int treintauno[7][15]; = {"Enero", "Marzo", "Mayo", "Julio", "Agosto", "Octubre", "Diciembre"};
    int treinta[4][15] = {"Abril", "Junio", "Septiembre", "Noviembre"};
    int veintiocho[2][15] = {"Febrero"};
    for (int i = 0; i<N; i++)
    {
    printf("mes 1: \n");
    scanf("%s", &month);  //strcpy
    printf("mes 2: \n");
    scanf("%s", &monthtwo);
    }

    int mesUno = charsTonum(month, months);
    int mesDos = charsTonum(monthtwo, months);
    return 1;
}
*/

int chartoint (char* month, char months[][15]){
    for(int i = 0; i < 12; i++)
    {if (strcmp(month,months[i]) == 0 )
        {return i;
        }
    }
}


void showData(int n, PRODUCTO producto) {
    printf("-----PRODUCTO-%i:\n", n);
    printf("%s\n", producto.nombre );
    printf("%s\n", producto.categoria);
    printf("%i\n", producto.codigo);
    printf("%i\n", producto.existencia);
    printf("%lf\n", producto.precio_compra);
    printf("%lf\n", producto.precio_venta);
    printf("---CADUCIDAD\n");
    printf("%i\n", producto.caducidad.dia);
    printf("%s\n", producto.caducidad.mes);
    printf("%i\n", producto.caducidad.anio);
}

void showAllData(int n, PRODUCTO data[]) {
    for(int i = 0; i < n; i++) {
        showData(i+1, data[i]);
    }
}

// Trabajando con archivos binarios
void readBinFile(BD *bd) {
	FILE *file;
	file = fopen("Data.bin", "r+b");

	fread(&bd->N, sizeof(int), 1, file);
	bd->productos = malloc(sizeof(PRODUCTO) * bd->N);
	fread(bd->productos, sizeof(PRODUCTO), bd->N, file);
	fclose(file);
}

void saveBinFile(BD *bd) {
    FILE *file;
	file = fopen("Data.bin", "w+b");

	fwrite(&bd->N, sizeof(int), 1, file);
	fwrite(bd->productos, sizeof(PRODUCTO), bd->N, file);
	fclose(file);
}

// CRUD
void transderData(PRODUCTO *newData, PRODUCTO *oldData) {
    strcpy(newData->nombre, oldData->nombre);
    strcpy(newData->categoria, oldData->categoria);
    newData->codigo = oldData->codigo;
    newData->existencia = oldData->existencia;
    newData->precio_compra = oldData->precio_compra;
    newData->precio_venta = oldData->precio_venta;
    newData->caducidad.dia = oldData->caducidad.dia;
    strcpy(newData->caducidad.mes, oldData->caducidad.mes);
    newData->caducidad.anio = oldData->caducidad.anio;
}

void addProduct(BD *bd, PRODUCTO product) {
    PRODUCTO *tmp;
    bd->N++;
    tmp = realloc(bd->productos, sizeof(PRODUCTO)*bd->N);
    bd->productos = tmp;
    bd->productos[bd->N-1] = product;
}

void deleteProduct(BD *bd, int id) {
    PRODUCTO *newData;
    newData = malloc(sizeof(PRODUCTO)*(bd->N-1));
    int aux = 0;
    for(int i = 0; i < bd->N; i++) {
        if(id != bd->productos[i].codigo) {
            transderData(&newData[aux], &bd->productos[i]);
            // newData[aux] = bd->productos[i];
            aux++;
        }
    }
    bd->N--;
    bd->productos = realloc(bd->productos, bd->N * sizeof(PRODUCTO));
    bd->productos = newData;
}

void searchProductById(BD *bd, int id) {
    for(int i = 0; i < bd->N; i++) {
        if(id == bd->productos[i].codigo) {
            showData(i+1, bd->productos[i]);
            break;
        }
    }
}

double* totalInvestment(BD *bd)	// 7 ¿Cual es el capital invertido en los productos de la tienda?
{
	double *investment = malloc(sizeof(double)*bd->N);
    for(int i=0; i< bd->N; i++)
    {
        investment[i] = bd->productos[i].precio_compra*bd->productos[i].existencia; 
    }
    return investment;
}

double* totalWinnings(BD *bd) // 8 ¿Cual es la ganancia total de los productos en la tienda?
{   
    double *winnings = malloc(sizeof(double)*bd->N);
	 for(int i=0; i < bd->N ; i++)
    {			//	  [(	 precio de venta	 )-(  precio de compra	       )](							)
        winnings[i] = (bd->productos[i].precio_venta-bd->productos[i].precio_compra)*bd->productos[i].existencia;
	}
    return winnings;
}
double* showI(BD *bd)
{
    double* arr = totalInvestment(bd);  
    printf("-----\n");                                      
	for (int i = 0; i < bd->N ; i++)
	{
		printf("La inversión total en el producto %i fue de $%.2lf\n",i+1 , arr[i]);
	}
	free(arr);
}

double* showW(BD *bd)
{
    double* arre = totalWinnings(bd);    
    printf("-----\n");
	for (int i = 0; i< bd->N ; i++)
	{
		printf("Las ganacias totales por el producto %i son de $%.2lf\n",i+1 ,arre[i]);
	}
	free(arre);
}

void searchProductByName(BD *bd, char name[150]) {
    for(int i = 0; i < bd->N; i++) {
        if(strcmp(name, bd->productos[i].nombre) == 0) {
            showData(i+1, bd->productos[i]);
            break;
        }
    }
}

int daysPerMonth(char* month){
    char treintauno[7][15] = {"Enero", "Marzo", "Mayo", "Julio", "Agosto", "Octubre", "Diciembre"};
    for(int i=0;i<7;i++){
        if( strcmp(month,treintauno[i]) == 0 ){
            return 31;
        }
    }
        if( strcmp(month,"Febrero") == 0 ){
            return 28;
        }
        else {
            return 30;
        }
}

// Funciones de ordenamiento
int orderExpirationD(const void *a, const void *b) { //tercer parametro para elegir cuál 
    PRODUCTO *producto1 = (PRODUCTO*)a;
    PRODUCTO *producto2 = (PRODUCTO*)b;
    char months[12][15] = {"Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio", "Julio", "Agosto", "Septiembre", "Octubre", "Noviembre", "Diciembre"};
/// date 1 : 11 09 23    date 2: 19 02 23     1 : 23*365 = 8395 + 20 = 8415    2 : 23*365 = 8395 + 21 = 8416
// date 1 : 11 09 23    date 2: 19 02 23     Septiembre: 330 +2023 +09 = 2362 Febrero: 2023 + 2 +532 =2557
    int date1 = (producto1->caducidad.anio*10000) + chartoint(producto1->caducidad.mes, months) *100  + (producto1->caducidad.dia) ;
    int date2 = (producto2->caducidad.anio*10000 ) + chartoint(producto2->caducidad.mes, months) *100  + (producto2->caducidad.dia);
    
   


    if(date1 < date2) {
        return 1;
    } else if(date1 > date2) {
        return -1;
    } else {
        return 0;
    }
}

int orderExpirationA(const void *a, const void *b) { //tercer parametro para elegir cuál 
    PRODUCTO *producto1 = (PRODUCTO*)a;
    PRODUCTO *producto2 = (PRODUCTO*)b;
    char months[12][15] = {"Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio", "Julio", "Agosto", "Septiembre", "Octubre", "Noviembre", "Diciembre"};


    int date1 = (producto1->caducidad.anio*10000) + chartoint(producto1->caducidad.mes, months) *100  + (producto1->caducidad.dia) ;
    int date2 = (producto2->caducidad.anio*10000 ) + chartoint(producto2->caducidad.mes, months) *100  + (producto2->caducidad.dia);


    if(date1 > date2) {
        return 1;
    } else if(date1 < date2) {
        return -1;
    } else {
        return 0;
    }
}

int orderExistenceD(const void *a, const void *b) {
    PRODUCTO *producto1 = (PRODUCTO*)a;
    PRODUCTO *producto2 = (PRODUCTO*)b;

    if(producto1->existencia < producto2->existencia) {
        return 1;
    } else if(producto1->existencia > producto2->existencia) {
        return -1;
    } else {
        return 0;
    }
}

int orderExistenceA(const void *a, const void *b) {
    PRODUCTO *producto1 = (PRODUCTO*)a;
    PRODUCTO *producto2 = (PRODUCTO*)b;

    if(producto1->existencia > producto2->existencia) {
        return 1;
    } else if(producto1->existencia < producto2->existencia) {
        return -1;
    } else {
        return 0;
    }
}

// Ordenamiento 0 ordena en descendiente
void sortByExpiration(BD *bd, int orden) {
    if(orden == 0){
         qsort(bd->productos, bd->N, sizeof(PRODUCTO), *orderExpirationD);
    }else{
         qsort(bd->productos, bd->N, sizeof(PRODUCTO), *orderExpirationA);
    }
    showAllData(bd->N, bd->productos);
   
}

void sortByExistence(BD *bd, int ordend) {
    if(ordend == 0){
        qsort(bd->productos, bd->N, sizeof(PRODUCTO), *orderExistenceD);
    }else{
        qsort(bd->productos, bd->N, sizeof(PRODUCTO), *orderExistenceA);
    }

    showAllData(bd->N, bd->productos);
}

// Crear una instancia de los structs
PRODUCTO createAProduct(char n[150], char cat[150], int cod, int e, double pc, double pv, FECHA date) {
    PRODUCTO product = { "", "", cod, e, pc, pv, date.dia, "", date.anio };
    strcpy(product.nombre, n);
    strcpy(product.categoria, cat);
    strcpy(product.caducidad.mes, date.mes);
    return product;
}

FECHA createADate(int day, char month[50], int year) {
    FECHA date = { day, "", year };
    strcpy(date.mes, month);
    return date;
}

int main() {
    BD bd = BDConstructor();
    readBinFile(&bd);
    /*FECHA fecha = createADate(20, "Agosto", 2020); *Agregar if (restricción para fecha de creación mes x tiene dias correspondientes)
    PRODUCTO producto = createAProduct("Seven-up", "bebidas", 2139013, 10, 10.00, 12.00, fecha); *else 
    addProduct(&bd, producto);
    deleteProduct(&bd, 2139013);*/
    sortByExistence(&bd, 1);
    printf("--- \n");
    sortByExistence(&bd, 0);
    printf("--- Existence over\n");

    sortByExpiration(&bd, 1);
    printf("---\n");
    sortByExpiration(&bd, 0); // 0 es des
    return 0;
}