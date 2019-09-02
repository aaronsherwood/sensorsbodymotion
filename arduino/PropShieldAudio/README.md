## Audio on the Teensy Prop Shield

### Install Libraries
* Copy the three libraries in the Libraries folder to your Arduino libraries folder. 
* Restart the Arduino app (if already opened).

### Load Files to the Prop Shield
* In the Arduino IDE set the USB Type to Raw HID
* Upload the teensytransfertool.ino sketch to the Teensy
* In your Arduino libraries folder navigate to the TeensyTransfer/extras folder
* Unzip the appropriate file for you OS (The gz - file contains the Linux-version, the *.zip the Windows-version, The .mac.zip file contains the Mac OS version)
* On the command line navigate to the TeensyTransfer/extras directory (same as above, in your Arduino libraris folder)
* Run `./teensytransfer <path_to_file>` to upload a file
* After upload switch USB Type back to Serial

### Play a File
* Load the MP3Player.ino sketch onto the Teensy
* *Make sure all pins are soldered onto Prop Shield, including the rear row of 7 pins (this includes the necessary DAC)*
