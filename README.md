# PowerTrack-shoes

![Project Cover Image](/media/coverImage.png)

## Table of Contents
- [The Team](#the-team)
- [Project Description](#project-description)
- [Getting Started](#getting-started)
    - [Prerequisites](#prerequisites)
    - [Installing](#installing)
- [Built With](#built-with)
  
## 👥 The Team 
**Team Members**
- [Itay Avidar](https://github.com/avidarit?tab=overview&from=2024-07-01&to=2024-07-31)
- [Talya Haya Feldhaim](talia403@emial.com)

**Supervisor**
- [Yuri Klebanov](http://www.yurikleb.com/)
- [Daniella Har Shalom](//)

## 📚 Project Description

Traveling without electricity poses risks, especially during emergencies. In the world today,
mobile phones are vital for safety and used to call for help when needed, but their usefulness
diminishes without recharge. Therefore, our goal is to create a self-sustaining product for
emergency assistance, independent of external power.

PowerTrace shoes are emergency shoes that can transmit their location when necessary. The
shoe features a layer of piezoelectric crystals embedded in the sole, which generate electricity
with each step. This energy is stored in an integrated battery and can later be used to power
a GPS module to pinpoint its location. The coordinates can then be sent through a transmitter,
allowing rescuers to locate and assist the wearer.

Our project included the following components:
1. Piezoelectric Discs (20 pieces)
2. 3D printed piezo bracket (if you don't have a printer, you can make it with cardboard)
3. LTC3588 Energy Harvester
4. Electrical switch, containing a button
5. Heltec Cubecell AB02S (2 pieces)
6. 868-915MHz Antenna (2 pieces)
7. 600 mAh LiPo Battery
8. 2 led in different colors
9. Soldering device
10. wires
11. Quechua NH100 shoes

Our project is taking advantage of the following technologies:
1. The piezoelectric effect
2. LORA transmission (868-915Mhz)
3. GPS


## ⚡ Getting Started


### 🧱 Prerequisites
Before starting please make sure to have huking shoes with a thick sole. Constructing the project demends soldering and handeling with hardware components. Therefore, please also make sure to posses a working soldering device and an orgenized space for it. 
In addition, you will need to use the Arduino IDE (you can download it [here](https://www.arduino.cc/en/software)).   

### 🛠️ 🏗️ Installing and building the system

1️⃣ Based on your shoes, design and print a sole to contain the 20 piezo discs and a bracket for the electronic components. You can use our design which is designated for Quechua NH100 shoes (size 45 EU).

2️⃣ Solder the piezos together in groups of 5. Each group should be connected in series.
   To connect them in series, you need to solder the white cap of one piezo to the gold frame of the next piezo, as shown in the attached picture. In each group, you should leave 1 wire coming out of the white cap and 1 wire coming out of the gold frame unsoldered.
   Now, you should connect all the groups in parallel. To connect in parallel, you solder all the wires coming out from the white caps of the piezos to one wire and all the wires coming out from the gold frames to a second wire, as shown in the attached picture. Now, fit the piezo discs inside the printed sole, so only 2 wires are coming out of it.

![piezo connect image](/media/connectPiezo.jpg)

3️⃣ connect the piezo sole and the battery to the LTC3588 Energy Harvester. The wires coming out from the sole should be connected to th PZT pins of the energy harvester, while the batter should be connected to the "Input" and the "GND" pins of the energy harvester. In addition, make sure that both 1/0 pins are callibrated to 1 to ensure an output voltage of 3.6V. Now, saperatly from the energy harvester, connect the button to the battery and to the Helltec module, so pressing the button will activate the module using the battery's power. 

4️⃣ Connect the 868-915MHz Antenna to the designaten "antenna" pin of the Heltec Cubecell AB02S. Connect also the 2 LEDs to 2 I/O pins on the helltec module. Now, download the code provided ("TX_Final") and upload it to the Helltec module connected the battery using the Arduino IDE. Make sure to adjust the pins in the code according to the I/O pins you've chosen. Then, download the code provided ("RX_Final") and upload it to the seconed Helltec module, that will ack as the reciever.

5️⃣ Pierce the inner sole of the shoes so it will have enough space to hold the electronic bracket. Place the TX helltec module, the antenna and the energy harvester inside the bracket, and place the piezo sole on top of it. Now, make 3 holes on the shoes ankel part, and place the button and the 2 LEDs in them. Lastly, Connect the RX helltec module to your computer, download the python code provided and run it.

**Now the shoes are ready to be used and when an SOS signal will be recived, a map containing the shoes location will appear**

## 🧪 Testing

Before going out and using the shoes for the first time, it is important to make sure it works properly:

1. Connect a voltmeter to the piezo sole and apply pressure on it. The voltmeter should present a pulse of voltage (that can get up to 30-35V in the pick of the pulse).
2. connect the voltmeter to the "input" and "GND" pins of the energy harvester after appling pressure on the piezo sole for few minutes. The voltmeter should present a constant 3.6V.
3. Press the SOS button and make sure both LEDs are turning on and immidietly turning off, before one of the start flashing.
4. Walk with the shoes for few minutes and the inspect that the box for the electronics didn't implode and all the components are are intact.
5. Press the SOS button while the shoes are exposed to the sky, wait a few minutes until one of the LEDs start flashing for 4 quick flashes in a row. It means that the GPS was succssesfuly calibrated. Now connect the RX helltec module to the computer and run the python code. The shoes's location should appear on the computer's screen.

## 🚀 Deployment

**The shoes are disgned to function outdoors.** Pressing the SOS button while the shoes are indoors or not exposed to the skys might cause the GPS to not calibrate or not to detect the shoes exact location. 
