local theProgram = {}

local configModule = require "configModule"
local mqttModule = require "mqttModule"

local MQTT = nil
local deviceState = 0 --Device is not connected to AP:0, Device is not connected to MQTT but connected to AP:1, Device is ready, connected to MQTT:2


function configureWifi()
	wifi.setmode(wifi.STATION)
	wifi.sta.config(configModule.Wifi.ssid,configModule.Wifi.password)
end

function isIpAvailable()
	if (wifi.sta.getip() ~= nil) then
		return true
	else
		return false
	end
end

function updateDeviceState()
	if (isIpAvailable() ~= true) then
		deviceState = 0
		configureWifi()
	else
		if (deviceState == 0) then
			deviceState = 1
		else
			if (mqttModule.connectionStatus == 0) then
				deviceState = 1
				if (mqttModule.isConnectFunctionCalled) then
					mqttModule.close()
					mqttModule.connect()
				else
					mqttModule.connect()
				end
			else
				deviceState = 2
				mqttModule.updateStatus()
			end
		end
	end
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

function theProgram.init()
	uart.setup(0,9600,8,0,1); --What does echo do? (last argument)
	uart.on("data", "\n", function(data) uartProcessData(data) end, 0) --I guess last option is about "whether i should try to run the code as LUA or not?"
	configureWifi()
	mqttModule.initialize()
	print("System is initialized.")
	end

function theProgram.loop()
	updateDeviceState()
	print("Device State:",deviceState)
end

return theProgram

--TODO, figure out the way tmr.alarm works and what does their ID refers to.
--State 0 iken tekrar bağlanmaya çalışmalı. Autoconnection olayını açmalıyım.
--[[Notlar:
*Bir fonksiyon çağrıldığı fonksiyondan AŞAĞIDA OLAMAZ. LUA interpreter, daha önce çağrılmak istenen fonksiyonla karşılaşmadığı için nil value'yi çağırmaya çalışır.
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