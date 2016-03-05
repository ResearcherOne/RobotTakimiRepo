local configModule = {}

configModule.MQTT = {}
configModule.MQTT.clientID = "moduleAlpha"
configModule.MQTT.username = "debugDevice" --Cloud MQTT te bu kullanici adli uyeye okuma izni vermeyi unutma.
configModule.MQTT.password = "12345"
configModule.MQTT.server = "m10.cloudmqtt.com"
configModule.MQTT.tlsPort = 38429
configModule.MQTT.unsecurePort = 18429
configModule.MQTT.secureConnection = false

configModule.Wifi = {}
configModule.Wifi.ssid = "Hey-Yo"
configModule.Wifi.password = "710710710"

return configModule