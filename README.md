# PS5 Autoloader Update Payload

Un payload en C diseñado para consolas PlayStation 5 que automatiza la búsqueda de una carpeta específica (`ps5_autoloader`) en dispositivos de almacenamiento USB conectados (puertos `usb0` a `usb7`) y la copia de forma recursiva al directorio interno `/data/` de la consola. 

Incluye notificaciones emergentes nativas en pantalla para mantener al usuario informado en todo momento sobre el progreso.

## 🚀 Características

- **Detección Automática de USB:** Escanea los puntos de montaje de la consola (`/mnt/usb0` hasta `/mnt/usb7`) para localizar la carpeta de origen.
- **Copia Recursiva:** Capaz de transferir carpetas completas, subdirectorios y archivos de cualquier tamaño de manera eficiente.
- **Feedback Visual (Notificaciones):** Utiliza `sceKernelSendNotificationRequest` para mostrar avisos nativos en la interfaz de la PS5 indicando:
  - Cuando inicia la búsqueda en la USB.
  - Si no se encuentra el directorio de origen.
  - Cuando el proceso de copia ha comenzado.
  - El aviso de éxito al finalizar la transferencia.

## 🛠️ Requisitos de Compilación

Este proyecto está diseñado para ser compilado utilizando el [PS5 Payload SDK](https://github.com/JohnTornblom/ps5-payload-sdk) y la herramienta `prospero-clang` en un entorno Linux (como Ubuntu o WSL en Windows).

### Instrucciones de Compilación:
1. Clona o ubica este repositorio dentro de los samples del SDK.
2. Ejecuta el comando de compilación:
   ```bash
   make clean && make
