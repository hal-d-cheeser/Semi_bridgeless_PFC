
/**
  TMR1 Generated Driver API Source File 

  @Company
    Microchip Technology Inc.

  @File Name
    tmr1.c

  @Summary
    This is the generated source file for the TMR1 driver using PIC24 / dsPIC33 / PIC32MM MCUs

  @Description
    This source file provides APIs for driver for TMR1. 
    Generation Information : 
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.170.0
        Device            :  PIC24FJ64GA002
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.61
        MPLAB             :  MPLAB X v5.45
*/

/*
    (c) 2020 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

/**
  Section: Included Files
*/

#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include "mcc.h"
#include "tmr1.h"

/**
 Section: File specific functions
*/
void (*TMR1_InterruptHandler)(void) = NULL;
void TMR1_CallBack(void);

/**
  Section: Data Type Definitions
*/

/** TMR Driver Hardware Instance Object

  @Summary
    Defines the object required for the maintenance of the hardware instance.

  @Description
    This defines the object required for the maintenance of the hardware
    instance. This object exists once per hardware instance of the peripheral.

  Remarks:
    None.
*/

typedef struct _TMR_OBJ_STRUCT
{
    /* Timer Elapsed */
    volatile bool           timerElapsed;
    /*Software Counter value*/
    volatile uint8_t        count;

} TMR_OBJ;

static TMR_OBJ tmr1_obj;

/**
  Section: Driver Interface
*/

void TMR1_Initialize (void)
{
    //TMR1 0; 
    TMR1 = 0x00;
    //Period = 0.00003 s; Frequency = 250000000 Hz; PR1 7499; 
    PR1 = 0x1D4B;
    //TCKPS 1:1; TON enabled; TSIDL disabled; TCS FOSC/2; TSYNC disabled; TGATE disabled; 
    T1CON = 0x8000;

    if(TMR1_InterruptHandler == NULL)
    {
        TMR1_SetInterruptHandler(&TMR1_CallBack);
    }

    IFS0bits.T1IF = false;
    IEC0bits.T1IE = true;
//    IEC0bits.T1IE = false;
	
    tmr1_obj.timerElapsed = false;

}


void __attribute__ ( ( interrupt, no_auto_psv ) ) _T1Interrupt (  )
{
    extern float kp_v;
    extern float ki_v;
    extern float kd_v;
    extern float error_v;
    extern float prev_error_v;
    extern float summ_error_v;
    extern float diff_error_v;
    
    extern float kp1_i;
    extern float ki1_i;
    extern float kd1_i;
    extern float error1_i;
    extern float prev_error1_i;
    extern float summ_error1_i;
    extern float diff_error1_i;

    extern float kp2_i;
    extern float ki2_i;
    extern float kd2_i;
    extern float error2_i;
    extern float prev_error2_i;
    extern float summ_error2_i;
    extern float diff_error2_i;
   
    extern float Vref;
    extern float Iref1;
    extern float Iactual1;
    extern float Iref2;
    extern float Iactual2;
    extern float Vactual;
    extern float cntrl1;
    extern float cntrl2;
    
    extern float Iref_tot;
    
    extern int vloop_cnt;
    /* Check if the Timer Interrupt/Status is set */

    //***User Area Begin
    //Sensor stuff
//    Vactual = ((float)ADC1BUF0/1023.0)*5.0;
//    Vactual = (2.5 - Vactual)*150.0;
    Vactual = fabs(375 - 0.7331378299*(float)ADC1BUF0);
//    Iactual = ((float)ADC1BUF1/1023.0)*5.0;
//    Iactual = (2.5 - Iactual)/0.1;
    Iactual1 = fabs(37.87878788 - 0.07405432625*(float)ADC1BUF1);
    Iactual2 = 25 - 0.04887585532*(float)ADC1BUF2;
    //Sensor stuff ends
    
//    printf("%.1f    %.1f \r", Vactual, Iactual);
    
//    error_v = Vref - Vactual;
//    diff_error_v = error_v - prev_error_v;
//    summ_error_v += error_v;
//    prev_error_v = error_v;
//    
//    cntrl = kp_v*error_v + kd_v*diff_error_v + ki_v*summ_error_v;
    
    
    
//    Iref1 = Iref_tot/2.0;
    Iref1 = Vactual*0.1*0.45;
    
//    Iref2 = Iref_tot/2.0;
    
    error1_i = Iref1 - Iactual1;
    diff_error1_i = error1_i - prev_error1_i;
    summ_error1_i += error1_i;
    prev_error1_i = error1_i;
    
//    error2_i = Iref2 - Iactual2;
//    diff_error2_i = error2_i - prev_error2_i;
//    summ_error2_i += error2_i;
//    prev_error2_i = error2_i;
    
    cntrl1 = kp1_i*error1_i + kd1_i*diff_error1_i + ki1_i*summ_error1_i;
    
//    cntrl2 = kp2_i*error2_i + kd2_i*diff_error2_i + ki2_i*summ_error2_i;
    
    
    if(cntrl1 >= 2000.0){
        cntrl1 = 2000.0;
    }
    else if(cntrl1 <= 0.0){
        cntrl1 = 0.0;
    }
    else{
        cntrl1 = cntrl1;
    }
    
    OC1RS = (int)cntrl1;
    
    
    
//    if(cntrl2 >= 2000.0){
//        cntrl2 = 2000.0;
//    }
//    else if(cntrl2 <= 0.0){
//        cntrl2 = 0.0;
//    }
//    else{
//        cntrl2 = cntrl2;
//    }
    
    OC2RS = OC1RS;
    
    
    vloop_cnt++;
    vloop_cnt = 0;
    if(vloop_cnt == 20){
        vloop_cnt = 0;
        error_v = Vref - Vactual;
        diff_error_v = error_v - prev_error_v;
        summ_error_v += error_v;
        prev_error_v = error_v;
    
        Iref_tot = kp_v*error_v + kd_v*diff_error_v + ki_v*summ_error_v;
        
        if(Iref_tot >= 40.5){
            Iref_tot = 40.5;
        }
        else if(Iref_tot <= 0.0){
            Iref_tot = 0.0;
        }
        else{
            Iref_tot = Iref_tot;
        }
        
    }
    
//    printf("%.1f %.1f %.1f %d %d \r", Vactual, Iactual1, Iref1, OC1RS, OC2RS);
//    printf("%.1f \r", Iactual1);
    // ticker function call;
    // ticker is 1 -> Callback function gets called everytime this ISR executes
    if(TMR1_InterruptHandler) 
    { 
           TMR1_InterruptHandler(); 
    }

    //***User Area End

    tmr1_obj.count++;
    tmr1_obj.timerElapsed = true;
    IFS0bits.T1IF = false;
}

void TMR1_Period16BitSet( uint16_t value )
{
    /* Update the counter values */
    PR1 = value;
    /* Reset the status information */
    tmr1_obj.timerElapsed = false;
}

uint16_t TMR1_Period16BitGet( void )
{
    return( PR1 );
}

void TMR1_Counter16BitSet ( uint16_t value )
{
    /* Update the counter values */
    TMR1 = value;
    /* Reset the status information */
    tmr1_obj.timerElapsed = false;
}

uint16_t TMR1_Counter16BitGet( void )
{
    return( TMR1 );
}


void __attribute__ ((weak)) TMR1_CallBack(void)
{
    // Add your custom callback code here
}

void  TMR1_SetInterruptHandler(void (* InterruptHandler)(void))
{ 
    IEC0bits.T1IE = false;
    TMR1_InterruptHandler = InterruptHandler; 
    IEC0bits.T1IE = true;
}

void TMR1_Start( void )
{
    /* Reset the status information */
    tmr1_obj.timerElapsed = false;

    /*Enable the interrupt*/
    IEC0bits.T1IE = true;

    /* Start the Timer */
    T1CONbits.TON = 1;
}

void TMR1_Stop( void )
{
    /* Stop the Timer */
    T1CONbits.TON = false;

    /*Disable the interrupt*/
    IEC0bits.T1IE = false;
}

bool TMR1_GetElapsedThenClear(void)
{
    bool status;
    
    status = tmr1_obj.timerElapsed;

    if(status == true)
    {
        tmr1_obj.timerElapsed = false;
    }
    return status;
}

int TMR1_SoftwareCounterGet(void)
{
    return tmr1_obj.count;
}

void TMR1_SoftwareCounterClear(void)
{
    tmr1_obj.count = 0; 
}

/**
 End of File
*/
