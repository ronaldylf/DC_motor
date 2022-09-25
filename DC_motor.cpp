/*
	Autor: Ronaldy Lima França
	Data: 09/2022

	Esta biblioteca tem por objetivo realizar o controle com maior
    precisão de motores com sensor encoder;
*/


#include <DC_motor.h>

void DC_motor::setMotorDriverPins(uint8_t in1, uint8_t in2, uint8_t en) {
    this-> in1 = in1; pinMode(in1, OUTPUT);
    this-> in2 = in2; pinMode(in2, OUTPUT);
    this-> en  =  en; pinMode(en, OUTPUT);
}

void DC_motor::countPulses() {
    if(digitalRead(encoderPinB)){ // Sentido horário
        pulses[0]++;
        pulses[1]++;
    } else {  // Sentido anti-horário
        pulses[0]--;
        pulses[1]--;
    }
}

void DC_motor::setEncoderPins(uint8_t pinA, uint8_t pinB) {
    this->encoderPinA = pinA; pinMode(encoderPinA, INPUT);
    this->encoderPinB = pinB; pinMode(encoderPinB, INPUT);
}

void DC_motor::setPPR(uint16_t ppr) {
    this->pp_rev = ppr;
    this->pp_rot = this->pp_rev * this->rr;
}

void DC_motor::setRR(float rr) {
    this->rr = rr;
    this->pp_rot = this->pp_rev * this->rr;
}

void DC_motor::startCounting();   // Inicia a contagem de rotações
    float getRotations();   // Retorna o número de rotações acumulado
    float getDegrees();     // Retorna os graus acumulados
    void stopCounting();    // Para a contagem de rotações

void DC_motor::startCounting() {
    pulses[1] = 0;
    total_rot = 0;
}

float DC_motor::getRotations() {
    total_rot = (1.0 / pp_rot) * pulses[1];
    return total_rot;
}

float DC_motor::getDegrees() {
    total_degrees = (360 * getRotations());
    return total_degrees;
}

void DC_motor::stopCounting() {
    startCounting();
}

void DC_motor::run(byte pwm) {
    if (pwm>0) {
        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);
    } else if (pwm<0) {
        digitalWrite(in1, LOW);
        digitalWrite(in2, HIGH);
    } else {
        digitalWrite(in1, LOW);
        digitalWrite(in2, LOW);
    }

    analogWrite(en, pwm);
}

void DC_motor::stop(int time=50) {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    analogWrite(en, LOW);
}