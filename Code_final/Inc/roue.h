#ifndef INC_ROUES_H_
#define INC_ROUES_H_

void setup_roue_PWM(void);
void roue_stop(void);
void roue_marche(int direction, int roue_droite);

int decode_inclinaison(int channel, int repos);
void controle_roues_sbus(void);

#endif

