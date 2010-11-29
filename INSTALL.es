==========================================
Instrucciones de instalaci�n Enable Viacam
==========================================

Este documento describe c�mo compilar e instalar Enable Viacam 
para GNU/Linux y Windows.

Linux
=====

- Pre-requisitos
  --------------
  wxWidgets >= 2.6
  OpenCV >= 1.0
  gtk-2.0
  libxtst
  libxext

  Notas Ubuntu: con el fin de compilar en Ubuntu (karmic) y en GGv6 se
  necesitan los siguientes paquetes: libxext-dev, libxtst-dev, libgtk2.0-dev, 
  libwxbase2.8-dev, libwxgtk2.8-dev, libhighgui-dev, libswscale-dev
  
- Compilaci�n e instalaci�n gen�rica
  ----------------------------------

  ./configure
  make
  make install

- Compilaci�n e instalaci�n gen�rica (modo de depuraci�n)
  -------------------------------------------------------
  
  ./configure --enable-debug
  make
  make install

- Generaci�n de paquete fuente
  ----------------------------

  ./configure
  make dist

- Generaci�n paquete binario DEB
  ------------------------------

  ./configure
  make deb

- Generaci�n paquetes fuentes DEB
  -------------------------------
  
  ./configure
  make deb-src

  Forma antigua:

	1.- Aseg�rese de que config.status no existe (user make distclean)
    2.- Ejecutar: fakeroot debian/rules binary
    3.- Limpieza: fakeroot debian/rules clean

- Generaci�n de paquete RPM
  -------------------------

  ./configure
  make rpm

Windows
=======

- Pre-requisitos
  --------------
  
  wxWidgets = 2.8.x
  OpenCV> = 1.0
  Platform SDK (probado con PSDK-x86_WindowsServer2003_SP1 (2005))
  DirectX SDK 9.0 Update (febrero de 2005) o posterior
  
- Construcci�n con Visual Studio 2003
  -----------------------------------

  Compilar proyecto
  \Microsoft Platform SDK\Samples\Multimedia\DirectShow\BaseClasses\
  Funciona con VS2003, pero tambi�n deber�a funcionar con versiones m�s 
  recientes de VS.
  La soluci�n de Visual Studio (.sln) est� en el directorio win32/
  Debe establecer las variables de entorno siguientes:

    WXWIN para que apunte a la carpeta wxWidgets
    CVPATH para que apunte a la carpeta opencv1
    PSDK_DIR para que apunte a la carpeta del Platform SDK

  Construir como Release.

  Una vez compilado, es posible que desee crear el paquete instalador.
  Emplee para ello Inno Setup y el fichero .iss bajo win32/