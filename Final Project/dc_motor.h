/*
 * dc_motor.h
 *
 * Created: 2/25/2019 11:39:16 AM
 *  Author: rust0
 */ 

#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

#define PushButton (PINA & 0x01) //pushbutton watch

//prototypes
void init_io (void);
void PWM_Fast (uint8_t dc);
//void rampUp (uint8_t start, uint8_t stop, uint16_t ms, uint8_t steps);
void init_PWM (void);
//void init_PWM_2 (void);
//void init_PWM_4 (void);
void init_INT(void);

void home (void);
void changeVertical (uint8_t destination);
void changeHorizontal (uint8_t destination);
void changeHook (uint8_t destination);
void pickUp (void);
void putDown (void);
//void calibrateHorizontal (void);

#endif /* DC_MOTOR_H_ */