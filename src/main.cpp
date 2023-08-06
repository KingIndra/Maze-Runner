// imports
#include <Arduino.h>
#include <AFMotor.h>
#include <string>

// alias
int DR(int input) {
    return digitalRead(input);
}

class Engine {
private:
    AF_DCMotor* m3 = (AF_DCMotor*)malloc(sizeof(AF_DCMotor)); 
    AF_DCMotor* m4 = (AF_DCMotor*)malloc(sizeof(AF_DCMotor)); 

public:
    AF_DCMotor leftMotor = *m3;
    AF_DCMotor rightMotor = *m4;

    Engine(int leftPin, int rightPin);
    
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
    this->leftMotor = *(this->m3);
    this->rightMotor = *(this->m4);
}

void Engine :: setEngineSpeed(int leftSpeed = 200, int rightSpeed = 200) {
    this->leftMotor.setSpeed(leftSpeed);
    this->rightMotor.setSpeed(rightSpeed);
}

void Engine :: move(int leftMotion, int rightMotion) {
    this->leftMotor.run(leftMotion); 
    this->rightMotor.run(rightMotion);
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

// Sensor Class
//        d
//  a  b     e  f
//        c
class Sensor {
public:
    int a, b, c, d, e, f, firstPin, lastPin;
    Sensor(int firstPin, int lastPin);
    bool straight();
    bool end();
    bool front_T();
    bool u_turn();
    bool cross_T();
    bool left_turn();
    bool right_turn();
    bool right_T();
    bool left_T();
    void showReadings();
};
Sensor :: Sensor(int firstPin, int lastPin) {
    this->firstPin = firstPin;
    this->lastPin = lastPin;
    for(int i = firstPin; i <= lastPin; i++) {
        pinMode(i, INPUT);
    }
    this->a = firstPin + 0;
    this->b = firstPin + 1;
    this->c = firstPin + 2;
    this->d = firstPin + 3;
    this->e = firstPin + 4;
    this->f = firstPin + 5;
}
bool Sensor :: straight() {
    if (
        !DR(this->a) && !DR(this->b) && DR(this->c) &&
        DR(this->d) && !DR(this->e) && !DR(this->f) 
    ) return true;
    else return false;
}
bool Sensor :: end() {
    if (
        DR(this->a) && !DR(this->b) && !DR(this->c) &&
        !DR(this->d) && !DR(this->e) && DR(this->f) 
    ) return true;
    else return false;
}
bool Sensor :: front_T() {
    if (
        DR(this->a) && DR(this->b) && DR(this->c) &&
        !DR(this->d) && DR(this->e) && DR(this->f) 
    ) return true;
    else return false;
}
bool Sensor :: u_turn() {
    if (
        !DR(this->a) && !DR(this->b) && !DR(this->c) &&
        !DR(this->d) && !DR(this->e) && !DR(this->f) 
    ) return true;
    else return false;
}
bool Sensor :: cross_T() {
    if (
        DR(this->a) && DR(this->b) && DR(this->c) &&
        DR(this->d) && DR(this->e) && DR(this->f) 
    ) return true;
    else return false;
}
bool Sensor :: left_turn() {
    if (
        DR(this->a) && DR(this->b) && !DR(this->c) &&
        DR(this->d) && !DR(this->e) && !DR(this->f) 
    ) return true;
    else return false;
}
bool Sensor :: right_turn() {
    if (
        !DR(this->a) && !DR(this->b) && DR(this->c) &&
        DR(this->d) && DR(this->e) && DR(this->f) 
    ) return true;
    else return false;
}
bool Sensor :: right_T() {
    if (
        !DR(this->a) && !DR(this->b) && DR(this->c) &&
        DR(this->d) && DR(this->e) && DR(this->f)
    ) return true;
    else return false;
}
bool Sensor :: left_T() {
    if (
        DR(this->a) && DR(this->b) && DR(this->c) &&
        DR(this->d) && !DR(this->e) && !DR(this->f) 
    ) return true;
    else return false;
}
void Sensor :: showReadings() {
    for(int i = this->firstPin; i <= this->lastPin; i++) {
        Serial.print("Pin i = ");
        Serial.println(DR(i));
    }
}

class Robot {
private:
    Sensor* sensor_pointer = (Sensor*)malloc(sizeof(sensor));
    Engine* engine_pointer = (Engine*)malloc(sizeof(sensor));

public:
    Sensor sensor = *(this->sensor_pointer);
    Engine engine = *(this->engine_pointer);
    String path = "", prevPath = "X";

    Robot(int sensorPins[], int motorPins[]);
    void update();
    String optimizedPath();
    ~Robot();
};

Robot :: Robot(int sensorPins[], int motorPins[]) {
    int firstSensorPin = sensorPins[0], lastSensorPin = sensorPins[1];
    *(this->sensor_pointer) = Sensor(firstSensorPin, lastSensorPin);

    int leftMotorPin = motorPins[0], rightMotorPin = motorPins[1];
    *(this->engine_pointer) = Engine(leftMotorPin, rightMotorPin);

    this->sensor = *(this->sensor_pointer);
    this->engine = *(this->engine_pointer);
}
void Robot :: update() {
    String currPath = "";
    if(this->sensor.end()) {
        this->engine.stop();
        currPath = "F";
    }
    else if(this->sensor.front_T()) {
        this->engine.moveLeft();
        currPath = "S";
    }
    else if(this->sensor.u_turn()) {
        this->engine.moveBackword();
        currPath = "B";
    }
    else if(this->sensor.cross_T()) {
        this->engine.moveLeft();
        currPath = "L";
    }
    else if(this->sensor.left_turn()) {
        this->engine.moveLeft();
        currPath = "L";
    }
    else if(this->sensor.right_turn()) {
        this->engine.moveRight();
        currPath = "R";
    }
    else if(this->sensor.left_T()) {
        this->engine.moveLeft();
        currPath = "L";
    }
    else if(this->sensor.right_T()) {
        this->engine.moveForward();
        currPath = "S";
    }
    if(currPath != this->prevPath) {
        this->path += currPath;
        this->prevPath = currPath;
    }
}
String Robot :: optimizedPath() {
    this->path.replace("LBL", "S");
    this->path.replace("LBS", "R");
    this->path.replace("RBL", "B");
    this->path.replace("SBS", "B");
    this->path.replace("SBL", "R");
    this->path.replace("LBR", "B");
    return this->path;
}
Robot :: ~Robot() {
    delete this->sensor_pointer;
    delete this->engine_pointer;
}

// SETUP
int sensorPins[2] = {14, 19};
int motorPins[2] = {3, 4}; 
Robot robot(sensorPins, motorPins);

void setup() {
    Serial.begin(9600);
    robot.engine.setEngineSpeed(200, 200);
    robot.engine.stop(); 
}

void loop() {
    robot.update();
}