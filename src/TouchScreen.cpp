/*
 * TouchScreen.cpp
 *
 *  Created on: 02 mar 2017
 *      Author: paolo
 */

#include <memory>
#include "TouchScreen.h"

TouchScreen::TouchScreen(uint16_t width, uint16_t height) : width(width), height(height){
    left = 0;
    right = 4096;
    top = 0;
    bottom = 4096;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_GPIOA, ENABLE);
    ADC_InitTypeDef ADC_InitStructure;

    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
    //We will convert multiple channels
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;
    //select continuous conversion mode
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE; //!
    //select no external triggering
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    //right 12-bit data alignment in ADC data register
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    //8 channels conversion
    ADC_InitStructure.ADC_NbrOfChannel = 1;
    //load structure values to control and status registers
    ADC_Init(ADC1, &ADC_InitStructure);

    ADC_Cmd(ADC1, ENABLE);
    ADC_ResetCalibration(ADC1);
    //Check the end of ADC1 reset calibration register
    while (ADC_GetResetCalibrationStatus(ADC1))
        ;
    //Start ADC1 calibration
    ADC_StartCalibration(ADC1);
    //Check the end of ADC1 calibration
    while (ADC_GetCalibrationStatus(ADC1))
        ;

}

Point TouchScreen::getPoint() {
    Point point(std::move(getRaw()));
    point.x = ((uint32_t)width*(point.x - left))/(right-left);
    point.y = ((uint32_t)height*(point.y - top))/(bottom-top);
    return point;
}


Point TouchScreen::getRaw() {
    Point point;

    CS_PORT->BSRR = CS_PIN;
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_InitStructure.GPIO_Pin = YP_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(YP_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = YM_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(YM_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = XP_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(XP_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = XM_PIN;
    GPIO_Init(XM_PORT, &GPIO_InitStructure);

    XP_PORT->BSRR = XP_PIN;
    XM_PORT->BRR = XM_PIN;
    ADC_RegularChannelConfig(ADC1, YP_ADC_PORT, 1, ADC_SampleTime_41Cycles5);

    uint16_t sample = 0;
    sample += ADC_GetConversionValue(ADC1);
    sample += ADC_GetConversionValue(ADC1);
    point.x = sample/2;

    GPIO_InitStructure.GPIO_Pin = YP_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(YP_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = YM_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(YM_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = XP_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(XP_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = XM_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(XM_PORT, &GPIO_InitStructure);

    YP_PORT->BSRR = XP_PIN;
    YM_PORT->BRR = XM_PIN;
    ADC_RegularChannelConfig(ADC1, XM_ADC_PORT, 1, ADC_SampleTime_41Cycles5);

    sample = 0;
    sample += ADC_GetConversionValue(ADC1);
    sample += ADC_GetConversionValue(ADC1);
    point.y = sample/2;

    return point;
}
