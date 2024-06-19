#include "xparameters.h"
#include "xgpio.h"
#include "led_ip.h"
#include "up_down_counter.h"
// Include scutimer header file
#include "xscutimer.h"

//====================================================
XScuTimer Timer;		/* Cortex A9 SCU Private Timer Instance */

#define ONE_TENTH 32500000 // half of the CPU clock speed/10

#define TIMER_DEVICE_ID		XPAR_XSCUTIMER_0_DEVICE_ID


#define SET_BIT(variable, bit_position) ((variable) |= (1 << (bit_position)))
#define CLEAR_BIT(variable, bit_position) ((variable) &= ~((1 << (bit_position))))
#define CHECK_BIT(variable, bit_position) (((variable) >> (bit_position)) & 1)
#define TOGGLE_BIT(variable, bit_position) ((variable) ^= (1 << (bit_position)))


typedef union {
	u32 reg;
	struct{
		u32 clk_i:1;	//clk_i  => slv_reg0(0),
		u32 clr_i:1;	//clr_i  => slv_reg0(1),
		u32 up_i:1;		//up_i   => slv_reg0(2),
		u32 down_i:1;	//down_i => slv_reg0(3),
	}bit;
}udc_slv_reg0_t;


int main (void)
{

	udc_slv_reg0_t udc_slv_reg0;
   XGpio dip, push;
   int psb_check, dip_check, dip_check_prev, count, Status;

   // PS Timer related definitions
   XScuTimer_Config *ConfigPtr;
   XScuTimer *TimerInstancePtr = &Timer;

   xil_printf("-- Start of the Program --\r\n");

   XGpio_Initialize(&dip, XPAR_SWITCHES_DEVICE_ID);
   XGpio_SetDataDirection(&dip, 1, 0xffffffff);

   XGpio_Initialize(&push, XPAR_BUTTONS_DEVICE_ID);
   XGpio_SetDataDirection(&push, 1, 0xffffffff);

   count = 0;

   // Initialize the timer
   ConfigPtr = XScuTimer_LookupConfig(TIMER_DEVICE_ID);
   Status = XScuTimer_CfgInitialize(TimerInstancePtr, ConfigPtr, ConfigPtr->BaseAddr);

   // Read dip switch values
   dip_check_prev = XGpio_DiscreteRead(&dip, 1);
   // Load timer with delay in multiple of ONE_TENTH
   XScuTimer_LoadTimer(TimerInstancePtr, ONE_TENTH*dip_check_prev);
   // Set AutoLoad mode
   XScuTimer_EnableAutoReload(TimerInstancePtr);
   // Start the timer
   XScuTimer_Start(TimerInstancePtr);





   while (1)
   {
	  // Read push buttons and break the loop if Center button pressed
	  psb_check = XGpio_DiscreteRead(&push, 1);
	  if(psb_check > 0)
	  {
		  xil_printf("Push button pressed: Exiting\r\n");
		  XScuTimer_Stop(TimerInstancePtr);
		  break;
	  }

	  dip_check = XGpio_DiscreteRead(&dip, 1);
	  if (dip_check != dip_check_prev) {
		  xil_printf("DIP Switch Status %x, %x\r\n", dip_check_prev, dip_check);
		  dip_check_prev = dip_check;
	  	  // load timer with the new switch settings
		  XScuTimer_LoadTimer(TimerInstancePtr, ONE_TENTH*dip_check);
		  count = 0;
	  }

	  if(XScuTimer_IsExpired(TimerInstancePtr)) {
			  // clear status bit
		  	  XScuTimer_ClearInterruptStatus(TimerInstancePtr);
		  	  // output the count to LED and increment the count
		  	  LED_IP_mWriteReg(XPAR_LED_PIN_S_AXI_BASEADDR, 0, count);

		  	  udc_slv_reg0.bit.clk_i = !udc_slv_reg0.bit.clk_i;	//toggle clock de UDC

		  	  switch (count) {
		  	    // Si `count` está entre 0 y 20 (inclusive):
		  	    case 0 ... 20:
		  	      // El contador incrementará.
		  	      udc_slv_reg0.bit.clr_i = 0;
		  	      udc_slv_reg0.bit.up_i = 1;
		  	      udc_slv_reg0.bit.down_i = 0;
		  	      break;

		  	    // Si `count` está entre 21 y 40 (inclusive):
		  	    case 21 ... 40:
		  	      // El contador decrementará.
		  	      udc_slv_reg0.bit.clr_i = 0;
		  	      udc_slv_reg0.bit.up_i = 0;
		  	      udc_slv_reg0.bit.down_i = 1;
		  	      break;

		  	    // Si `count` está entre 41 y 60 (inclusive):
		  	    case 41 ... 60:
		  	      // El contador se reiniciará.
		  	      udc_slv_reg0.bit.clr_i = 1;
		  	      udc_slv_reg0.bit.up_i = 0;
		  	      udc_slv_reg0.bit.down_i = 0;
		  	      break;

		  	    // Si `count` es igual a 61:
		  	    case 61:
		  	      // Se reinicia el contador a 0 y se desactivan todas las señales.
		  	      udc_slv_reg0.bit.clr_i = 0;
		  	      udc_slv_reg0.bit.up_i = 0;
		  	      udc_slv_reg0.bit.down_i = 0;
		  	      count = 0;
		  	      break;
		  	  }

		  	  // Se escribe el estado del contador en el registro de hardware.
		  	  UP_DOWN_COUNTER_mWriteReg(XPAR_UP_DOWN_COUNTER_0_S00_AXI_BASEADDR, 0, udc_slv_reg0.reg);

		  	  count++;
		  	  xil_printf("%d\r\n", count);
	  }
   }
   return 0;
}
