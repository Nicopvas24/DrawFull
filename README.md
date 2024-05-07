# DrawFull

Este repositorio alberga un programa para editar imagenes desarrollado con Qt Creator, diseñado para simplificar la edición de imagenes con formato. Ofrece herramientas como abrir imagenes, pintar y otras más. Además, ofrece opciones para gestionar archivos, permitiendo guardar el texto editado en formatos PNG, JPG o BMP. También proporciona al usuario la capacidad de imprimir el texto desde la aplicación.

# Descripcion de su Arquitectura

Este proyecto se ha desarrollado utilizando Qt Creator y se vale de CMake como su sistema de construcción. Su arquitectura adopta una estructura modular que simplifica tanto el mantenimiento como la capacidad de ampliación. A continuación, se detallan los componentes principales y cómo interactúan entre sí:

# CMake y Estructura Base del Proyecto

El proyecto se construye con CMake, aprovechando su capacidad para gestionar la compilación de manera eficiente y flexible. La estructura base del proyecto sigue un enfoque modular, organizando los componentes de manera lógica y facilitando su mantenimiento y escalabilidad.

# Logica de la Aplicacion

Se reúnen y se definen las clases y funciones que dan vida a la lógica principal de la aplicación en el archivo mainwindow.h, las cuales son posteriormente utilizadas en el flujo de ejecución.

# Flujo de Ejecucion

La ejecución se inicia en la clase principal main.cpp, encargada de inicializar la aplicación y cargar la interfaz de usuario. La interacción del usuario desencadena eventos que son gestionados por las clases dentro del módulo de lógica de la aplicación en mainwindow.cpp, lo que conlleva a actualizaciones en la interfaz y operaciones en el texto. En este se controlan las operaciones de edición de imagen, el formato y otras funciones principales.

# Interfaz de Usuario

Dentro de este módulo se encuentran las clases y archivos vinculados con la interfaz gráfica de usuario. Se encarga de gestionar las ventanas, widgets y elementos visuales que conforman la interfaz.

# Explicacion de Funciones de Edicion

# MainWindow()

Esta funcion es el constructor con el cual se prepara la ventana principal en este caso un lienzo de dibujo con unos parametros predeterminados y algunos objetos con los que se pueden interactuar para estar listo a recibir ordenes del usuario

# PainEvent()

Dentro de si misma se crea un objeto con el cual el usuario pueda pintar el lienzo, esta se encarga de dibujar en la ventana principal cada vez que el usuario lo desee

# MouseMoveEvent()

Analiza los movimientos que el usuario realiza con el mouse, permitiendole dibujar mientras se este presionando el click y este seleccionado el pincel

# MousePressEvent()

Se encarga de detectar si el usuario esta presionando el click izquierdo del mouse para despues almacenar su posicion inical y comenzar a dibujar

# MouseReleaseEvent()

Esta funcion detecta si el usuario suelta el clink izquierdo del mouse, almacenando la ubicacion en la cual termino el usuario de dibujar para realizar las acciones programadas como (linea,cuadrado,circulo,triangulo entre otras)

# on_tamano_clicked()

Permite al usuario cambiar el tamaño del pincel mediante un cuadro de dialogo y actualiza el tamaño del pincel segun el valor ingresado

# on_color_clicked()

Le concede al usuario la opcion de elegir el color del pencil por medio de un cuadro de dialogo de seleccion de color formato "ARGB" y actualiza el color del pincel inmediatamente. Si el usuario tiene el borrador activo, no podra hacer ninguna accion que permite esta funcion

# on_borrador_clicked()

Accede la activacion del modo borrador, guardando temporalmente el color que anteriormente el usuario selecciono para mas tarde retormalo y cambia el color del pincel a blanco para permitir al usuario utilizar el pincel como borrador

# on_pincel_clicked()

Desactiva el modo borrador, retomando la accion de dibujar y restaura el color del pincel que tenia el usuario antes de usar el borrador

# on_linea_clicked()

Activa el modo dibujo de lineas y retoma el color previamente seleccionado si el usuario estaba en modo borrador

# on_rectangulo_clicked()

Deshabilita el modo borrador, configurando el modo para dibujar rectangulos vacios y restaura el color seleccionado si el usuario tenia activado el borrador

# on_elipse_clicked()

Desactiva el modo de borrador, configura la acción actual para dibujar elipses y restaura el color del pincel al color que estaba en uso antes de activar el modo de borrador.

# on_triangulo_clicked()

Anula la accion de borrar, mientras actualiza la accion para dibujar triangulos y recupera el color del pincel que tenia el usuario antes de activar el borrador

# Explicacion de Funcion para el Manejo de Archivos

# closeEvent()

Se encarga de decidir si la aplicacion debe cerrarse o no dependiendo de lo deseado por el usuario y analizado por la condicion "mTalvez();"

# on_cerrar_clicked()

Esta funcion se encarga de cerrar la ventana principal cuando el usuario da click a la opcion de cerrar

# mTalvez()

Verifica si el usuario ha realizado cambios en el lienzo desde la ultima vez que guardo su progreso y solicita al usuario que dicida si quiere guardas los cambios hechos antes de cerrar la aplicacion

# on_guardar_clicked()

Llama a la funcion "mGuardar()" para guardar la imagen actual y se activa cuando el usuario hace click en el elemento de la interfaz grafica que esta asociado con esta accion

# mGuardar()

Maneja el proceso de guardado de la imagen actual en los archivos del dispositivo del usuario

# on_abrir_clicked()

Esta funcion permite al usuario abrir imagenes que tenga en su dispositivo para luego esta hacerse cargop de copiar en el lienzo la imagen seleccinada

# on_nuevo_clicked()

Restablece los valores del lienzo dejandolo como nuevo para volver a comenzar a dibujar

# Manual Tecnico

Una vez que la compilación haya concluido y la aplicación esté abierta, se mostrará un menú en la izquierda de la pantalla. Este menú permite acceder a diversas opciones para el manejo de archivos, como "Guardar", que posibilita al usuario guardar la imagen editada en formatos como PNG,JPG O BMP. También se encuentran opciones para abrir, guardar cambios, eliminar y cerrar, todas estas relacionadas con la gestión de los archivos del usuario. En medio del programa se encuentra un área en blanco donde el usuario puede dubijar lo deseado.

# Hecho por

UNIVERSIDAD TECNOLOGICA DE PEREIRA Ingeniería en Sistemas y Computación Facultad de Ingenierias Programación II 

Ing(c):Juan Jose Grajales 

Ing(c):Nicolás Valencia 

Ing(c): Renzo Usma Barrios 

Ing(c):Juan Jose Gomez 

Ing(c):Juan Manuel Agudelo

# Contactanos

juan.gomez14@utp.edu.co

j.agudelo10@utp.edu.co

j.grajales4@utp.edu.co

n.valencia4@utp.edu.co

renzo.usma@utp.edu.co
