local theProgram = {}

local configModule = require "configModule"
local mqttModule = require "mqttModule"

local MQTT = nil
local deviceState = 0 --Device is not connected to AP:0, Device is not connected to MQTT:1, Device is ready:2

function theProgram.init()
	uart.setup(0,9600,8,0,1); --What does echo do? (last argument)
	uart.on("data", "\n", function(data) uartProcessData(data) end, 0) --I guess last option is about "whether i should try to run the code as LUA or not?"
	configureWifi()
	mqttModule.initialize()
	print("System is initialized.")
	end

function theProgram.loop()
	updateDeviceState()
	mqttModule.updateStatus()
end

function updateDeviceState()
	if (isIpAvailable == 0) then
		deviceState = 0
	elseif (isIpAvailable == 1) then
		deviceState = 1
	elseif (deviceState == 1) then
		if (mqttModule.connectionStatus == 0) then
			mqttModule.connect()
		else
			deviceState = 2
		end
	end
	print("DeviceState:%d",deviceState)
end

function uartProcessData(data)
	if (string.find(data, "Header:") ~= nil) then
		uart.write(0, "Successfully Recieved Header:"..data)
	elseif (string.find(data, "Message:") ~= nil) then 
		uart.write(0, "Successfully Recieved Message:"..data)
	else
		uart.write(0, "Noo!")
	end
end

function isIpAvailable()
	if (wifi.sta.getip() ~= nil) then
		return 1
	else
		return 0
	end
end

function configureWifi()
	wifi.setmode(wifi.STATION)
	wifi.sta.config(configModule.Wifi.ssid,configModule.Wifi.password)
end

return theProgram

--TODO, figure out the way tmr.alarm works and what does their ID refers to.
--State 0 iken tekrar bağlanmaya çalışmalı. Autoconnection olayını açmalıyım.
--[[Notlar:
*Fonksiyonun çağrıldığı fonksiyondan aşağıda olması bir şeyi etkilemiyor.
*Fonksiyon modülü return etmeden önce tanımlanmalı yoksa hata veriyor.
*modulIsmı.fonksiyonIsmi seklinde bir fonksiyonu belirtmedikçe, fonksiyon local de kalıyor.
! Nodemcu modullerinin ismine dikkat et. Overwrite etme. Örnek: mqtt = nil deyip mqtt modülünü overwrite etmek.
]]--

--Arduino, dakikada bir alive mesajı yollasın. Böylece bağlantı sürsün.
--ESP serial den verileri paket olarak alıp aynı şekilde MQTT kanalına basacak.

--[[
Program overview:
if (validPackage){
	if (isConnectedToMQTT){
		sendPackage(recievedPackage)
	} else {
		connectMQTT(sendPackageContent(recievedPackage))
	}
} else {
	uart.write("Invalid package recieved.")
}

ValidPackage: "Header:headerContent\nMessage:messageContent\n"

]]--