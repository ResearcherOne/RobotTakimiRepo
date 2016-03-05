local mqttModule = {}

local configModule = require "configModule"

mqttModule.connectionStatus = 0 --No connection:0, Connected:1
mqttModule.isConnectFunctionCalled = false
local callbackMessageRecieved = nil

function messageRecievedMQTT(client, topic, data)
	print("Message Recieved:"..data)
end

function mqttModule.initialize()
	MQTT = mqtt.Client(configModule.MQTT.clientID, 120, configModule.MQTT.username, configModule.MQTT.password)
	MQTT:lwt("/lwt", configModule.MQTT.clientID..":offline", 0, 0)
	MQTT:on("message", function(client, topic, data) messageRecievedMQTT(client, topic, data) end)
end

function mqttModule.connect()
		mqttModule.isConnectFunctionCalled = true
	if (configModule.MQTT.secureConnection) then
		MQTT:connect(configModule.MQTT.server, configModule.MQTT.tlsPort, 1, 1, function(client) mqttModule.connectionStatus = 1 print("debug1") end)
	else
		MQTT:connect(configModule.MQTT.server, configModule.MQTT.unsecurePort, 0, 1, function(client) mqttModule.connectionStatus = 1 print("debug2") MQTT:subscribe("testTopic",0, function(conn) print("subscribe success") end) end)
	end
end

function mqttModule.updateStatus()
	mqttModule.connectionStatus = 0
	publishStatus = MQTT:publish("/alive","hello",0,0, function(client) mqttModule.connectionStatus = 1 end)
end

function mqttModule.setMessageRecievedCallback(func)
	callbackMessageRecieved = func
end

function mqttModule.close()
	mqttModule.isConnectFunctionCalled = false
	MQTT:close()
end

function messageRecieved(client, topic, data)
	mqttModule.connectionStatus = 1
end

return mqttModule