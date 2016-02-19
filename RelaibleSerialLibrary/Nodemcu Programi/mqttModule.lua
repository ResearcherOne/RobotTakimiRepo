local mqttModule = {}

local configModule = require "configModule"

mqttModule.connectionStatus = 0
local callbackMessageRecieved = nil

function mqttModule.initialize()
	MQTT = mqtt.Client(configModule.MQTT.clientID, 120, configModule.MQTT.username, configModule.MQTT.password)
	MQTT:lwt("/lwt", configModule.MQTT.clientID..":offline", 0, 0)
	MQTT:subscribe("/alive",0, function(client) print("subscribe success") end)
	MQTT:on("message", function(client, topic, data) messageRecievedMQTT(client, topic, data) end)
		--if data ~= nil then
		--print(data)
		--end
end

function mqttModule.connect()
	if (configModule.MQTT.secureConnection) then
		MQTT:connect(configModule.MQTT.server, configModule.MQTT.tlsPort, 1, 1, function(client) mqttModule.connectionStatus = 1 print("debug1") end)
	else
		MQTT:connect(configModule.MQTT.server, configModule.MQTT.unsecurePort, 0, 1, function(client) mqttModule.connectionStatus = 1 print("debug2") end)
	end
end

function mqttModule.updateStatus()
	mqttModule.connectionStatus = 0
	publishStatus = MQTT:publish("/alive","hello",0,0, function(client) mqttModule.connectionStatus = 1 end)
end

function mqttModule.setMessageRecievedCallback(func)
	callbackMessageRecieved = func
end

function messageRecieved(client, topic, data)
	mqttModule.connectionStatus = 1
end

return mqttModule