local testModule = require "testModule"

local LOOP_PERIOD_MS = 1000;
local IDLE_AT_STARTUP_MS = 5000;

tmr.alarm(1,IDLE_AT_STARTUP_MS,0,function()
init()
loop()
tmr.alarm(2,LOOP_PERIOD_MS,1,function()loop()end)
end)

function init()
uart.setup(0,115200,8,0,1);
end

function loop()
testModule.testFunc()
end

--TODO, figure out the way tmr.alarm works.