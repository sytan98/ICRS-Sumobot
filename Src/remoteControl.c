//
// Created by jqp on 1/30/20.
//

#include "remoteControl.h"

uint32_t CH3_Val1 = 0;
uint32_t CH3_Val2 = 0;
uint32_t CH3_Difference = 0;
uint8_t CH3_Is_First_Captured = 0; //is the first value captured?

uint32_t CH2_Val1 = 0;
uint32_t CH2_Val2 = 0;
uint32_t CH2_Difference = 0;
uint8_t CH2_Is_First_Captured = 0; //is the first value captured?

uint32_t CH1_Val1 = 0;
uint32_t CH1_Val2 = 0;
uint32_t CH1_Difference = 0;
uint8_t CH1_Is_First_Captured = 0; //is the first value captured?

void remoteControl_init() {
    //Reads for CH1 on rc receiver (right toggle)
    HAL_TIM_IC_Start_IT(&htim2,TIM_CHANNEL_1);
    //Reads for CH5 on rc receiver (right knob)
    HAL_TIM_IC_Start_IT(&htim15,TIM_CHANNEL_2);
    //Reads for CH3 on rc receiver (left toggle)
    HAL_TIM_IC_Start_IT(&htim3,TIM_CHANNEL_4);
}

uint32_t get_RIGHT_KNOB() {
    return CH2_Difference;
}

uint32_t get_LEFT_TOGGLE() {
    return CH3_Difference;
}
uint32_t get_RIGHT_TOGGLE() {
    return CH1_Difference;
}

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim) {
    //Handles right toggle
    if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1) {
        if (CH1_Is_First_Captured == 0) {
            CH1_Val1 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);
            CH1_Is_First_Captured = 1;
            __HAL_TIM_SET_CAPTUREPOLARITY(htim, TIM_CHANNEL_1, TIM_INPUTCHANNELPOLARITY_FALLING);

        } else if (CH1_Is_First_Captured == 1) {
            CH1_Val2 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);
            __HAL_TIM_SET_COUNTER(htim, 0);
            if (CH1_Val2 > CH1_Val1) {
                CH1_Difference = CH1_Val2 - CH1_Val1;
            }
            CH1_Is_First_Captured = 0;
            __HAL_TIM_SET_CAPTUREPOLARITY(htim, TIM_CHANNEL_1, TIM_INPUTCHANNELPOLARITY_RISING);

        }

    }
    //Handles right knob
    if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2) {
        if (CH2_Is_First_Captured == 0) {
            CH2_Val1 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_2);
            CH2_Is_First_Captured = 1;
            __HAL_TIM_SET_CAPTUREPOLARITY(htim, TIM_CHANNEL_2, TIM_INPUTCHANNELPOLARITY_FALLING);

        } else if (CH2_Is_First_Captured == 1) {
            CH2_Val2 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_2);
            __HAL_TIM_SET_COUNTER(htim, 0);
            if (CH2_Val2 > CH2_Val1) {
                CH2_Difference = CH2_Val2 - CH2_Val1;
            }
            CH2_Is_First_Captured = 0;
            __HAL_TIM_SET_CAPTUREPOLARITY(htim, TIM_CHANNEL_2, TIM_INPUTCHANNELPOLARITY_RISING);
        }
    }
    //Handles left toggle
    if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_4) {
        if (CH3_Is_First_Captured == 0) {
            CH3_Val1 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_4);
            CH3_Is_First_Captured = 1;
            __HAL_TIM_SET_CAPTUREPOLARITY(htim, TIM_CHANNEL_4, TIM_INPUTCHANNELPOLARITY_FALLING);

        } else if (CH3_Is_First_Captured == 1) {
            CH3_Val2 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_4);
            __HAL_TIM_SET_COUNTER(htim, 0);
            if (CH3_Val2 > CH3_Val1) {
                CH3_Difference = CH3_Val2 - CH3_Val1;

            }
            CH3_Is_First_Captured = 0;
            __HAL_TIM_SET_CAPTUREPOLARITY(htim, TIM_CHANNEL_4, TIM_INPUTCHANNELPOLARITY_RISING);

        }

    }
}

// If we don't receive any signal from right toggle, do something
void HAL_TIM_PeriodElapsedHalfCpltCallback(TIM_HandleTypeDef *htim) {
    if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1) {
        printf("right toggle timeout!!");
    }
}