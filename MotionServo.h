//Copyed from https://www.github.com/timoxd7/MotionServo and modifyed for specific needs

//------------------------------------------------------------------------------------------

#include <Servo.h>

#define SERVO_MIN 0
#define SERVO_MAX 180

class MotionServo {
  public:
    void begin(uint8_t Pin, uint8_t Min, uint8_t Max, uint8_t Home) {
      //Check Min for Possibility
      if (Min < SERVO_MIN) Min = SERVO_MIN;
      else if (Min > SERVO_MAX) Min = SERVO_MAX;

      //Check Max for Possibility
      if (Max < SERVO_MIN) Max = SERVO_MIN;
      else if (Max > SERVO_MAX) Max = SERVO_MAX;

      //Check Home for Possibility
      if (Min < Max) {
        if (Home < Min) Home = Min;
        else if (Home > Max) Home = Max;
      } else if (Min > Max) {
        if (Home > Min) Home = Min;
        else if (Home < Max) Home = Max;
      } else Home = Min;

      _servo.min = Min;
      _servo.max = Max;
      _servo.pin = Pin;
      _servo.home = Home;

      _servo.object.attach(Pin);

      home(0, 0);
    }

    void home(unsigned long Time, unsigned long startTime = millis()) {
      moveTo(_servo.home, Time, startTime);
    }

    void moveTo(uint8_t Position, unsigned long Time, unsigned long startTime = millis()) {
      if (Time == 0) {
        setServo(Position);
        _position.destination = Position;
        _position.start = _position.current;
        _time.start = startTime;
        _time.duration = 0;
      } else {
        _position.destination = Position;
        _position.start = _position.current;
        _time.start = startTime;
        _time.duration = Time;
      }
    }

    void move(int16_t addPosition, unsigned long Time, unsigned long startTime = millis()) {
      if (Time == 0) {
        _position.destination = _position.current + addPosition;
        setServo(_position.destination);
        _position.start = _position.destination;
        _time.start = startTime;
        _time.duration = 0;
      } else {
        _position.destination = _position.current + addPosition;
        _position.start = _position.current;
        _time.start = startTime;
        _time.duration = Time;
      }
    }

    uint8_t getHome() {
      return _servo.home;
    }

    uint8_t getCurrentPosition() {
      return _position.current;
    }

    bool loop(unsigned long currentLoopTime = millis(), bool smooth = false);

  protected:
    void setServo(uint8_t Position) {
      if (Position < _servo.min) Position = _servo.min;
      if (Position > _servo.max) Position = _servo.max;

      _servo.object.write(Position);
      _position.current = Position;
    }

    struct _servo {
      uint8_t pin, min, max, home;
      Servo object;
    } _servo;

    struct _position {
      uint8_t start, current, destination;
    } _position;

    struct _time {
      unsigned long start, duration;
    } _time;
};


bool MotionServo::loop(unsigned long currentTime, bool smooth) {
  if (_position.destination == _position.current) return false;
  if (currentTime < _time.start) return true;

  int16_t movement = _position.destination - _position.start;
  unsigned long currentMovementTime = currentTime - _time.start;

  if (currentMovementTime >= _time.duration) {
    setServo(_position.destination);
    return false;
  } else {
    float timePoint = (float)currentMovementTime / (float)_time.duration;
    uint8_t moveToThisTime = _position.start;
    if (smooth) {
      movement /= 2;
      if (timePoint < 0.5) {
        moveToThisTime += movement * (pow(timePoint * DOUBLE_BASE, EXPONENT) / POW);
      } else {
        timePoint = 1 - timePoint;
        moveToThisTime += movement;
        moveToThisTime += movement * (1 - (pow(timePoint * DOUBLE_BASE, EXPONENT) / POW));
      }
    } else {
      moveToThisTime += (float)movement * timePoint;
    }
    setServo(moveToThisTime);
    return true;
  }
}

