#include "Interrupt_setup.h"



typedef struct {
	u32 OutputHz;	/* Output frequency */
	XInterval Interval;	/* Interval value */
	u8 Prescaler;	/* Prescaler value */
	u16 Options;	/* Option settings */
} TmrCntrSetup;

//*******for first timer******
#define TTC_TICK_DEVICE_ID	XPAR_XTTCPS_0_DEVICE_ID
#define TTC_TICK_INTR_ID	XPAR_XTTCPS_0_INTR
static TmrCntrSetup ticksetup={800, 0, 0, 0};	//800hz
//****************************

//******for second timer******
#define TTC_TICK_DEVICE1_ID	XPAR_XTTCPS_1_DEVICE_ID
#define TTC_TICK_INTR1_ID	XPAR_XTTCPS_1_INTR
static TmrCntrSetup ticksetup1={10, 0, 0, 0};	//10hz
//****************************


//GPIO definitions
#define GPIO_BANK			XGPIOPS_BANK2
#define GPIO_DEVICE_ID		XPAR_XGPIOPS_0_DEVICE_ID
#define INTC_DEVICE_ID		XPAR_SCUGIC_SINGLE_DEVICE_ID
#define GPIO_INTERRUPT_ID	XPAR_XGPIOPS_0_INTR

static XTtcPs TtcPsInst;
static XTtcPs TtcPsInst1;

static XGpioPs Gpio; /* The Instance of the GPIO Driver */

static XScuGic Intc; /* The Instance of the Interrupt Controller Driver */


int SetupTimerInt(){

	TmrCntrSetup *TimerSetup;
	XTtcPs_Config *Config;

	TimerSetup = &(ticksetup);

	TimerSetup->Options |= (XTTCPS_OPTION_INTERVAL_MODE |
	XTTCPS_OPTION_WAVE_DISABLE);

	Config = XTtcPs_LookupConfig(TTC_TICK_DEVICE_ID);

	XTtcPs_CfgInitialize(&TtcPsInst, Config, Config->BaseAddress);

	XTtcPs_SetOptions(&TtcPsInst, TimerSetup->Options);

	XTtcPs_CalcIntervalFromFreq(&TtcPsInst, TimerSetup->OutputHz,
			&(TimerSetup->Interval), &(TimerSetup->Prescaler));

	XTtcPs_SetInterval(&TtcPsInst, TimerSetup->Interval);

	XTtcPs_SetPrescaler(&TtcPsInst, TimerSetup->Prescaler);


	XScuGic_Connect(&Intc, TTC_TICK_INTR_ID,
	(Xil_ExceptionHandler)TickHandler, (void *)&TtcPsInst);

	XScuGic_Enable(&Intc, TTC_TICK_INTR_ID);

	XTtcPs_EnableInterrupts(&TtcPsInst, XTTCPS_IXR_INTERVAL_MASK);

	XTtcPs_Start(&TtcPsInst);
	//Xil_ExceptionEnable();
	//Xil_ExceptionEnableMask(XIL_EXCEPTION_IRQ);

}

int SetupTimerInt1(){

	TmrCntrSetup *TimerSetup;
	XTtcPs_Config *Config;
	//XTtcPs *TtcPsTick;

	TimerSetup = &(ticksetup1);

	//Set options, no PWM output , interrupt with interval
	TimerSetup->Options |= (XTTCPS_OPTION_INTERVAL_MODE |
	XTTCPS_OPTION_WAVE_DISABLE);


	Config = XTtcPs_LookupConfig(TTC_TICK_DEVICE1_ID);

	XTtcPs_CfgInitialize(&TtcPsInst1, Config, Config->BaseAddress);

	XTtcPs_SetOptions(&TtcPsInst1, TimerSetup->Options);

	int a=0;

	XTtcPs_CalcIntervalFromFreq(&TtcPsInst1, TimerSetup->OutputHz,
			&(TimerSetup->Interval), &(TimerSetup->Prescaler));

	XTtcPs_SetInterval(&TtcPsInst1, TimerSetup->Interval);

	XTtcPs_SetPrescaler(&TtcPsInst1, TimerSetup->Prescaler);


	XScuGic_Connect(&Intc, TTC_TICK_INTR1_ID,
	(Xil_ExceptionHandler)TickHandler1, (void *)&TtcPsInst1);

	XScuGic_Enable(&Intc, TTC_TICK_INTR1_ID);

	XTtcPs_EnableInterrupts(&TtcPsInst1, XTTCPS_IXR_INTERVAL_MASK);

	XTtcPs_Start(&TtcPsInst1);

}



//setup interrupt system and Gpio interrupts
int SetupGpioInterruptSystem(){
	XGpioPs_Config *ConfigPtr;

	ConfigPtr = XGpioPs_LookupConfig(GPIO_DEVICE_ID);
		if (ConfigPtr == NULL) {
			return XST_FAILURE;
	}


	XGpioPs_CfgInitialize(&Gpio, ConfigPtr, ConfigPtr->BaseAddr);
	//***********************************************************


	XScuGic_Config *IntcConfig;
	Xil_ExceptionInit();
	IntcConfig = XScuGic_LookupConfig(INTC_DEVICE_ID);
	XScuGic_CfgInitialize(&Intc, IntcConfig,
			IntcConfig->CpuBaseAddress);

	Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT,
					(Xil_ExceptionHandler)XScuGic_InterruptHandler,
					&Intc);


	//Connect GPIO handler to Intc driver
	XScuGic_Connect(&Intc, GPIO_INTERRUPT_ID,
					(Xil_ExceptionHandler)XGpioPs_IntrHandler,
	(void *)&Gpio);

	//set Interrupt type (in this case low edge, on buttons, both on switch). For more info, see xilinx API Driver documentation
	XGpioPs_SetIntrType(&Gpio, GPIO_BANK, 0xFF, 0x00, 0x30);

	//connect handler to gpio driver
	XGpioPs_SetCallbackHandler(&Gpio, (void *)&Gpio, ButtonHandler);

	//enable interrputs connected to bank (2)
	XGpioPs_IntrEnable(&Gpio, GPIO_BANK, 0b111111);

	//enable GPIO interrupts
	XScuGic_Enable(&Intc, GPIO_INTERRUPT_ID);

	//something
	//Xil_ExceptionEnableMask(XIL_EXCEPTION_IRQ);

	//after init, clearing gpio0,1 int registers is mandatory, because for some reason bank0 and 1 interrupts are set.

		XGpioPs_IntrClear(&Gpio,0,0xffffffff);
		XGpioPs_IntrClear(&Gpio,1,0xffffffff);

}

void change_freq(uint32_t freq){

	if(freq!=0){
		TmrCntrSetup *TimerSetup;
		TimerSetup = &(ticksetup1);
		ticksetup1.OutputHz=freq;

		XTtcPs_CalcIntervalFromFreq(&TtcPsInst1, TimerSetup->OutputHz,
				&(TimerSetup->Interval), &(TimerSetup->Prescaler));

		XTtcPs_SetInterval(&TtcPsInst1, TimerSetup->Interval);

		XTtcPs_SetPrescaler(&TtcPsInst1, TimerSetup->Prescaler);

	}
}

void init_interrupts(){
	SetupGpioInterruptSystem();
	SetupTimerInt();
	SetupTimerInt1();
}

