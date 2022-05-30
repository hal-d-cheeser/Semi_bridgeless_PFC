/**
  Generated main.c file from MPLAB Code Configurator

  @Company
    Microchip Technology Inc.

  @File Name
    main.c

  @Summary
    This is the generated main.c using PIC24 / dsPIC33 / PIC32MM MCUs.

  @Description
    This source file provides main entry point for system initialization and application code development.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.170.0
        Device            :  PIC24FJ64GA002
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.61
        MPLAB 	          :  MPLAB X v5.45
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
#include "mcc_generated_files/system.h"

/*
                         Main application
 */
float kp_v = 3.0;
float ki_v = 0.005844;
float kd_v = 0.04;
float error_v = 0.0;
float prev_error_v = 0.0;
float summ_error_v = 0.0;
float diff_error_v = 0.0;

float kp1_i = 64.0;
float ki1_i = 35.5;
float kd1_i = 0.05;
float error1_i = 0.0;
float prev_error1_i = 0.0;
float summ_error1_i = 0.0;
float diff_error1_i = 0.0;

float kp2_i = 24.0;
float ki2_i = 7.5;
float kd2_i = 0.05;
float error2_i = 0.0;
float prev_error2_i = 0.0;
float summ_error2_i = 0.0;
float diff_error2_i = 0.0;

float Vref = 70.0;
float Iref1 = 8.5;
float Iactual1 = 0.0;
float Iref2 = 8.5;
float Iactual2 = 0.0;
float Vactual = 0.0;
float cntrl1 = 0.0;
float cntrl2 = 0.0;

float Iref_tot = 0.0;

int vloop_cnt = 0;

int main(void)
{
    // initialize the device
    SYSTEM_Initialize();
    phase_shift(1236);
//    TMR3_Stop();
//    TMR3_Start();
    
    while (1)
    {
        // Add your application code
//        OC1RS = 1200;
//        OC1RS = 1200;
//        OC2RS = 1200;
    }

    return 1;
}
/**
 End of File
*/

