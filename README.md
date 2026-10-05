# **PS5 Autoloader Update Payload**



Un payload en C diseñado para consolas PlayStation 5 que automatiza la búsqueda de una carpeta específica (`ps5\_autoloader`) en dispositivos de almacenamiento USB conectados (puertos `usb0` a `usb7`) y la copia de forma recursiva al directorio interno `/data/` de la consola.



Incluye notificaciones emergentes nativas en pantalla para mantener al usuario informado en todo momento sobre el progreso.



## **🚀 Características**

Detección Automática de USB: Escanea los puntos de montaje de la consola (`/mnt/usb0` hasta `/mnt/usb7`) para localizar la carpeta de origen.

Copia Recursiva: Capaz de transferir carpetas completas, subdirectorios y archivos de cualquier tamaño de manera eficiente.

Feedback Visual (Notificaciones): Utiliza `sceKernelSendNotificationRequest` para mostrar avisos nativos en la interfaz de la PS5 indicando:

Cuando inicia la búsqueda en la USB.

Si no se encuentra el directorio de origen.

Cuando el proceso de copia ha comenzado.

El aviso de éxito al finalizar la transferencia.



## **🛠️ Requisitos de Compilación**

Este proyecto está diseñado para ser compilado utilizando el PS5 Payload SDK y la herramienta `prospero-clang` en un entorno Linux (como Ubuntu o WSL en Windows).



## **Instrucciones de Compilación:**

1\. Clona o ubica este repositorio dentro de los samples del SDK.

2\. Ejecuta el comando de compilación:

make clean \&\& make



## **📖 Instrucciones de Uso:**

1\. Preparar la Memoria USB:

&#x20;  - Formatea una unidad de almacenamiento USB en formato exFAT o FAT32.

&#x20;  - En la raíz de la memoria USB, crea una carpeta con el nombre exacto: ps5\_autoloader.

&#x20;  - Coloca dentro de esta carpeta todos los payloads y el archivo autoload.txt para transferir de manera automática a la consola.



2\. Conectar la USB a la PS5:

&#x20;  - Inserta la memoria USB en cualquiera de los puertos USB disponibles de la consola PlayStation 5.



3\. Ejecutar el Payload:

&#x20;  - Lanza o inyecta el payload compilado (.elf) utilizando tu método de carga o exploit favorito en la PS5.



4\. Monitorear el Proceso:

&#x20;  - El payload escaneará automáticamente los puertos desde usb0 hasta usb7.

&#x20;  - Verás una serie de notificaciones emergentes nativas en la pantalla indicando el progreso.



5\. Verificación:

&#x20;  - Una vez finalizado el proceso, los archivos estarán disponibles dentro del directorio interno /data/ de la PS5.



## **📖 Instructions for use:**

1\. Prepare the USB Drive:

\- Format a USB storage drive in exFAT or FAT32 format.

\- In the root directory of the USB drive, create a folder with the exact name: ps5\_autoloader.

\- Place all payloads and the autoload.txt file inside this folder to automatically transfer to the console.



2\. Connect the USB Drive to the PS5:

\- Insert the USB drive into any of the available USB ports on the PlayStation 5 console.



3\. Run the Payload:

\- Launch or inject the compiled payload (.elf) using your preferred loading method or exploit on the PS5.



4\. Monitor the Process:

\- The payload will automatically scan the ports from usb0 to usb7.

\- You will see a series of native pop-up notifications on the screen indicating the progress.



5\. Verification:

\- Once the process is complete, the files will be available in the PS5's /data/ directory.



#### 🤖 AI-Assisted Development



This project was developed with the assistance of \*\*\[Google Gemini](https://gemini.google.com/)\*\*.

The source code was generated with the help of Gemini and subsequently reviewed and tested.

