/* Copyright (C) 2023 John Törnblom

This program is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation; either version 3, or (at your option) any
later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; see the file COPYING. If not, see
<http://www.gnu.org/licenses/>.  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>

// Structure and system function to display notifications on the PS5 screen
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

// Function to copy an individual file
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

// Recursive function to copy directories
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

    show_notification("Searching for ps5_autoloader folder on USB...");

    // Search in USB mount points from 0 to 7
    for (int i = 0; i <= 7; i++) {
        snprintf(usb_path, sizeof(usb_path), "/mnt/usb%d/ps5_autoloader", i);
        
        struct stat st;
        if (stat(usb_path, &st) == 0 && S_ISDIR(st.st_mode)) {
            found = 1;
            break;
        }
    }

    if (!found) {
        show_notification("Error: ps5_autoloader not found on USB");
        return -1;
    }

    show_notification("Copying files to internal storage...");

    const char *dest_dir = "/data/ps5_autoloader";
    copy_dir(usb_path, dest_dir);

    show_notification("Copy completed successfully!");

    return 0;
}