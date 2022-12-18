# ESP32 based WS2812 Controller

###### CURRENT VERSION: 1.0.0
###### All updates made to this project are mentioned in the **versionlist.txt** file.

## ABOUT THE PROJECT
* This is a microcontroller-based LED-Array Controller.
* The controller used in this project is an ESP32.
* You need a WiFi network, and an MQTT broker to use this device.
* ESP32 has subscribed to a topic and the payload of the message is the R-G-B values for the LED array.
* This project involves Electronic circuitry and C-programming.
* To make this project, you first need to build the electronic circuitry to utilize the complete set of features.
* After all the peripherals are tested...upload the main **controller.ino** code provided in the **/code files/controller** folder. 

## STEPS TO MAKE THE BOARD
* Schematic Diagrams, Bill Of Materials, and Board Routing files are provided in the **/PCB files** folder.
* Create a PCB either via Etching, GPP, or by paying a professional to create it for you.\
*NOTE: The routing of the board has been done specifically to accommodate GPP boards...for those who cannot purchase or etch PCBs. The bottom layer (blue) wires can be treated as tracks on the bottom layer, and the top layer (red) wires can be treated as jumpers.*
* Assemble and solder all the components.
* Do a visual inspection of the board, and ensure that no two different tracks are shorted.

## STEPS TO RUN THE SOFTWARE
* Open the **controller.ino** file through the Arduino software and upload the code to your Arduino Nano controller.
* The device is now ready!

## HOW TO USE THE DEVICE
*WARNING: HIGH VOLTAGE INVOLVED*\
*This Device uses 230V mains voltage to power up. Ensure that you are qualified to work on mains voltage.*  
*If you are not, seek professional help in making and working with AC connections.*   
*This project has been thoroughly tested at my end, and it has been working without any problems for 6 months now.*   
*I take no responsibility for any mishaps that may occur while working on the project.*

![Img](https://github.com/benahalkar/ESP32-WS2812-CONTROLLER/blob/main/images/connection_diagram.jpg)

* When the device is powered OFF... make the AC-power and DC-LED connections.
* Switch ON the device.
* The ESP will now connect to the WiFi network... and then to the MQTT broker.
* To light up the LED, send a JSON object with the R-G-B colors on the **sub_topic**. This will light up the WS2812 array with the corresponding color.
* After every color change, the ESP also sends out the same R-G-B color code on the **pub_topic**. I have used it as a fail-safe method to check if the color has been updated or not.
