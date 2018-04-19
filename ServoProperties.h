//Servo port definitions
#define SERVO_MIDDLE_PORT 7
#define SERVO_CLAW_PORT 8
#define SERVO_RIGHT_PORT 9
#define SERVO_LEFT_PORT 10

//Servo IDs
#define MIDDLE_ID 0
#define LEFT_ID   1
#define RIGHT_ID  2
#define CLAW_ID   3

//Servo counter
#define SERVO_COUNT 4

//Max Servo Speed in mS/°
#define MAX_SPEED 100/9  //== 90 °/S

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
