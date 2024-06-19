# Arty Z7 Pin Assignments
############################
# On-board led             #
############################
#set_property -dict { PACKAGE_PIN R14    IOSTANDARD LVCMOS33 } [get_ports { led_0[0] }]; #IO_L6N_T0_VREF_34 Sch=LED0
#set_property -dict { PACKAGE_PIN P14    IOSTANDARD LVCMOS33 } [get_ports { led_0[1] }]; #IO_L6P_T0_34 Sch=LED1
#set_property -dict { PACKAGE_PIN N16    IOSTANDARD LVCMOS33 } [get_ports { led_0[2] }]; #IO_L21N_T3_DQS_AD14N_35 Sch=LED2
#set_property -dict { PACKAGE_PIN M14    IOSTANDARD LVCMOS33 } [get_ports { led_0[3] }]; #IO_L23P_T3_35 Sch=LED3
set_property PACKAGE_PIN R14 [get_ports LED_0[0]]
set_property IOSTANDARD LVCMOS33 [get_ports LED_0[0]]
set_property PACKAGE_PIN P14 [get_ports LED_0[1]]
set_property IOSTANDARD LVCMOS33 [get_ports LED_0[1]]
set_property PACKAGE_PIN N16 [get_ports LED_0[2]]
set_property IOSTANDARD LVCMOS33 [get_ports LED_0[2]]
set_property PACKAGE_PIN M14 [get_ports LED_0[3]]
set_property IOSTANDARD LVCMOS33 [get_ports LED_0[3]]
