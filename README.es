                                ---------------
                                 Enable Viacam
                                ---------------
                                  
             emulador de rat�n multi-plataforma a trav�s de c�mara web

 Acerca de
===========

Enable Viacam (alias eViacam) es un programa de ordenador que sustituye la funcionalidad del rat�n permitiendo mover el puntero a partir del movimiento de la cabeza. Funciona en un ordenador PC equipado con una c�mara web, sin elementos adicionales. eViacam est� basado en el programa Rat�n Facial galardonado con varios premios.

 Plataformas soportadas
========================

GNU/Linux
Windows 2000/XP/Vista/7

 Instrucciones
==============

(NOTA: a partir de la versi�n 1.4, el manual de instrucciones se incluye en el software)

Primero hay que haber instalado y configurar correctamente la c�mara web. Es muy importante configurar al c�mara en modo de exposici�n manual y ajustar este par�metro para obtener 25 fps o m�s de velocidad de captura. La mayor�a de c�maras modernas proporcionan hasta 30 fps. Consulte el manual de la c�mara en caso necesario.

Una vez instalado, ejecute evicam (evicam.exe para Windows). El programa debe abrirse, detectar autom�ticamente la c�mara y mostrar la imagen en tiempo real.

Sit�e la c�mara por obtener una imagen frontal de su rostro. La anchura de este, en la imagen, debe ser aproximadamente un tercio de la anchura del cuadro. Hay que centrar el rect�ngulo (azul) de seguimiento alrededor de su rostro moviendo la c�mara o desplazando el cuadro con el rat�n (click en la esquina).

Active la opci�n para iniciar la funci�n de control desde el men� Archivo. Pruebe a mover la cabeza y observe el resultado. Puede ajustar la sensibilidad (velocidad ejes X e Y) a trav�s del di�logo de configuraci�n. Debe poder hacer llegar el puntero a cualquier lugar de la pantalla.

Para hacer clic s�lo hace falta parar el puntero sobre la localizaci�n desea. En unos instantes se genera un clic de forma autom�tica (este tiempo de espera se puede ajustar desde el di�logo de configuraci�n). Utilice la ventana empotrada de la parte superior para escoger entre los diferentes tipos de clic.

 Instalaci�n
==============

Ver archivo INSTALL

 Notas
=======

- Idioma Asturiano (Bable)

La versi�n estable actual de wxWidgets (2.8.x en noviembre de 2010) no es compatible con lengua asturiana a�n, pero parece que se ha a�adido soporte para la versi�n de desarrollo. Por lo tanto, si desea activar el soporte de lengua asturiana, necesita la �ltima versi�n de desarrollo de wxWidgets y hay descomentar la siguiente l�nea antes de compilar

	// # Define ENABLE_ASTURIAN
en:
	src/langnames-utf8.h
	src/langnames-utf16.h

Tenga en cuenta que estos archivos utilizan una codificaci�n especial.

 Licencia
===========

Enable Viacam se proporciona bajo licencia GNU/GPL v3.
Vea el archivo COPYING para detalles sobre la licencia.

 Autor
========
 
(C) 2008-10 Cesar Mauri Loba (cesar a crea-si punto com)
Vea los archivos AUTHORS y THANKS para m�s informaci�n sobre otras contribuciones.

 Agradecimientos
=================

- Este software ha sido desarrollado gracias al apoyo de diferentes
  colaboradores y el patrocinio de:
	- Consorcio Fernando de los R�os
    - Seceretar�a de Telecomunicaciones y Sociedad de la Informaci�n del
	Departamento de Gobernaci�n y Administraciones P�blicas de la Generalitat
	de Catalu�a
	- Asociaci�n Provincial de Par�lisis Cerebral (APPC) de Tarragona.

- Gracias a toda la gente de la APPC por su colaboraci�n en las pruebas y especialmente a los usuarios que han colaborado activamente, entre ellos el Ruben, Gloria, Cristina y muchos y muchos otros. Gracias a todos.

 Enlaces
=========

http://viacam.org
	- Enable Viacam website
http://www.wxwidgets.org
        - wxWidgets toolkit homepage
http://sourceforge.net/projects/opencvlibrary/
	- Open Computer Vision Library homepage
http://www.innosetup.org

http://www.crea-si.com
	- CREA Software Systems site