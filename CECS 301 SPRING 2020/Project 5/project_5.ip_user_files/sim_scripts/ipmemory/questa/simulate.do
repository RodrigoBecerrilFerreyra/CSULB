onbreak {quit -f}
onerror {quit -f}

vsim -t 1ps -lib xil_defaultlib ipmemory_opt

do {wave.do}

view wave
view structure
view signals

do {ipmemory.udo}

run -all

quit -force
