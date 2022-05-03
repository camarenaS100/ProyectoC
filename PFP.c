#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int dia;
    char mes [50];
    int anio;
 }FECHA;

typedef struct{
    char nombre [150];
    char categoria [150];
    int codigo;
    int existencia;
    double precio_compra;
    double precio_venta;
    FECHA caducidad;
 }PRODUCTO;

typedef struct{  
    PRODUCTO *productos;
    int N;
 }BD;

void CargarDatos () //Crea memoria espacio en memoria, nosotros creamos y destruimos
{
	FILE *file;
	int i;
	char basura[10];

	file = fopen("Inventario.txt", "r"); //calloc 1
	fscanf(file, "%d", &BD.N); 
	BD.productos = malloc(sizeof(PRODUCTO)*BD.N); // asignamos memoria dinámica por cada malloc, calloc 2
	for(i=0; i < BD.N, i++) // 
	{
		fscanf(file, "%s", basura);
		fscanf(file, "%s", BD.productos[i].nombre);
		fscanf(file, "%s", BD.productos[i].categoria);
		fscanf(file, "%d", BD.productos[i].codigo);
        fscanf(file, "%d", BD.productos[i].existencia);
        fscanf(file, "%lf", BD.productos[i].precio_compra);
        fscanf(file, "%lf", BD.productos[i].precio_venta);
        fscanf(file, "%d %s %d", BD.productos[i].FECHA.dia, BD.productos[i].FECHA.mes, BD.productos[i].FECHA.anio);
	}
	fclose(file);
}

void GuardarEnBinario() // escribir datos 
{
	FILE *file;
	file = fopen("Inventario.bin", "w+b") //archivo binario nuevo, (nombre, modo de apertura : write y binary)  Creación .bin

	fwrite(&BD.N,sizeof(int), 1, file); 
	fwrite(BD.productos, sizeof(PRODUCTO), BD.N, file); //Éste
	fclose(file);
}

void CargarDatosBinario()  // leer archivo binario
{
	FILE *file;
	file = fopen("Inventario.bin", "r+b"); 

	fread(&BD.N, sizeof(int), 1, file);  //es el mismo a fwrite en 57   Desplazamiento es automático, si quieres especificar fseek
	BD.productos = malloc(sizeof(PRODUCTO)*BD.N);
	fread(BD.productos, sizeof(PRODUCTO), BD.N, file);
	fclose(file);
}

int main()
{
    CargarDatos();
    GuardarEnBinario();
    for (int i=0; i < BD.N; i++)
    {
        printf("%s",BD.productos[i].nombre);
    } 
    
    return 0;
}