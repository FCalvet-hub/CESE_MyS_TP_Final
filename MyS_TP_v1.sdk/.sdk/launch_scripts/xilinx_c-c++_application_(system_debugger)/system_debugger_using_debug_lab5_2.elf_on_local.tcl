#If required use the below command and launch symbol server from an external shell.
#symbol_server.bat -S -s tcp::1534
connect -path [list tcp::1534 tcp:lseserver.ddns.net:3121]
source C:/Users/fert2/Desktop/_MyS/lab5/lab5.sdk/lab5_proj/ps7_init.tcl
targets -set -filter {jtag_cable_name =~ "Digilent Arty Z7 003017A4C8ABA" && level==0} -index 1
fpga -file C:/Users/fert2/Desktop/_MyS/lab5/lab5.sdk/lab5_proj/system_wrapper.bit
targets -set -nocase -filter {name =~"APU*" && jtag_cable_name =~ "Digilent Arty Z7 003017A4C8ABA"} -index 0
loadhw -hw C:/Users/fert2/Desktop/_MyS/lab5/lab5.sdk/lab5_proj/system.hdf -mem-ranges [list {0x40000000 0xbfffffff}]
configparams force-mem-access 1
targets -set -nocase -filter {name =~"APU*" && jtag_cable_name =~ "Digilent Arty Z7 003017A4C8ABA"} -index 0
stop
ps7_init
ps7_post_config
targets -set -nocase -filter {name =~ "ARM*#0" && jtag_cable_name =~ "Digilent Arty Z7 003017A4C8ABA"} -index 0
rst -processor
targets -set -nocase -filter {name =~ "ARM*#0" && jtag_cable_name =~ "Digilent Arty Z7 003017A4C8ABA"} -index 0
dow C:/Users/fert2/Desktop/_MyS/lab5/lab5.sdk/lab5_2/Debug/lab5_2.elf
configparams force-mem-access 0
targets -set -nocase -filter {name =~ "ARM*#0" && jtag_cable_name =~ "Digilent Arty Z7 003017A4C8ABA"} -index 0
con
