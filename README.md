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


## ⚡ Getting Started


### 🧱 Prerequisites
To assemble such a shoe, you will need the following components:

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
    
### 🛠️ built the system

1️⃣ First, you need to solder the piezos together in groups of 5. Each group should be connected in series.
   To connect them in series, you need to solder the white cap of one piezo to the gold frame of the next piezo, as shown in the attached picture. In each group, you should leave 1 wire coming out of the white cap and 1 wire coming out of the gold frame unsoldered.
   Now, you should connect all the groups in parallel. To connect in parallel, you solder all the wires coming out from the white caps of the piezos to one wire and all the wires coming out from the gold frames to a second wire, as shown in the attached picture.

![piezo connect image](/media/connectPiezo.jpg)

2️⃣ connect the piezo and the battery to the LTC3588 Energy Harvester. The wires coming out from the piezos should be connected to th PZT pins of the energy harvester, while the batter should be connected to the "Input" and the "GND" pins of the energy harvester. In addition, make sure that both 1/0 pins are callibrated to 1 to ensure an output voltage of 3.6V. 

3️⃣ Saperatly from connect the button to the battery 

4️⃣ connect the 868-915MHz Antenna to Heltec Cubecell AB02S with the and connect one of the heltec to the battery

5️⃣ Install the code provided and calibrate the Heltec on the shoe with a distress dispatcher’s code. Calibrate the other Heltec with a code for rescuers.

**Now the shoes are ready to be used**

### 🏗️ Installing


## ⚙️ Built With
