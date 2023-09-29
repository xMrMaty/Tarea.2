#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "hashmap.h"
//---------------------------------------------------------------------
//Funcion para leer las cadenas.
void leerCadena101(char cadena[101]){
  scanf("%101[^\n]s",cadena);
  getchar();
}
//--------------------------------------------------------------------
//Función para printear el menú.
void menu(){
  printf("\n           MENÚ TURISTICO \n");
  printf("1 Registrar punto de interés\n");
  printf("2 Mostrar datos de punto de interés\n");
  printf("3 Eliminar punto de interés\n");
  printf("4 Registrar turista\n");
  printf("5 Agregar lugar favorito a turista\n");
  printf("6 Mostrar turistas por país\n");
  printf("7 Mostrar todos los puntos de interés de un tipo\n");
  printf("8 Importar\n");
  printf("9 Exportar\n");
  printf("0 SALIR\n");
  printf("\nIngrese una opción:");
}
//--------------------------------------------------------------------
//Structs a utilizar en el ejercicio.
typedef struct{
  char nombre[101];
  char tipo[101];
  char direccion[101];
  char horario[101];
  char descripcion[101];
}PuntoInteres;

typedef struct{
  char pasaporte[101];
  char nombre[101];
  char pais[101];
  List *favoritos;
}Turista;
//--------------------------------------------------------------------
/*Función para registrar puntos de intereses, en este se pide que el usuario ingrese los datos del punto de interes, guardarandose en una lista y un mapa.
*/
void registrarPuntoInteres(List* lista_punto,HashMap* mapa_punto_nombre){
  getchar();
  char auxNombre[101];
  char auxTipo[101];
  char auxDireccion[101];
  char auxHorario[101];
  char auxDescripcion[101];

  printf("Ingrese nombre:\n");
  leerCadena101(auxNombre);
  if (searchMap(mapa_punto_nombre, auxNombre) != NULL) {
    printf("El punto de interés con nombre '%s' ya existe.\n", auxNombre);
    return;
  }
  printf("Ingrese tipo:\n");
  leerCadena101(auxTipo);
  printf("Ingrese dirección\n");
  leerCadena101(auxDireccion);
  printf("Ingrese horario:\n");
  leerCadena101(auxHorario);
  printf("Ingrese descripción:\n");
  leerCadena101(auxDescripcion);

  PuntoInteres *nuevoPunto = (PuntoInteres *)malloc(sizeof(PuntoInteres));
  strcpy(nuevoPunto->nombre, auxNombre);
  strcpy(nuevoPunto->tipo, auxTipo);
  strcpy(nuevoPunto->direccion, auxDireccion);
  strcpy(nuevoPunto->horario, auxHorario);
  strcpy(nuevoPunto->descripcion, auxDescripcion);
  
  insertMap(mapa_punto_nombre,nuevoPunto->nombre,nuevoPunto);
  pushFront(lista_punto, nuevoPunto);
}
//--------------------------------------------------------------------
/*Función para mostrar los puntos de interes, el usario ingresa el nombre y este lo buscara en el mapa por la clave "nombre" para luego printearlo por pantalla.
*/
void mostrarPuntoInteres(HashMap* mapa_punto_nombre){
  getchar();
  char nombreBuscado[101];
  
  printf("Ingrese nombre:\n");
  leerCadena101(nombreBuscado);
  
  Pair* puntoPair = searchMap(mapa_punto_nombre, nombreBuscado);
  if (puntoPair != NULL) {
    PuntoInteres* punto = (PuntoInteres*)puntoPair->value;
    printf("Nombre: %s\n", punto->nombre);
    printf("Tipo: %s\n", punto->tipo);
    printf("Dirección: %s\n", punto->direccion);
    printf("Horario: %s\n", punto->horario);
    printf("Descripción: %s\n", punto->descripcion);
  } else {
    printf("El punto de interés con nombre '%s' no existe.\n", nombreBuscado);
  }
}
//--------------------------------------------------------------------
/*Función para eliminar un punto de interes. Le pedimos al usuario que ingrese el nombre del lugar, la funcion usara el mapa, donde la clave es el nombre. Luego lo eliminara del mapa y la lista.
*/
void eliminarPuntoInteres(List* lista_punto, HashMap* mapa_punto_nombre){
  getchar();
  char nombreBuscado[101];
  
  printf("Ingrese nombre:\n");
  leerCadena101(nombreBuscado);
  
  Pair* puntoPair = searchMap(mapa_punto_nombre, nombreBuscado);
  if (puntoPair != NULL) {
    PuntoInteres* punto = (PuntoInteres*)puntoPair->value;
    
    eraseMap(mapa_punto_nombre, punto->nombre);
    popFront(lista_punto);
    
    printf("Punto de interés eliminado con éxito.\n");
  } else {
    printf("El punto de interés con nombre '%s' no existe.\n", nombreBuscado);
  }
}
//--------------------------------------------------------------------
/*La funcion registra al turista. Le pide al usuario que ingrese nombre, pasaporte y país. Se guardara en una lista turista y un mapa pasaporte, ademas se le creara una lista de lugares donde le gustaria ir al turista.
*/
void registrarTurista(List* lista_turista,HashMap* mapa_turista_pasaporte){
  getchar();
  char auxNombre[101];
  char auxPasaporte[101];
  char auxPais[101];

  printf("Ingrese nombre del turista:\n");
  leerCadena101(auxNombre);
  printf("Ingrese el numero de pasaporte del turista:\n");
  leerCadena101(auxPasaporte);
  if (searchMap(mapa_turista_pasaporte, auxPasaporte) != NULL) {
    printf("El turista con número de pasaporte '%s' ya existe.\n", auxPasaporte);
    return;
  }
  printf("Ingrese pais del turista\n");
  leerCadena101(auxPais);

  Turista *nuevoTurista = (Turista *)malloc(sizeof(Turista));
  strcpy(nuevoTurista->nombre, auxNombre);
  strcpy(nuevoTurista->pasaporte, auxPasaporte);
  strcpy(nuevoTurista->pais, auxPais);
  
  insertMap(mapa_turista_pasaporte,nuevoTurista->pasaporte,nuevoTurista);
  pushFront(lista_turista, nuevoTurista);
  nuevoTurista->favoritos = createList();
}
//--------------------------------------------------------------------
/*Funcion para guardar lugares favoritos del turista. Le pide al usuario que ingrese su pasaporte y el nombre del lugar favorito. Este ingresara a traves del mapa, usando como clave el pasaporte. Luego ingresara el lugar favorito a la lista del turista de sus lugares favoritos.
*/
void lugarFavTurista(HashMap* mapa_turista_pasaporte, List* lista_turista){
  getchar();
  char pasaporteBuscado[101];
  char nombreLugarFavorito[101];

  printf("Ingrese el número de pasaporte del turista:\n");
  leerCadena101(pasaporteBuscado);
  printf("Ingrese el nombre del lugar favorito:\n");
  leerCadena101(nombreLugarFavorito);
  
  Pair* turistaPair = searchMap(mapa_turista_pasaporte, pasaporteBuscado);
  if (turistaPair != NULL){
    Turista* turista = (Turista*)turistaPair->value;
    char* lugarFavorito = strdup(nombreLugarFavorito);
    pushFront(turista->favoritos, lugarFavorito);
    printf("Lugar favorito '%s' agregado con éxito al turista con pasaporte '%s'.\n", lugarFavorito, pasaporteBuscado);
  } else {
    printf("El turista con número de pasaporte '%s' no existe.\n", pasaporteBuscado);
  }
}
//--------------------------------------------------------------------
/*Funcion mostrarTuristaXpais, mostrara los turistas pero con el pais ingresado por el usuario. Este recorrera la lista y los filtrara por pais, para luego mostrarlos por pantalla.
*/
void mostrarTuristaXpais(List* lista_turista){
  getchar();
  char paisBuscado[101];

  printf("Ingrese el país:\n");
  leerCadena101(paisBuscado);
  
  Turista* turistaData = firstList(lista_turista);
  int encontrado = 0;

  while (turistaData != NULL) {
    Turista* turista = (Turista*)turistaData;
    
    if (strcmp(turista->pais, paisBuscado) == 0) {
      encontrado = 1;
      printf("\nNombre: %s\n", turista->nombre);
      printf("Número de pasaporte: %s\n", turista->pasaporte);

      List* favoritos = turista->favoritos;
      Turista* favoritoData = firstList(favoritos);

      printf("Lugares favoritos:\n");
      while (favoritoData != NULL) {
        char* lugarFavorito = (char*)favoritoData;
        printf("- %s", lugarFavorito);
        favoritoData = nextList(favoritos);
      }
      printf("\n");
    }
    turistaData = nextList(lista_turista);
  }
  if (encontrado == 0) {
    printf("No se encontraron turistas de %s.\n", paisBuscado);
  }
}
//--------------------------------------------------------------------
/*Funcion mostrarPuntoInteresUnTipo, mostrara los puntos de interes pero con el tipo que el usuario ingresa. Este recorrara la lista y lo filtrara por el tipo, para luego mostrarlos por pantalla.
*/
void mostrarPuntoInteresUnTipo(List* lista_punto){
  getchar();
  char tipoBuscado[101];

  printf("Ingrese el tipo:\n");
  leerCadena101(tipoBuscado);

  PuntoInteres* puntoData = firstList(lista_punto);
  int encontrado = 0;

  while (puntoData != NULL){
    PuntoInteres* punto = (PuntoInteres*)puntoData;
    if (strcmp(punto->tipo, tipoBuscado) == 0){
      encontrado = 1;
      printf("Nombre: %s\n", punto->nombre);
      printf("Tipo: %s\n", punto->tipo);
      printf("Dirección: %s\n", punto->direccion);
      printf("Horario: %s\n", punto->horario);
      printf("Descripción: %s\n\n", punto->descripcion);
    }
    puntoData = nextList(lista_punto);
  }
  if (encontrado == 0) {
    printf("No se encontraron puntos de interés de tipo '%s'.\n", tipoBuscado);
  }
}
//--------------------------------------------------------------------
/*Funcion de importar los datos csv de los punto de interes y los turistas. Le pide al usuario que ingrese los nombres de los archivos, luego se registraran y se guardaran en la lista y mapa. Se usa el mismo procedimiento para los dos archivos, la unica diferencia es que a los turistas se crea una lista para los lugares favoritos
*/
void importar(List* lista_punto, HashMap* mapa_punto_nombre, List* lista_turista, HashMap* mapa_turista_pasaporte){
  char nombre_archivo_puntos[101];
  char nombre_archivo_turistas[101];
  
  printf("Ingrese el nombre del archivo de puntos de interés (CSV):\n");
  scanf("%s",nombre_archivo_puntos);
  
  printf("Ingrese el nombre del archivo de turistas (CSV):\n");
  scanf("%s",nombre_archivo_turistas);
  //Puntos de interes
  FILE* archivo_puntos = fopen(nombre_archivo_puntos, "r");
  
  char linea[1024];
  while (fgets(linea, sizeof(linea), archivo_puntos)){
    char* nombre = strtok(linea, ",");
    char* tipo = strtok(NULL, ",");
    char* direccion = strtok(NULL, ",");
    char* horario = strtok(NULL, ",");
    char* descripcion = strtok(NULL, ",");
    
    PuntoInteres* nuevoPunto = (PuntoInteres*)malloc(sizeof(PuntoInteres));
    
    strcpy(nuevoPunto->nombre, nombre);
    strcpy(nuevoPunto->tipo, tipo);
    strcpy(nuevoPunto->direccion, direccion);
    strcpy(nuevoPunto->horario, horario);
    strcpy(nuevoPunto->descripcion, descripcion);
    
    insertMap(mapa_punto_nombre, nuevoPunto->nombre, nuevoPunto);
    pushFront(lista_punto, nuevoPunto);
  }
  fclose(archivo_puntos);
  printf("Datos de puntos de interés importados con éxito desde %s.\n", nombre_archivo_puntos);
  
  //Turistas
  FILE* archivo_turista = fopen(nombre_archivo_turistas, "r");
  char linea2[1024];
  
  while (fgets(linea2, sizeof(linea2), archivo_turista)){
    if (strspn(linea2, " \t\n\r\f\v") == strlen(linea2))
      continue; // Ignorar líneas en blanco
    
    char* pasaporte = strtok(linea2, ",");
    char* nombre = strtok(NULL, ",");
    char* pais = strtok(NULL, ",");
    char* lugaresFavoritos = strtok(NULL, ",");
    
    Turista* nuevoTurista = (Turista*)malloc(sizeof(Turista));
    
    strcpy(nuevoTurista->pasaporte, pasaporte);
    strcpy(nuevoTurista->nombre, nombre);
    strcpy(nuevoTurista->pais, pais);
    
    insertMap(mapa_turista_pasaporte, nuevoTurista->pasaporte, nuevoTurista);
    pushFront(lista_turista, nuevoTurista);
    
    nuevoTurista->favoritos = createList();
    char* lugarFavorito = strtok(lugaresFavoritos, ";");
    while (lugarFavorito != NULL){
      pushFront(nuevoTurista->favoritos, strdup(lugarFavorito));
      lugarFavorito = strtok(NULL, ";");
    }
  }
  fclose(archivo_turista);
  printf("Datos de turistas importados con éxito desde %s.\n", nombre_archivo_turistas);
}

//--------------------------------------------------------------------
/*La funcion exporta los archivos de punto de interes y turistas. Le pide al usuario que ingrese los nombres de los archivos donde los quiere exportar. Se sigue el mismo procedimiento para los dos archivos, con diferencia que para los turistas se le agrega lo de su lista de lugares favoritos.
*/
void exportar(List* lista_punto, HashMap* mapa_punto_nombre, List* lista_turista, HashMap* mapa_turista_pasaporte){
  char nombre_archivo_puntos[101];
  char nombre_archivo_turistas[101];
  
  printf("Ingrese el nombre del archivo de puntos de interés (CSV):\n");
  scanf("%s",nombre_archivo_puntos);
  
  printf("Ingrese el nombre del archivo de turistas (CSV):\n");
  scanf("%s",nombre_archivo_turistas);
  
  FILE* archivo_puntos = fopen(nombre_archivo_puntos, "w");
  
  PuntoInteres* puntoData = firstList(lista_punto);
  while (puntoData != NULL) {
    PuntoInteres* punto = (PuntoInteres*)puntoData;
    fprintf(archivo_puntos, "%s,%s,%s,%s,%s\n", punto->nombre, punto->tipo, punto->direccion, punto->horario, punto->descripcion);
    puntoData = nextList(lista_punto);
  }

  fclose(archivo_puntos);
  printf("Datos de puntos de interés exportados con éxito a %s.\n", nombre_archivo_puntos);
  
  FILE* archivo_turistas = fopen(nombre_archivo_turistas, "w");
  
  Turista* turistaData = firstList(lista_turista);
  while (turistaData != NULL) {
    Turista* turista = (Turista*)turistaData;
    fprintf(archivo_turistas, "%s,%s,%s,", turista->pasaporte, turista->nombre, turista->pais);
    
    List* favoritos = turista->favoritos;
    Turista* favoritoData = firstList(favoritos);
    while (favoritoData != NULL) {
      char* lugarFavorito = (char*)favoritoData;
      fprintf(archivo_turistas, "%s;", lugarFavorito);
      favoritoData = nextList(favoritos);
    }
    fprintf(archivo_turistas, "\n");
    turistaData = nextList(lista_turista);
  }

  fclose(archivo_turistas);
  printf("Datos de turistas exportados con éxito a %s.\n", nombre_archivo_turistas);
}


//--------------------------------------------------------------------
// MAIN
int main(){
  //Mapas a usar
  HashMap* mapa_punto_nombre = createMap(100);
  HashMap* mapa_turista_pasaporte = createMap(100);
  
  //Listas a usar
  List* lista_punto = createList();
  List* lista_turista = createList();
  
  int opcion;
  while (true) {
    menu();
    scanf("%d", &opcion);
    switch (opcion) {
      case 1:
        registrarPuntoInteres(lista_punto,mapa_punto_nombre);
        break;
      case 2:
        mostrarPuntoInteres(mapa_punto_nombre);
        break;
      case 3:
        eliminarPuntoInteres(lista_punto,mapa_punto_nombre);
        break;
      case 4:
        registrarTurista(lista_turista, mapa_turista_pasaporte);
        break;
      case 5:
        lugarFavTurista(mapa_turista_pasaporte,lista_turista);
        break;
      case 6:
        mostrarTuristaXpais(lista_turista);
        break;
      case 7:
        mostrarPuntoInteresUnTipo(lista_punto);
        break;
      case 8:
        importar(lista_punto, mapa_punto_nombre, lista_turista, mapa_turista_pasaporte);
        break;
      case 9:
        exportar(lista_punto, mapa_punto_nombre, lista_turista, mapa_turista_pasaporte);
        break;
      case 0:
          printf("SALISTE DEL MENÚ\n");
          return 0;
                
      default:
          printf("Ingrese una opción válida\n");
          break;
      }
  }
  return 0;
}