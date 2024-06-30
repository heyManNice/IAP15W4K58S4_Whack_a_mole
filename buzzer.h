#ifndef BUZZER_H
#define BUZZER_H
#include "framework.h"

#define TONE_1KHZ 11059

void Buzzer_Init();
void Buzzer_Beep();
void Buzzer_noBeep();
void Buzzer_Tone(long int tone);

//音符周期(us) = 1khz周期*1000/音符频率
#define DO      21145
#define DO_S    19962
#define RE      18840
#define RE_S    17780
#define MI      16781
#define FA      15844
#define FA_S    14945
#define SO      14106
#define SO_S    13308
#define LA      12567
#define LA_S    11866
#define SI      11193

#endif