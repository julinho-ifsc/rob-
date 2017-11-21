#ifndef EngineControl_h
#define EngineControl_h

#include <Arduino.h>

#define BASE_VELOCITY 75
#define TINY_FACTOR 0.4
#define SMALL_FACTOR 0.7
#define MEDIUM_FACTOR 0.9
#define NORMAL_FACTOR 1.0

struct EnginePins {
    int velocity;
    int rotation1;
    int rotation2;
};

class EngineControl {
private:
    EnginePins frontLeftPins;
    EnginePins frontRightPins;
    EnginePins backLeftPins;
    EnginePins backRightPins;
    void frontLeftEngine();
    void frontRightEngine();
    void backLeftEngine();
    void backRightEngine();
public:
    void setFrontLeftPins (EnginePins);
    void setFrontRightPins (EnginePins);
    void setBackLeftPins (EnginePins);
    void setBackRightPins (EnginePins);
    void stop ();
    void forward ();
    void turnLeft (float factor);
    void turnRight (float factor);
};

#endif
