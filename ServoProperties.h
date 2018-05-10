//Servo IDs
#define MIDDLE_ID 0
#define LEFT_ID   1
#define RIGHT_ID  2
#define CLAW_ID   3

//Max Servo Speed in mS/° (for a linear movement)
#define ANIMATION_SPEED 100/9  //== 90 °/S
#define SMOOTH_ANIMATION_SPEED ANIMATION_SPEED/0.7
//To deactivate double speed for the claw, comment the following line
#define CLAW_DOUBLE_SPEED

//servoProperties IDs
#define PORT_ID 0
#define MIN_ID  1
#define MAX_ID  2
#define HOME_ID 3

//{Port, Min, Max, Home}
const uint8_t servoProperties[4][4] = {{SERVO_MIDDLE_PORT, 12, 160, 80},
                                       {SERVO_LEFT_PORT,   30,  90, 30},
                                       {SERVO_RIGHT_PORT,  45, 180, 90},
                                       {SERVO_CLAW_PORT,    0,  97, 97}};

//Config for smoothed movement
bool useSmooth = true;
#define USE_SMOOTH_NOTHING_FOUND false
#define BASE 10
#define EXPONENT 4

//Calculated constants by using the smooth constants
const int16_t DOUBLE_BASE = BASE * 2;
const float POW = pow(BASE, EXPONENT);

//Error massage if the exponent is not at least 2
#if EXPONENT < 2
#error "Exponent for smooth movement has to be at least 2"
#endif
