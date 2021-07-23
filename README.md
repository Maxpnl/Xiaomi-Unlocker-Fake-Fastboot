# Xiaomi Unlocker Fake Fastboot

## What it does
This tool is a workaround for errors like "read failed, please reboot the device or refresh" and similar errors, it will fake communications with the device to get the signature to run the `fastboot oem unlock SIGNATURE_FILE`

## When should you use it
To understand if this tool could fix your problems with the Xiaomi Unlocker tool, open the cmd from windows start and run the following commands:
- `cd C:\FOLDER\TO\XIAOMI\UNLOCKER\TOOL`
- `fastboot oem device-info` 

if the fastboot command hangs try pressing `CTRL+C` and run it again, and again, until you receive a response that isn't an error, if after a few tries (could be many), you receive something like

```
...
(bootloader) Verity mode: true
(bootloader) Device unlocked: false
(bootloader) Device critical unlocked: false
(bootloader) Charger screen enabled: false
OKAY [  0.010s]
finished. total time: 0.011s

```

**and you didn't get this response on the FIRST TRY**, it means that this tool will help you cirvumvent the problems you are facing unlocking the bootloader, these problems are most likely happening because you have an AMD processor, but there could be other reasons.

## Why it helps
Xiaomi Unlocker Tool needs to receive *"predictable"* answers from fastboot, if fastboot behaves weirdly and keeps acting differently to the same command input, meaning that it will either:
- hang
- give you some error
- give you the right answer

the official unlocker tool will not work, so we'll need to tinker with it a little bit.

## How to use it
### Preparing everything
First of all you need to get the right answers from fastboot, so, enter fastboot mode from your phone and connect it to a USB port. These are the commands you'll want to run until they give you the answer you want, after you get the right answer, you should just copy and paste it inside the corresponding txt file (to understand how the answer should look like, take a look at the file)

| Command                    | Output File         |
| -------------------------- | ------------------- |
| `fastboot devices`         | devices.txt         |
| `fastboot oem device-info` | oem device-info.txt |
| `fastboot getvar product`  | get_product.txt     |

There are other txt files but (**except for get_token.txt**) you can leave them like they are right now
### Unlocking the bootloader
Copy the files from this tool inside the Xiaomi Tool Unlocker, replacing fastboot (you can just rename the current one to *fastboot_orig.exe* and avoid copying the *fastboot_orig.exe* provided by this tool), from now on, **if you want to use the REAL fastboot, you should use fastboot_orig.exe**

After doing that you should get the token from your device using `fastboot_orig getvar token` (just keep spamming it like for the other commands until you get the token, there could be errors like `GetVar Variable Not found` that will make you think there's no token, but there is so just keep trying), there are other possible commands like `fastboot_orig oem get_token` as far as I have seen in Ghidra, but the first one worked for me (if your device uses `oem get_token` you should change the fastboot.c file, handle it and recompile it!).

As soon as you get the token you should paste it inside `get_token.txt` (paste the whole output of fastboot like for the other commands, and make sure it's the file inside the Xiaomi Unlocker).

Now, if for any reason your device restarts, **YOU SHOULD GET A NEW TOKEN**, this is because it refreshes everytime it boots.

After doing all that, you'll need to start the Xiaomi Unlocker tool, you'll see that it will immediatly detect the device, no matter if the device is actually connected to an usb port, this is because by using this tool you are making the Xiaomi Unlocker use a fake fastboot that will reply to the commands you ran before in a static way (it will just open the output files and print them).

Before pressing the Unlock button, you'll need to **open a task manager and be prepared to kill the Xiaomi Unlock process** (I recommend using Process Explorer as it's easier to use).

As soon as you have located the process, proceed to press unlock and keep an eye on the xiaomi unlocker tool folder, **as soon as you see a file named like** `XXXXXXXX_sig.data` (XXXXXXXX should be the first string inside devices.txt) **kill the Xiaomi Unlocker tool process from the task manager!**.

If you succeded, this file `XXXXXXXX_sig.data` will still be there, otherwise you'll have to reopen xiaomi unlocker and try again.

Now, you are almost done, the only thing left to do is to run `fastboot_orig oem unlock XXXXXXXX_sig.data`

If it succeeds, I hope you had less of a hard time than I had! Otherwise just keep spamming the command, if the device reboots without succeeding, try again starting from the beginning of the **Unlocking the bootloader** chapter.

## Compiling
Just use mingw and run `gcc fastboot.c -o fastboot.exe`

