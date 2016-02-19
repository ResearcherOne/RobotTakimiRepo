local theProgram = require "theProgram"

local LOOP_PERIOD_MS = 5000;
local IDLE_AT_STARTUP_MS = 10000;

tmr.alarm(1,IDLE_AT_STARTUP_MS,0,function()
theProgram.init()
theProgram.loop()
tmr.alarm(2, LOOP_PERIOD_MS, 1, function()theProgram.loop()end)
end)