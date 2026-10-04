\# PS5 Autoloader Update Payload



Un payload en C diseñado para consolas PlayStation 5 que automatiza la búsqueda de una carpeta específica (`ps5\_autoloader`) en dispositivos de almacenamiento USB conectados (puertos `usb0` a `usb7`) y la copia de forma recursiva al directorio interno `/data/` de la consola.



Incluye notificaciones emergentes nativas en pantalla para mantener al usuario informado en todo momento sobre el progreso.



🚀 Características

Detección Automática de USB: Escanea los puntos de montaje de la consola (`/mnt/usb0` hasta `/mnt/usb7`) para localizar la carpeta de origen.

Copia Recursiva: Capaz de transferir carpetas completas, subdirectorios y archivos de cualquier tamaño de manera eficiente.

Feedback Visual (Notificaciones): Utiliza `sceKernelSendNotificationRequest` para mostrar avisos nativos en la interfaz de la PS5 indicando:

Cuando inicia la búsqueda en la USB.

Si no se encuentra el directorio de origen.

When el proceso de copia ha comenzado.

El aviso de éxito al finalizar la transferencia.



🛠️ Requisitos de Compilación

Este proyecto está diseñado para ser compilado utilizando el PS5 Payload SDK y la herramienta `prospero-clang` en un entorno Linux (como Ubuntu o WSL en Windows).



Instrucciones de Compilación:

1\. Clona o ubica este repositorio dentro de los samples del SDK.

2\. Ejecuta el comando de compilación:

make clean \&\& make



📖 Instrucciones de Uso:

1\. Preparar la Memoria USB:

&#x20;  - Formatea una unidad de almacenamiento USB en formato exFAT o FAT32.

&#x20;  - En la raíz de la memoria USB, crea una carpeta con el nombre exacto: ps5\_autoloader.

&#x20;  - Coloca dentro de esta carpeta todos los archivos, carpetas o datos que desees transferir de manera automática a la consola.



2\. Conectar la USB a la PS5:

&#x20;  - Inserta la memoria USB en cualquiera de los puertos USB disponibles de la consola PlayStation 5.



3\. Ejecutar el Payload:

&#x20;  - Lanza o inyecta el payload compilado (.elf) utilizando tu método de carga o exploit favorito en la PS5.



4\. Monitorear el Proceso:

&#x20;  - El payload escaneará automáticamente los puertos desde usb0 hasta usb7.

&#x20;  - Verás una serie de notificaciones emergentes nativas en la pantalla indicando el progreso.



5\. Verificación:

&#x20;  - Una vez finalizado el proceso, los archivos estarán disponibles dentro del directorio interno /data/ de la PS5.

