// imports
#include <Arduino.h>
#include <AFMotor.h>

class Engine {
private:
    AF_DCMotor* m3 = (AF_DCMotor*)malloc(sizeof(AF_DCMotor)); 
    AF_DCMotor* m4 = (AF_DCMotor*)malloc(sizeof(AF_DCMotor)); 

public:
    AF_DCMotor leftMotor = this->getLeftMotor();
    AF_DCMotor rightMotor = this->getRightMotor();

    Engine(int leftPin, int rightPin);
    
    AF_DCMotor getLeftMotor();
    AF_DCMotor getRightMotor();
    void setEngineSpeed(int leftSpeed, int rightSpeed);
    void move(int leftMotion, int rightMotion);
    void stop();
    void halt(int wait);
    void moveForward(int wait, int smoothning);
    void moveLeft(int wait, int smoothning);
    void moveRight(int wait, int smoothning);
    void moveBackword(int wait, int smoothning);

    ~Engine();
};

Engine :: Engine(int leftPin = 3, int rightPin = 4) {
    *(this->m3) = AF_DCMotor(leftPin);
    *(this->m4) = AF_DCMotor(rightPin);
}
AF_DCMotor Engine :: getLeftMotor() {
    return *(this->m3);
}
AF_DCMotor Engine :: getRightMotor() {
    return *(this->m4);
}
void Engine :: setEngineSpeed(int leftSpeed = 200, int rightSpeed = 200) {
    this->getLeftMotor().setSpeed(leftSpeed);
    this->getRightMotor().setSpeed(rightSpeed);
}
void Engine :: move(int leftMotion, int rightMotion) {
    this->getLeftMotor().run(leftMotion); 
    this->getRightMotor().run(rightMotion);
}
void Engine :: stop() {
    this->move(RELEASE, RELEASE);
}
void Engine :: halt(int wait = 10) {
    this->stop();
    delay(wait);
}
void Engine :: moveForward(int wait = 100, int smoothning = 1) {
    this->move(FORWARD, FORWARD);
    delay(wait);
    this->stop();
    delay(smoothning);
}
void Engine :: moveLeft(int wait = 100, int smoothning = 1) {
    this->move(BACKWARD, FORWARD);
    delay(wait);
    this->stop();
    delay(smoothning);
}
void Engine :: moveRight(int wait = 100, int smoothning = 1) {
    this->move(FORWARD, BACKWARD);
    delay(wait);
    this->stop();
    delay(smoothning);
}
void Engine :: moveBackword(int wait = 100, int smoothning = 1) {
    this->move(BACKWARD, BACKWARD);
    delay(wait);
    this->stop();
    delay(smoothning);
}
Engine :: ~Engine () {
    delete this->m3;
    delete this->m4;
}

// SETUP
void setup() {
    Engine engine(3, 4);
    engine.setEngineSpeed(200, 200);
    engine.stop();
}

// LOOP
void loop() {

}