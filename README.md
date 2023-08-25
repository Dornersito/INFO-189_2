# Trabajo 1 - Sistema Operativo y Programación

## Descripción
Este programa implementa una aplicación que permite gestionar permisos de usuarios y realizar diferentes operaciones numéricas en base a permisos otorgados.

## Compilación
Para compilar el programa, utiliza el siguiente comando en la terminal:

```bash
make
```
# Ejecución
Una vez compilado, puedes ejecutar el programa proporcionando el nombre de usuario y el vector correspondiente. Aquí tienes un ejemplo:

```bash
./ej -u [edgardo] -v [1,2,3] -f ["ruta;prueba.txt"] -t ["texto de prueba"]
```
Esto ejecuta el programa asignando como nombre de usuario "edgardo" y el vector {1, 2, 3}, además recibe como ruta "ruta" y nombre de archivo "prueba.txt" (separados por ";") Si no se cumple el formato el programa no se ejecutará.
También se le asigna el parámetro -t, que contiene un texto para agregarlo al archivo. En este caso es "texto de prueba"

# Base de Datos
La información de usuarios y permisos se almacena en dos archivos de texto: usuarios.txt y permisos.txt. Estos archivos siguen el siguiente formato:

#### usuarios.txt
El archivo usuarios.txt contiene los nombres de usuario separados por punto y coma (;).
Ejemplo:
```bash
vicho;mati;edgardo
```

#### permisos.txt
El archivo permisos.txt almacena los permisos asignados a cada usuario. Cada línea contiene el nombre de usuario seguido de los números de permisos separados por comas (,).

Ejemplo:
```bash
vicho;1,2,3
edgardo;1,2,4
mati;3,4
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
7,Nueva opción 1,indefinido
```
El programa crea una lista enlazada con una estructura donde guarda el numero de opción, su descripción y su respectiva función asociada.

## Ejecución
- **Si el usuario se encuentra en la base de datos.**
El programa le dará las opciones a ejecutar en el vector correspondientes a sus permisos.
Si el usuario no tiene permiso a ejecutar una opción, se le negará.

    Las opciones son las siguientes:
    -- 0) Salir: Termina el programa.
    -- 1) Realizar sumatoria del vector: Suma los valores del vector.
    -- 2) Realizar promedio del vector: Promedia los valores del vector.
    -- 3) Realizar moda del vector: Calcula la moda del vector.
    -- 4) Contar elementos del vector: Cuenta los numeros del vector.
    -- 5) Crear archivo: Crea un archivo con la ruta y nombre especificado.
    -- 6) Agregar texto a archivo: Escribe en el archivo.
    -- 7) Nueva opción 1: Funciones no implementadas.

- **Si el usuario no se encuentra en la base de datos**
Se terminará con la ejecución del programa
