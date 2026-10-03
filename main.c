#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>

// Estructura y función del sistema para mostrar notificaciones en la pantalla de la PS5
typedef struct notify_request {
    char useless1[45];
    char message[3075];
} notify_request_t;

int sceKernelSendNotificationRequest(int, notify_request_t*, size_t, int);

void show_notification(const char *msg) {
    notify_request_t req;
    bzero(&req, sizeof(req));
    strncpy(req.message, msg, sizeof(req.message) - 1);
    sceKernelSendNotificationRequest(0, &req, sizeof(req), 0);
}

// Función para copiar un archivo individual
int copy_file(const char *src, const char *dest) {
    FILE *fsrc = fopen(src, "rb");
    if (!fsrc) return -1;
    
    FILE *fdest = fopen(dest, "wb");
    if (!fdest) {
        fclose(fsrc);
        return -1;
    }
    
    char buffer[8192];
    size_t bytes;
    while ((bytes = fread(buffer, 1, sizeof(buffer), fsrc)) > 0) {
        fwrite(buffer, 1, bytes, fdest);
    }
    
    fclose(fsrc);
    fclose(fdest);
    return 0;
}

// Función recursiva para copiar directorios
void copy_dir(const char *src_path, const char *dest_path) {
    DIR *dir = opendir(src_path);
    if (!dir) return;

    mkdir(dest_path, 0777);

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        char src_full[1024];
        char dest_full[1024];
        snprintf(src_full, sizeof(src_full), "%s/%s", src_path, entry->d_name);
        snprintf(dest_full, sizeof(dest_full), "%s/%s", dest_path, entry->d_name);

        struct stat st;
        if (stat(src_full, &st) == 0) {
            if (S_ISDIR(st.st_mode)) {
                copy_dir(src_full, dest_full);
            } else if (S_ISREG(st.st_mode)) {
                copy_file(src_full, dest_full);
            }
        }
    }
    closedir(dir);
}

int main(int argc, char *argv[]) {
    char usb_path[64];
    int found = 0;

    show_notification("Buscando carpeta ps5_autoloader en USB...");

    // Buscar en los puntos de montaje de USB del 0 al 7
    for (int i = 0; i <= 7; i++) {
        snprintf(usb_path, sizeof(usb_path), "/mnt/usb%d/ps5_autoloader", i);
        
        struct stat st;
        if (stat(usb_path, &st) == 0 && S_ISDIR(st.st_mode)) {
            found = 1;
            break;
        }
    }

    if (!found) {
        show_notification("Error: No se encontro ps5_autoloader en la USB");
        return -1;
    }

    show_notification("Copiando archivos a la memoria interna...");

    const char *dest_dir = "/data/ps5_autoloader";
    copy_dir(usb_path, dest_dir);

    show_notification("¡Copia completada con exito!");

    return 0;
}

