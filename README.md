# Trabajo 1 - Sistema Operativo y Programación

## Descripción
Este programa implementa una aplicación que permite gestionar permisos de usuarios y realizar diferentes operaciones numéricas en base a permisos otorgados.

## Compilación
Para compilar el programa, utiliza el siguiente comando en la terminal dentro del directorio /main
```bash
make
```
# Ejecución
Una vez compilado, puedes ejecutar el programa proporcionando el nombre de usuario, el vector correspondiente, una ruta de lectura, un texto a escribir, una ruta de input y una ruta de output. Aquí se muestra un ejemplo:

```bash
./ej -u [edgardo] -v [1,2,3] -f ["ruta;prueba.txt"] -t ["texto de prueba"] -i ["ruta_input"] -o ["ruta_output"]
```
Esto ejecuta el programa asignando como nombre de usuario "edgardo" y el vector {1, 2, 3}, además recibe como ruta "ruta" y nombre de archivo "prueba.txt" (separados por ";") Si no se cumple el formato el programa no se ejecutará.
También se le asigna el parámetro -t, que contiene un texto para agregarlo al archivo. En este caso es "texto de prueba"
Los parametrors **-i** y **-o** indican rutas de lectura y escritura de archivo respectivamente. El programa leera el archivo de entrada, realizará operaciones y escribirá los resultados en el archivo de salida (indicado en la ejecución).

# Variables de entorno "rutas.env"
El proyecto tiene un archivo **.env** en el que se encuentran definidas las rutas de las bases de datos que se utilizarán en el programa principal. Este es de  la siguiente forma:

```bash
usuarios=/home/edgardo/Programacion/INFO-189_2/bdd/usuarios.txt
permisos=/home/edgardo/Programacion/INFO-189_2/bdd/permisos.txt
menu=/home/edgardo/Programacion/INFO-189_2/bdd/menu.txt
EXTENTION=txt
PATH_FILES_IN=~/Programacion/INFO-189_2/files/in
PATH_FILES_OUT=~/Programacion/INFO-189_2/files/out
AMOUNT_THREADS=15
INVERTED_INDEX_FILE=~/Programacion/INFO-189_2/main/funciones_externas/index.idx
```

# Base de Datos
La información de usuarios y permisos se almacena en dos archivos de texto: usuarios.txt y permisos.txt. Estos archivos, estan organizados en la carpeta **"bdd"** y siguen el siguiente formato:

#### usuarios.txt
El archivo usuarios.txt contiene los nombres de usuario y su tipo (separados por coma ",") y entre usuarios separados por punto y coma (;).
Ejemplo:
```bash
nico,admin;iban,userRookie;edgardo,userGeneral;
```

#### permisos.txt
El archivo permisos.txt almacena los permisos asignados a cada tipo usuario. Cada línea contiene el tipo de usuario seguido de los números de permisos separados por comas (,).

Ejemplo:
```bash
admin;0,1,2,3,4,5,6,7,8
userGeneral;0,1,2,3,4
userRookie;0,1,2
```

### menu.txt
El archivo "menu.txt" contiene las opciones de menú para que el usuario pueda interactuar, este tiene el siguiente formato:
```bash
0,Salir,salir
1,Realizar sumatoria del vector,sumatoria
2,Realizar promedio del vector,promedio
3,Realizar moda del vector,moda
4,Contar elementos del vector,contar
5,Crear archivo,crear
6,Agregar texto a archivo,agregar
7,Contar palabras de texto,count_words
8,PREPARAR DATOS PARA INDICE INVERTIDO,preparar_datos
9,CREAR INDICE INVERTIDO,crear_indice
10,Nueva opción 1,indefinido
```
El programa crea una lista enlazada con una estructura donde guarda el numero de opción, su descripción y su respectiva función asociada.

## Ejecución

### Si el usuario se encuentra en la base de datos

El programa le dará las opciones a ejecutar en el vector correspondientes a sus permisos. Si el usuario no tiene permiso para ejecutar una opción, se le negará.

Las opciones son las siguientes:

1. Salir: Termina el programa.
2. Realizar sumatoria del vector: Suma los valores del vector.
3. Realizar promedio del vector: Promedia los valores del vector.
4. Realizar moda del vector: Calcula la moda del vector.
5. Contar elementos del vector: Cuenta los números del vector.
6. Crear archivo: Crea un archivo con la ruta y nombre especificado.
7. Agregar texto a archivo: Escribe en el archivo.
8. Contar palabras del archivo de entrada.
9. PREPARAR DATOS PARA INDICE INVERTIDO: Lee archivos de una ruta específica y crea archivos de salida con su conteo de palabras.
10. CREAR INDICE INVERTIDO: Lee los conteos de palabras y genera un archivo con la cantidad de ocurrencias por palabra en cada archivo.
9. Nueva opción 1: Funciones no implementadas.


#### Opciones 8) y 9)
*Tanto las opciones 8) y 9), son procesos externos, estos se llaman al seleccionar la opción con sus respectivos parámetros:
**PREPARAR DATOS PARA INDICE INVERTIDO:** ```./app [EXTENTION] [PATH_FILES_IN] [PATH_FILES_OUT] [AMOUNT_THREADS]```
**CREAR INDICE INVERTIDO:** ```./app [INVERTED_INDEX_FILE] [PATH_FILES_OUT]```*
**(Todos estos parámetros se extraen desde el archivo .env*)*

### Si el usuario no se encuentra en la base de datos

Se terminará la ejecución del programa.

