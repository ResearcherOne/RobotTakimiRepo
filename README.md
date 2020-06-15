# Description
- Aim is to build a modular robotic platform that will enable you to develop robotic systems on top of self-surviving (e.g. charge itself in unknown environments) and self localizing (using LIDAR systems) system.

# Mapping a Dorm Room With The Prototype
[![Mapping a dorm room.](http://i.imgur.com/aGk2MWS.png)](http://www.youtube.com/watch?v=oFOAtAxZN7c&t=0m44s "Mapping a dorm room.")
[![Mapping a dorm room.](https://raw.githubusercontent.com/ResearcherOne/RobotTakimiRepo/master/images/robot.png)](https://www.youtube.com/watch?v=Zqhcy5wxcf4 "Plugging to Outlet.")

# Video Log of Development of The Robot (Highly Recommended to Watch!)
https://www.youtube.com/watch?v=pvZsUYuiq-Y&list=PLIdKqNOzltlwOTcxoQ6y2CK0AK1hCf2Rg&index=1
		
# How It Works?
RP-LIDAR 360 and Camera mounted Raspberry Pi will be the heart of this system. Raspberry Pi will utilize the following modules in order to achieve locatilaztion and self-charge from plugs;
- wheelModule
  - 4 Independent Wheels & Encoders
  - Arduino
  - Esp8266
- roboticArmModule
  - Robotic Arm
  - Arduino
  - Esp8266
- batteryModule
  - accumulator (akü)
- brainModule
  - Raspberry Pi (MQTT server, WiFi AccessPoint)
  - Webcam (for recognition of wall outlets)
# Contact
- birkan.kolcu@ozu.edu.tr

# For Helping Me at The Different Stages of The Project, Special Thanks Goes to:
- Gürol Sağlam
- Sami Menteş
- Burak Kara
- Emir Ünlütürk
- Oğulcan Cingiler
- Mehmet Mert Özgün
		
