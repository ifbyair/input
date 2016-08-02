/*
Defining values for rotary encoder
*/

#define ENCODER_A   3   /* encoder pin A */
#define ENCODER_B   2   /* encoder pin B */
#define ENCODER_STEP    4   /* encoder change value per step */
#define ENCODER_EXEC    0   /* encoder button pin */

struct encoder {
    int pin_a;
    int pin_b;
    int pin_enter;
    volatile long value;
    volatile int lastEncoded;
};

