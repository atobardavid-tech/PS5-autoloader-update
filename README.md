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

## **📖 Inside Autoload.txt:**

Place the payload name ps5_autoloader_updater.elf at the end of the list to avoid conflicts with 
the .elf file loading process.

```bash
   	!3000
	shadowmountplus.elf
	!3000
	kstuff-1.13-fpkg-dr-test5.elf
	!11000
	pldmgr_v0.5.1.elf
	!2000
	pegasus_dl.elf
	!2000
	ps5_autoloader_updater.elf
```

## **Acknowledgements**

* Thanks to **Drakmor** and the **ShadowMountPlus** project for providing a reference for the PS5 system language 
detection implementation used in this project. The original implementation was analyzed with the help of an AI assistant 
to understand how the language detection worked and adapt the approach to this project.
* Special thanks to the **[PS5 Payload SDK](https://github.com/ps5-payload-dev/sdk)** developers for providing the SDK used 
to build this project.


#### 🤖 AI-Assisted Development

This project was developed with the assistance of **[Google Gemini](https://gemini.google.com/)** and **ChatGPT by OpenAI**, 
used for code generation, debugging, testing, and development guidance.


