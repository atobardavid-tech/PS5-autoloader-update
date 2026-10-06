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
#include <stdint.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>

/*
 * ============================================================
 * PS5 Notification
 * ============================================================
 */

typedef struct notify_request {
    char useless1[45];
    char message[3075];
} notify_request_t;

int sceKernelSendNotificationRequest(
    int,
    notify_request_t *,
    size_t,
    int
);

/*
 * ============================================================
 * PS5 System Language
 * ============================================================
 */

int sceSystemServiceParamGetInt(int param_id, int32_t *value);

#define SCE_SYSTEM_SERVICE_PARAM_ID_LANG 1

/*
 * Language IDs used by the PS5 system.
 *
 * These correspond to the order found in sm_l10n.c:
 *
 * 0  ja-JP
 * 1  en-US
 * 2  fr-FR
 * 3  es-ES
 * 4  de-DE
 * 5  it-IT
 * 6  nl-NL
 * 7  pt-PT
 * 8  ru-RU
 * 9  ko-KR
 * 10 zh-TW
 * 11 zh-CN
 * 12 fi-FI
 * 13 sv-SE
 * 14 da-DK
 * 15 no-NO
 * 16 pl-PL
 * 17 pt-BR
 * 18 en-GB
 * 19 tr-TR
 * 20 es-MX
 * 21 ar-SA
 * 22 fr-CA
 * 23 cs-CZ
 * 24 hu-HU
 * 25 el-GR
 * 26 ro-RO
 * 27 th-TH
 * 28 vi-VN
 * 29 id-ID
 * 30 uk-UA
 */

typedef enum {
    LANG_JA_JP = 0,
    LANG_EN_US,
    LANG_FR_FR,
    LANG_ES_ES,
    LANG_DE_DE,
    LANG_IT_IT,
    LANG_NL_NL,
    LANG_PT_PT,
    LANG_RU_RU,
    LANG_KO_KR,
    LANG_ZH_TW,
    LANG_ZH_CN,
    LANG_FI_FI,
    LANG_SV_SE,
    LANG_DA_DK,
    LANG_NO_NO,
    LANG_PL_PL,
    LANG_PT_BR,
    LANG_EN_GB,
    LANG_TR_TR,
    LANG_ES_MX,
    LANG_AR_SA,
    LANG_FR_CA,
    LANG_CS_CZ,
    LANG_HU_HU,
    LANG_EL_GR,
    LANG_RO_RO,
    LANG_TH_TH,
    LANG_VI_VN,
    LANG_ID_ID,
    LANG_UK_UA
} language_id_t;


/*
 * ============================================================
 * Notification messages
 * ============================================================
 */

typedef struct {
    const char *searching;
    const char *not_found;
    const char *copying;
    const char *completed;
} notification_strings_t;


/*
 * English is used as the fallback language.
 */
static const notification_strings_t lang_en = {
    "Searching for ps5_autoloader folder on USB...",
    "Error: ps5_autoloader not found on USB",
    "Copying files to internal storage...",
    "Copy completed successfully!"
};


/*
 * Spanish (Spain)
 */
static const notification_strings_t lang_es_es = {
    "Buscando la carpeta ps5_autoloader en el USB...",
    "Error: no se encontro ps5_autoloader en el USB",
    "Copiando archivos al almacenamiento interno...",
    "¡Copia completada correctamente!"
};


/*
 * Spanish (Mexico)
 */
static const notification_strings_t lang_es_mx = {
    "Buscando la carpeta ps5_autoloader en el USB...",
    "Error: no se encontro ps5_autoloader en el USB",
    "Copiando archivos al almacenamiento interno...",
    "¡Copia completada correctamente!"
};


/*
 * Japanese
 */
static const notification_strings_t lang_ja = {
    "USBでps5_autoloaderフォルダを検索しています...",
    "エラー: USBにps5_autoloaderが見つかりません",
    "内部ストレージにファイルをコピーしています...",
    "コピーが正常に完了しました！"
};


/*
 * French (France)
 */
static const notification_strings_t lang_fr_fr = {
    "Recherche du dossier ps5_autoloader sur USB...",
    "Erreur : ps5_autoloader est introuvable sur USB",
    "Copie des fichiers vers le stockage interne...",
    "Copie terminee avec succes !"
};


/*
 * French (Canada)
 */
static const notification_strings_t lang_fr_ca = {
    "Recherche du dossier ps5_autoloader sur USB...",
    "Erreur : ps5_autoloader est introuvable sur USB",
    "Copie des fichiers vers le stockage interne...",
    "Copie terminee avec succes !"
};


/*
 * German
 */
static const notification_strings_t lang_de = {
    "Suche nach dem Ordner ps5_autoloader auf dem USB-Laufwerk...",
    "Fehler: ps5_autoloader wurde auf dem USB-Laufwerk nicht gefunden",
    "Dateien werden auf den internen Speicher kopiert...",
    "Kopiervorgang erfolgreich abgeschlossen!"
};


/*
 * Italian
 */
static const notification_strings_t lang_it = {
    "Ricerca della cartella ps5_autoloader sull'USB...",
    "Errore: ps5_autoloader non trovato sull'USB",
    "Copia dei file nella memoria interna...",
    "Copia completata con successo!"
};


/*
 * Dutch
 */
static const notification_strings_t lang_nl = {
    "Bezig met zoeken naar de map ps5_autoloader op USB...",
    "Fout: ps5_autoloader niet gevonden op USB",
    "Bestanden worden naar de interne opslag gekopieerd...",
    "Kopieren succesvol voltooid!"
};


/*
 * Portuguese (Portugal)
 */
static const notification_strings_t lang_pt_pt = {
    "A procurar a pasta ps5_autoloader no USB...",
    "Erro: ps5_autoloader nao encontrado no USB",
    "A copiar ficheiros para o armazenamento interno...",
    "Copia concluida com sucesso!"
};


/*
 * Portuguese (Brazil)
 */
static const notification_strings_t lang_pt_br = {
    "Procurando a pasta ps5_autoloader no USB...",
    "Erro: ps5_autoloader nao encontrado no USB",
    "Copiando arquivos para o armazenamento interno...",
    "Copia concluida com sucesso!"
};


/*
 * Russian
 */
static const notification_strings_t lang_ru = {
    "Поиск папки ps5_autoloader на USB...",
    "Ошибка: ps5_autoloader не найден на USB",
    "Копирование файлов во внутреннее хранилище...",
    "Копирование успешно завершено!"
};


/*
 * Korean
 */
static const notification_strings_t lang_ko = {
    "USB에서 ps5_autoloader 폴더를 검색하는 중...",
    "오류: USB에서 ps5_autoloader를 찾을 수 없습니다",
    "내부 저장소로 파일을 복사하는 중...",
    "복사가 성공적으로 완료되었습니다!"
};


/*
 * Chinese (Traditional)
 */
static const notification_strings_t lang_zh_tw = {
    "正在USB上搜尋ps5_autoloader資料夾...",
    "錯誤：在USB上找不到ps5_autoloader",
    "正在將檔案複製到內部儲存空間...",
    "複製成功完成！"
};


/*
 * Chinese (Simplified)
 */
static const notification_strings_t lang_zh_cn = {
    "正在USB上搜索ps5_autoloader文件夹...",
    "错误：在USB上找不到ps5_autoloader",
    "正在将文件复制到内部存储...",
    "复制成功完成！"
};


/*
 * Finnish
 */
static const notification_strings_t lang_fi = {
    "Etsitaan ps5_autoloader-kansiota USB:lta...",
    "Virhe: ps5_autoloader-kansiota ei loytynyt USB:lta",
    "Kopioidaan tiedostoja sisaiselle tallennustilalle...",
    "Kopiointi onnistui!"
};


/*
 * Swedish
 */
static const notification_strings_t lang_sv = {
    "Soker efter mappen ps5_autoloader pa USB...",
    "Fel: ps5_autoloader hittades inte pa USB",
    "Kopierar filer till intern lagring...",
    "Kopieringen slutfördes!"
};


/*
 * Danish
 */
static const notification_strings_t lang_da = {
    "Soger efter mappen ps5_autoloader pa USB...",
    "Fejl: ps5_autoloader blev ikke fundet pa USB",
    "Kopierer filer til internt lager...",
    "Kopiering fuldført!"
};


/*
 * Norwegian
 */
static const notification_strings_t lang_no = {
    "Soker etter mappen ps5_autoloader pa USB...",
    "Feil: ps5_autoloader ble ikke funnet pa USB",
    "Kopierer filer til intern lagring...",
    "Kopiering fullfort!"
};


/*
 * Polish
 */
static const notification_strings_t lang_pl = {
    "Wyszukiwanie folderu ps5_autoloader na USB...",
    "Blad: nie znaleziono ps5_autoloader na USB",
    "Kopiowanie plikow do pamieci wewnetrznej...",
    "Kopiowanie zakonczone pomyslnie!"
};


/*
 * English (United Kingdom)
 */
static const notification_strings_t lang_en_gb = {
    "Searching for ps5_autoloader folder on USB...",
    "Error: ps5_autoloader not found on USB",
    "Copying files to internal storage...",
    "Copy completed successfully!"
};


/*
 * Turkish
 */
static const notification_strings_t lang_tr = {
    "USB'de ps5_autoloader klasoru araniyor...",
    "Hata: USB'de ps5_autoloader bulunamadi",
    "Dosyalar dahili depolamaya kopyalaniyor...",
    "Kopyalama basariyla tamamlandi!"
};


/*
 * Arabic
 */
static const notification_strings_t lang_ar = {
    "جار البحث عن مجلد ps5_autoloader على USB...",
    "خطأ: لم يتم العثور على ps5_autoloader على USB",
    "جار نسخ الملفات إلى وحدة التخزين الداخلية...",
    "اكتمل النسخ بنجاح!"
};


/*
 * Czech
 */
static const notification_strings_t lang_cs = {
    "Hledani slozky ps5_autoloader na USB...",
    "Chyba: ps5_autoloader nebyl na USB nalezen",
    "Kopirovani souboru do interniho uloziste...",
    "Kopirovani bylo uspesne dokonceno!"
};


/*
 * Hungarian
 */
static const notification_strings_t lang_hu = {
    "A ps5_autoloader mappa keresese USB-n...",
    "Hiba: a ps5_autoloader nem talalhato az USB-n",
    "Fajlok masolasa a belso tarhelyre...",
    "A masolas sikeresen befejezodott!"
};


/*
 * Greek
 */
static const notification_strings_t lang_el = {
    "Αναζήτηση του φακέλου ps5_autoloader στο USB...",
    "Σφάλμα: δεν βρέθηκε το ps5_autoloader στο USB",
    "Αντιγραφή αρχείων στον εσωτερικό χώρο αποθήκευσης...",
    "Η αντιγραφή ολοκληρώθηκε με επιτυχία!"
};


/*
 * Romanian
 */
static const notification_strings_t lang_ro = {
    "Se cauta folderul ps5_autoloader pe USB...",
    "Eroare: ps5_autoloader nu a fost gasit pe USB",
    "Se copiaza fisierele in stocarea interna...",
    "Copierea a fost finalizata cu succes!"
};


/*
 * Thai
 */
static const notification_strings_t lang_th = {
    "กำลังค้นหาโฟลเดอร์ ps5_autoloader บน USB...",
    "ข้อผิดพลาด: ไม่พบ ps5_autoloader บน USB",
    "กำลังคัดลอกไฟล์ไปยังพื้นที่จัดเก็บข้อมูลภายใน...",
    "คัดลอกเสร็จสมบูรณ์!"
};


/*
 * Vietnamese
 */
static const notification_strings_t lang_vi = {
    "Đang tìm thư mục ps5_autoloader trên USB...",
    "Lỗi: không tìm thấy ps5_autoloader trên USB",
    "Đang sao chép tệp vào bộ nhớ trong...",
    "Đã sao chép thành công!"
};


/*
 * Indonesian
 */
static const notification_strings_t lang_id = {
    "Mencari folder ps5_autoloader di USB...",
    "Kesalahan: ps5_autoloader tidak ditemukan di USB",
    "Menyalin file ke penyimpanan internal...",
    "Penyalinan berhasil diselesaikan!"
};


/*
 * Ukrainian
 */
static const notification_strings_t lang_uk = {
    "Пошук папки ps5_autoloader на USB...",
    "Помилка: ps5_autoloader не знайдено на USB",
    "Копіювання файлів у внутрішнє сховище...",
    "Копіювання успішно завершено!"
};


/*
 * ============================================================
 * Get notification language
 * ============================================================
 */

const notification_strings_t *get_language_strings(void)
{
    int32_t language_id = -1;

    /*
     * Ask the PS5 for the currently configured system language.
     */
    int ret = sceSystemServiceParamGetInt(
        SCE_SYSTEM_SERVICE_PARAM_ID_LANG,
        &language_id
    );

    /*
     * If the system call fails, use English.
     */
    if (ret != 0) {
        return &lang_en;
    }

    switch (language_id) {
        case LANG_JA_JP:
            return &lang_ja;

        case LANG_EN_US:
            return &lang_en;

        case LANG_FR_FR:
            return &lang_fr_fr;

        case LANG_ES_ES:
            return &lang_es_es;

        case LANG_DE_DE:
            return &lang_de;

        case LANG_IT_IT:
            return &lang_it;

        case LANG_NL_NL:
            return &lang_nl;

        case LANG_PT_PT:
            return &lang_pt_pt;

        case LANG_RU_RU:
            return &lang_ru;

        case LANG_KO_KR:
            return &lang_ko;

        case LANG_ZH_TW:
            return &lang_zh_tw;

        case LANG_ZH_CN:
            return &lang_zh_cn;

        case LANG_FI_FI:
            return &lang_fi;

        case LANG_SV_SE:
            return &lang_sv;

        case LANG_DA_DK:
            return &lang_da;

        case LANG_NO_NO:
            return &lang_no;

        case LANG_PL_PL:
            return &lang_pl;

        case LANG_PT_BR:
            return &lang_pt_br;

        case LANG_EN_GB:
            return &lang_en_gb;

        case LANG_TR_TR:
            return &lang_tr;

        case LANG_ES_MX:
            return &lang_es_mx;

        case LANG_AR_SA:
            return &lang_ar;

        case LANG_FR_CA:
            return &lang_fr_ca;

        case LANG_CS_CZ:
            return &lang_cs;

        case LANG_HU_HU:
            return &lang_hu;

        case LANG_EL_GR:
            return &lang_el;

        case LANG_RO_RO:
            return &lang_ro;

        case LANG_TH_TH:
            return &lang_th;

        case LANG_VI_VN:
            return &lang_vi;

        case LANG_ID_ID:
            return &lang_id;

        case LANG_UK_UA:
            return &lang_uk;

        default:
            return &lang_en;
    }
}


/*
 * ============================================================
 * Show notification
 * ============================================================
 */

void show_notification(const char *msg)
{
    notify_request_t req;

    bzero(&req, sizeof(req));

    strncpy(
        req.message,
        msg,
        sizeof(req.message) - 1
    );

    sceKernelSendNotificationRequest(
        0,
        &req,
        sizeof(req),
        0
    );
}


/*
 * ============================================================
 * Copy an individual file
 * ============================================================
 */

int copy_file(const char *src, const char *dest)
{
    FILE *fsrc = fopen(src, "rb");

    if (!fsrc)
        return -1;

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


/*
 * ============================================================
 * Recursive directory copy with extension filter only
 * ============================================================
 */

void copy_dir(const char *src_path, const char *dest_path)
{
    DIR *dir = opendir(src_path);

    if (!dir)
        return;

    mkdir(dest_path, 0777);

    struct dirent *entry;

    while ((entry = readdir(dir)) != NULL) {

        if (strcmp(entry->d_name, ".") == 0 ||
            strcmp(entry->d_name, "..") == 0)
            continue;

        char src_full[1024];
        char dest_full[1024];

        snprintf(
            src_full,
            sizeof(src_full),
            "%s/%s",
            src_path,
            entry->d_name
        );

        snprintf(
            dest_full,
            sizeof(dest_full),
            "%s/%s",
            dest_path,
            entry->d_name
        );

        struct stat st;

        if (stat(src_full, &st) == 0) {

            if (S_ISDIR(st.st_mode)) {

                copy_dir(
                    src_full,
                    dest_full
                );

            } else if (S_ISREG(st.st_mode)) {

                /* 
                 * Validar extensión (.elf o .txt) sin restricción de tamaño
                 */
                const char *ext = strrchr(entry->d_name, '.');
                if (ext != NULL && (strcmp(ext, ".elf") == 0 || strcmp(ext, ".txt") == 0)) {

                    copy_file(
                        src_full,
                        dest_full
                    );
                }
            }
        }
    }

    closedir(dir);
}

/*
 * ============================================================
 * Clear destination directory
 * ============================================================
 */

void clear_dir(const char *path)
{
    DIR *dir = opendir(path);

    if (!dir)
        return;

    struct dirent *entry;

    while ((entry = readdir(dir)) != NULL) {

        if (strcmp(entry->d_name, ".") == 0 ||
            strcmp(entry->d_name, "..") == 0)
            continue;

        char full_path[1024];

        snprintf(
            full_path,
            sizeof(full_path),
            "%s/%s",
            path,
            entry->d_name
        );

        struct stat st;

        if (stat(full_path, &st) == 0) {

            if (S_ISDIR(st.st_mode)) {

                clear_dir(full_path);
                rmdir(full_path);

            } else if (S_ISREG(st.st_mode)) {

                unlink(full_path);
            }
        }
    }

    closedir(dir);
}

/*
 * ============================================================
 * Main
 * ============================================================
 */

int main(int argc, char *argv[])
{
    char usb_path[64];
    int found = 0;

    /*
     * Detect the PS5 system language once at startup.
     */
    const notification_strings_t *msg =
        get_language_strings();


    /*
     * Search for ps5_autoloader.
     */
    show_notification(msg->searching);

    /*
     * Search USB mount points from usb0 to usb7.
     */
    for (int i = 0; i <= 7; i++) {

        snprintf(
            usb_path,
            sizeof(usb_path),
            "/mnt/usb%d/ps5_autoloader",
            i
        );

        struct stat st;

        if (stat(usb_path, &st) == 0 &&
            S_ISDIR(st.st_mode)) {

            found = 1;
            break;
        }
    }


    /*
     * Folder was not found.
     */
    if (!found) {

        show_notification(msg->not_found);

        return -1;
    }


    /*
     * Copy files.
     */
    show_notification(msg->copying);

    const char *dest_dir =
        "/data/ps5_autoloader";

    clear_dir(dest_dir);

    copy_dir(
        usb_path,
        dest_dir
    );


    /*
     * Finished.
     */
    show_notification(msg->completed);

    return 0;
}

