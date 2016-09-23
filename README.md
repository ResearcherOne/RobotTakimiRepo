#Description:
	Aim is to build a modular robotic platform that will eneable you to develop robotic systems that is mostly focused on
		localization and 2D LIDAR mapping.

#How It Works?
	RP-LIDAR 360 and Camera mounted Raspberry Pi will be the heart of this system. Raspberry Pi will utilize the following modules in order
		to achieve locatilaztion and self-charge from plugs;
			wheelModule
				4 Independent Wheels & Encoders
				Arduino
				Esp8266
			roboticArmModule
				Robotic Arm
				Arduino
				Esp8266
			batteryModule
				accumulator (akü)
				Esp8266
			brainModule
				Raspberry Pi (MQTT server, WiFi AccessPoint)
				
#Project Challanges:
+	-Haar-Traning to recognize wall plugs
	-Set-Up ROS
		-Set-Up ROS-Nodejs Integration
		-Create ROS module for image(plug) recognition
			alternative(1): craete the module on nodejs 
	-NodeJs MQTT client module
	-Set-Up MQTT server on Raspberry Pi
	-Use Raspberry Pi as Access Point (Use nodejs wifi api?)
	-Set-Up RPLIDAR 360 integration to ROS
		alternative(2): write a nodejs driver for it.
	
	!: In case of implementing alternative 1 & alternative 2 we won't need ROS to operate this system. We can
		just use nodeJs.

#Esp8266 SERIAL-MQTT Bridge
	#Description
		Esp8266 that uses NodeMCU firmware will send messages to MQTT channel, that are recieved from the serial that are in JSON format.
	
	#Project Challanges
		
	#Project Structure

#RaspberryPi NodeJs App:
	#Description
		This app will be nodeJs implementation of some ROS modules. Aim is to make easier to develop these modules.

	#Project Structure
		-mapperBot.js
			init()
			loop() --Loop will period around a minute.
		-wifiModule.js
			connectWifi()
			isWifiConnected()

	#Dependenencies:
		Wifi API:	https://github.com/tlhunter/node-wireless
		MQTT API: 
#Video Diary Link:
	https://www.youtube.com/watch?v=aMHOmCP7reY&list=PLIdKqNOzltlwOTcxoQ6y2CK0AK1hCf2Rg
