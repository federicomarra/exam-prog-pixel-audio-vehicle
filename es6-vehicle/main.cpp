//
// Created by Federico Marra on 02/07/2020.
//
#include <iostream>
#include <string>
#include <cmath>
#include <memory>


class Vehicle {
public:
    virtual ~Vehicle() {}

    virtual void redirect(int &direction) = 0;

    virtual void correctAcceleration(int &acceleration) = 0;

    virtual void turn(int ang) = 0;

    virtual void accelerate(int acc) = 0;

    virtual void decelerate(int acc) = 0;

protected:
    int speed, acceleration, direction;
};


class SpeedCar : public Vehicle {
public:
    SpeedCar(int s = 0, int a = 0, int d = 90) : speed(s), acceleration(a), direction(d) {}

    virtual ~SpeedCar() {}

    void redirect(int &direction) override {
        if (direction < 0)
            direction += 360;
        if (direction > 359)
            direction -= 360;
    }

    void correctAcceleration(int &acceleration) override {
        if (acceleration > 10)
            acceleration = 10;
        if (acceleration < 0)
            acceleration = 0;
    }

    void correctSpeed(int &speed) {
        if (speed > 255)
            speed = 255;
        if (speed < 0)
            speed = 0;
    }

    void turn(int ang) override {
        if (ang >= 1 && ang <= 179)
            direction += ang;
        redirect(direction);
        if (ang >= -179 && ang <= -1)
            direction += ang;
        redirect(direction);
    }

    void accelerate(int acc) override {
        if (acc >= 1 && acc <= 10)
            acceleration += acc;
        correctAcceleration(acceleration);
        speed += std::ceil(acceleration / 2);
        correctSpeed(speed);
    }

    void decelerate(int acc) override {
        if (acc >= 1 && acc <= 10)
            acceleration -= acc;
        correctAcceleration(acceleration);
        speed -= acc / 2;
        correctSpeed(speed);
    }

private:
    int speed, acceleration, direction;
};

class SpeedBoat {   //adaptee
public:
    SpeedBoat(int s = 0, int a = 0, int d = 90) : speed(s), acceleration(a), direction(d) {}

    virtual ~SpeedBoat() {}

    void redirect(int &direction) {
        if (direction < 0)
            direction += 360;
        if (direction > 359)
            direction -= 360;
    }

    void turn(int ang) {
        if (ang >= 1 && ang <= 179)
            direction -= ang;
        redirect(direction);
        if (ang >= -179 && ang <= -1)
            direction -= ang;
        redirect(direction);
    }

    void accelerate(int acc) {
        if (acc == 0) {
            acceleration--;
            speed--;
        }
        acceleration += acc;
        speed += ceil(acceleration / 4);
    }

private:
    int speed, acceleration, direction;
};


class GameCharacter {   //client
public:
    GameCharacter(Vehicle *v) : vehicle(v) {}

    void drive(int acc, int d) {
        if (acc >= 0)
            vehicle->accelerate(acc);
        if (acc < 0)
            vehicle->decelerate(acc);
        vehicle->turn(d);
    }

    Vehicle *getVehicle() const {
        return vehicle;
    }

    void setVehicle(Vehicle *v) {
        vehicle = v;
    }

private:
    Vehicle *vehicle;
};


class Adapter : public Vehicle {
public:
    Adapter(SpeedBoat *a) : speedBoat(a) {}

    void turn(int ang) override {
        speedBoat->turn(ang);
    }

    void accelerate(int acc) override {
        speedBoat->accelerate(acc);
    }

    void decelerate(int acc) override {}

    void redirect(int &direction) override {}

    void correctAcceleration(int &acceleration) override {}

private:
    SpeedBoat *speedBoat;
};

int main() {
    std::cout << "Esercizio 6:" << std::endl << std::endl;
    std::string veh;
    std::cout << "Inserire speedCar = c, speedBoat = b:  ";
    std::cin >> veh;
    std::unique_ptr<Vehicle> vehicle;
    if (veh == "c")
        vehicle = std::unique_ptr<Vehicle>(new SpeedCar());
    if (veh == "b") {
        std::unique_ptr<SpeedBoat> boat (new SpeedBoat());
        vehicle = std::unique_ptr<Vehicle>(new Adapter(boat.get()));
    }
    auto driver = new GameCharacter(vehicle.get());
    int acc, dir;
    std::cout << "Inserire accelerazione in interi: ";
    std::cin >> acc;
    std::cout << "Inserire direzione in interi: ";
    std::cin >> dir;
    driver->drive(acc, dir);
}
