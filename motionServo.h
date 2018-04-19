#include <Servo.h>

class motionServo {
  public:
    void begin(uint8_t Pin, uint8_t Min, uint8_t Max, uint8_t Home) {
      _servo.pin = Pin;
      _servo.min = Min;
      _servo.max = Max;
      _servo.home = Home;

      _servo.object.attach(Pin);

      home(0);
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

    bool loop();

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


bool motionServo::loop() {
  if (_position.destination == _position.current) return false;
  if (millis() < _time.start) return true;

  int16_t movement = _position.destination - _position.start;
  unsigned long currentTime = millis() - _time.start;

  if (currentTime >= _time.duration) {
    setServo(_position.destination);
    return false;
  } else {
    uint8_t moveToThisTime = _position.start + (movement * (currentTime / _time.duration));
    setServo(moveToThisTime);
    return true;
  }
}

