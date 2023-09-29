MENÚ TURISTICO

Descripcion:
Este codigo es un programa de gestion de puntos turisticos y de turistas que se encarga de registrar turistas y puntos de interes turistico, ademas de marcar los lugares favoritos de cada turista, tambien muestra a los turistas segregados por pais y los puntos de interes turisticos dependiendo del tipo al que estos pertenezcan. 

Compilar y ejecutar:
https://github.com/xMrMaty/Tarea-2
cd gestor-de-tareas
gcc main.c funciones_tareas.c -o gestor
./gestor

FUNCIONALIDADES
Funcionando correctamente:
  -menu: Una funcion exclusiva para mostrar el menu al usuario, para que asi este pueda seleccionar la opcion que quiera trabajar.
  
  -registrarPuntoInteres: El usuario puede registrar los puntos de interes turistico que el desee proporcionando el nombre, tipo, ubicacion, horario y una breve descripcion de este. La funcion guardara los datos en una lista y en un mapa donde la clave es el nombre y el valor el punto de interes.
  
  -mostrarPuntoInteres: El usuario puede seleccionar esta opcion para mostrar los puntos de interes turistico, para esto debe proporcionar el nombre del punto de interes que desea mostrar.
  
  -eliminarPuntoInteres: Esta opcion permite al usuario eliminar el punto de interes turistico, para hacer esto el usuario debe proporcionar el nombre del punto de interes. La funcion lo eliminira de la lista y el mapa.
  
  -registrarTurista: Esta opcion permite al usuario registrar un turista nuevo ingresando el nombre, el numero de pasaporte y el pais del que es el turista ingresado. La funcion guardara los datos en una lista y un mapa, ademas creara una lista con los lugares favoritos del usuario.
  
  -lugarFavTurista: Esta opcion permite guardar los lugares favoritos de cada turista proporcionando el numero de pasaporte del turista y el nombre del punto de interes que quiere guardar como favorito. La funcion guardara los lugares favoritos en una lista.
  
  -mostrarTuristaXpais: Esta opcion permite al usuario mostrar todos los turistas registrados por pais, esto se logra ingresando el pais de los turista que quiere mostrar.
  
  -mostrarPuntoInteresUnTipo: Esta opcion permite al usuario mostrar los puntos de interes turisticos separados por los tipos que estos sean, el usuario ingresa el tipo de punto de interes que quiere mostrar.
  
  -importar: Esta opcion permite al usuario importar los puntos de interes turisticos y los turistas desde un archivo csv para utilizarlos con cualquiera de las demas opciones del programa. La funcion guardara los datos y le asignara su correspondiente lista y mapa.
  
  -exportar: Esta opcion permite al usuario exportar los puntos de interes turisticos y los turistas a un archivo csv para mantener una base de datos persistente.
  
Problemas conocidos:

  -Falta verificación en el caso de agregar un nuevo lugar favorito a la lista del turista.
  
CONTRIBUCIONES:

    Javier Morales:
      -Hecho la funcion "menu"
      -Hecho la funcion "registrarTurista"
      -Hecho la funcion "lugarFavTurista"
      -Hecho la funcion "mostrarTuristaXpais"
      -Hecho la funcion "mostrarPuntoInteresUnTipo"
      -Hecho la funcion "exportar"
      -Resulocion de logica del programa en las funciones que realizo
      Puntaje en el trabajo: 3(Aporte excelente)
    Matias Ruiz:
      -Hecho la funcion "registrarPuntoInteres"
      -Hecho la funcion "mostrarPuntoInteres"
      -Hecho la funcion "eliminarPuntoInteres"
      -Hecho la funcion "importar"
      -Resulocion de logica del programa en las funciones que realizo
      Puntaje en el trabajo: 3(Aporte excelente)