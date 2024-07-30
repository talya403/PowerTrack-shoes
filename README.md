# PowerTrack-shoes

![Project Cover Image](/media/coverImage.png)


## 👥 The Team 
**Team Members**
- [Itay Avidar](name@emial.com)
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

1. Piezoelectric Disc (20 pieces)
2. 3D printed piezo bracket (if you don't have a printer, you can make it with cardboard)
3. LTC3588 Energy Harvester
4. Button
5. Heltec Cubecell AB02S (2 pieces)
6. 868-915MHz Antenna (2 pieces)
7. 800 mAh LiPo Battery
8. Soldering device
9. wires
    
### 🛠️ built the system

1️⃣ First, you need to connect the piezos in groups of 5. Within each group,they are connected in series.
   To connect them in series, you need to solder the white wire of one piezo to the gold contact of the next piezo, as shown in the attached picture.
   After that, all groups are connected in parallel. To connect in parallel, you solder all the white wires of the piezos to one wire and all the gold contacts to a second wire, as shown in theattached picture.

![piezo connect image](/media/connectPiezo.jpg)

2️⃣ connect the piezo and the battery to the  LTC3588 Energy Harvester 

3️⃣ connect the button to the battery 

4️⃣ connect the 868-915MHz Antenna to Heltec Cubecell AB02S with the and connect one of the heltec to the battery

5️⃣ Install the code provided and calibrate the Heltec on the shoe with a distress dispatcher’s code. Calibrate the other Heltec with a code for rescuers.

**Now the shoes are ready to use**

### 🏗️ Installing


## ⚙️ Built With
