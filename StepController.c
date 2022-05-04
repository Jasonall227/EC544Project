

/**
 * 17   27  22  selection
 * 0    0   1   M1
 * 0    1   0   M2
 * 0    1   1   M3
 * 1    0   0   M4
 * 1    0   1   M5
 * 1    1   0   M6
 *
 * 5    6   operation
 * x    0   NOP
 * val  1   set position to val
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wiringPi.h>
#include <softPwm.h>

#define P1 17
#define P2 27
#define P3 22
#define P4 5
#define P5 6

void init();
int selectMotor(int motor);
int operate(int pos);
int handleInput(char* input);



/* init wiringPi */
void init() {
    wiringPiSetupGpio();

    // init motor selection pins
    pinMode(P1, OUTPUT);
    pinMode(P2, OUTPUT);
    pinMode(P3, OUTPUT);

    // init operation pins
    // softPwmCreate(P4, 50, 100);
    pinMode(P4, OUTPUT);
    pinMode(P5, OUTPUT);
}

/* select motor */
int selectMotor(int motor) {
    switch (motor) {
        case 1:
            printf("select motor 1\n");
            digitalWrite(P1, LOW);
            digitalWrite(P2, LOW);
            digitalWrite(P3, HIGH);
            break;
        case 2:
            printf("select motor 2\n");
            digitalWrite(P1, LOW);
            digitalWrite(P2, HIGH);
            digitalWrite(P3, LOW);
            break;
        case 3:
            printf("select motor 3\n");
            digitalWrite(P1, LOW);
            digitalWrite(P2, HIGH);
            digitalWrite(P3, HIGH);
            break;
        case 4:
            printf("select motor 4\n");
            digitalWrite(P1, HIGH);
            digitalWrite(P2, LOW);
            digitalWrite(P3, LOW);
            break;
        case 5:
            printf("select motor 5\n");
            digitalWrite(P1, HIGH);
            digitalWrite(P2, LOW);
            digitalWrite(P3, HIGH);
            break;
        case 6:
            printf("select motor 6\n");
            digitalWrite(P1, HIGH);
            digitalWrite(P2, HIGH);
            digitalWrite(P3, LOW);
            break;
        default:
            perror("invalid motor number\n");
            return -1;
    }

    return 0;
}
/*
int operate(int pos) {
    printf("set position to %d\n", pos);
    // softPwmWrite(P4, pos);

    // activate
    digitalWrite(P5, HIGH);
    // digitalWrite(P5, LOW);

    return 0;
}
*/
void operate(int dir){
    if (dir == 1)  {
        digitalWrite(P4, HIGH);   // direction set, rotate CW
        printf("direction = clockwise\n");
    }
    else if (dir == 0)  {
        digitalWrite(P4, LOW);
        printf("direction = counterclockwise\n");
    }
    else printf("invalid direction\n");
    digitalWrite(P5, HIGH);
}


void rest() {
    digitalWrite(P5, LOW);
}

int handleInput(char* input) {
    int motor;
    char* temp;
    int pos;

    motor = input[3] - '0';
    if (motor < 1 || motor > 6) {
        perror("motor number\n");
        return -1;
    }

    temp = strtok(input, "-");
    pos = atoi(temp);
    if (pos < 0 || pos > 100) {
        perror("position\n");
        return -1;
    }

    selectMotor(motor);
    operate(pos);

    return 0;
}