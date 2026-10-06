# **PS5 Autoloader Updater Payload**

A C-based payload designed for PlayStation 5 consoles that automates the search for a specific folder (`ps5_autoloader`) on connected USB storage devices 
(`usb0` through `usb7` ports) and recursively copies it to the console's internal `/data/` directory.It detects the console's language (supporting all 31 system languages)
 and includes native on-screen pop-up notifications (in the console's language) to keep the user informed at all times about the progress.

## **🚀 Features**

* **Automatic USB Detection:** Scans the console's mount points (`/mnt/usb0` through `/mnt/usb7`) to locate the source folder.
* **Recursive Copy:** Capable of efficiently transferring entire folders, subdirectories, and files of any size.
* **Visual Feedback (Notifications):** Uses `sceKernelSendNotificationRequest` to display native notices on the PS5 interface indicating:
  * When the USB search starts.
  * If the source directory is not found.
  * When the copy process has begun.
  * The success notice upon completion of the transfer.
* **Automatic Language Detection:** Uses `sceSystemServiceParamGetInt` to detect the PS5 system language and display notifications in the 
corresponding language.

## **What's new in v1.00**

* Added automatic detection of the PS5 system language.
* Added notification translations for all 31 languages supported by the PS5 system.
* Notifications are automatically displayed in the language configured on the console.

## **What's new in v1.01**

* Added file filtering: only `.elf` and `.txt` files are copied from the USB `ps5_autoloader` folder.
* Added destination cleanup: the existing contents of `/data/ps5_autoloader` are removed before copying the new files.
* This ensures that old files are not left behind when updating the contents of the destination folder.

## **🛠️ Build Requirements**

This project is designed to be compiled using the PS5 Payload SDK and the `prospero-clang` tool in a Linux environment (such as Ubuntu or WSL on Windows).

## **Build Instructions:**

1. Clone or place this repository inside the SDK's samples.
2. Run the compilation command:
   ```bash
   make clean && make

## **📖 Instructions for use:**

1\. Prepare the USB Drive:
\- Format a USB storage drive in exFAT or FAT32 format.
\- In the root directory of the USB drive, create a folder with the exact name: ps5\_autoloader.
\- Place all payloads and the autoload.txt file inside this folder to automatically transfer to the console.

2\. Connect the USB Drive to the PS5:
\- Insert the USB drive into any of the available USB ports on the PlayStation 5 console.

3\. Run the Payload:
\- Launch or inject the compiled payload (.elf) using your preferred loading method or exploit on the PS5.
\(Remember that the PS5 is listening on port 9021).

4\. Monitor the Process:
\- The payload will automatically scan the ports from usb0 to usb7.
\- You will see a series of native pop-up notifications on the screen indicating the progress.

5\. Verification:
\- Once the process is complete, the files will be available in the PS5's /data/ directory.

#### 🤖 AI-Assisted Development

This project was developed with the assistance of \*\*\[Google Gemini](https://gemini.google.com/)\*\*.
The source code was generated with the help of Gemini and subsequently reviewed and tested.
ChatGPT by OpenAI, used for code assistance, debugging, and development guidance.

