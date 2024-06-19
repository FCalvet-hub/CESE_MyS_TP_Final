// Copyright 1986-2018 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2018.1 (win64) Build 2188600 Wed Apr  4 18:40:38 MDT 2018
// Date        : Wed Jun 19 10:00:54 2024
// Host        : DESKTOP-AG6MLBM running 64-bit major release  (build 9200)
// Command     : write_verilog -force -mode synth_stub
//               c:/Users/fert2/Desktop/_MyS/lab5/lab5.srcs/sources_1/bd/system/ip/system_vio_0_0/system_vio_0_0_stub.v
// Design      : system_vio_0_0
// Purpose     : Stub declaration of top-level module interface
// Device      : xc7z010clg400-1
// --------------------------------------------------------------------------------

// This empty module with port declaration file causes synthesis tools to infer a black box for IP.
// The synthesis directives are for Synopsys Synplify support to prevent IO buffer insertion.
// Please paste the declaration into a Verilog source file or add the file as an additional source.
(* X_CORE_INFO = "vio,Vivado 2018.1" *)
module system_vio_0_0(clk, probe_in0, probe_in1, probe_out0, 
  probe_out1)
/* synthesis syn_black_box black_box_pad_pin="clk,probe_in0[3:0],probe_in1[3:0],probe_out0[1:0],probe_out1[3:0]" */;
  input clk;
  input [3:0]probe_in0;
  input [3:0]probe_in1;
  output [1:0]probe_out0;
  output [3:0]probe_out1;
endmodule
