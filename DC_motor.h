/*
	Autor: Ronaldy Lima França
	Data: 09/2022

	Esta biblioteca tem por objetivo realizar o controle com maior
    precisão de motores com sensor encoder;
*/

#ifndef DC_motor_h
#define DC_motor_h

#include <Arduino.h>

class DC_motor{
  public:
    uint8_t in1, in2, en, encoderPinA, encoderPinB;
    float pp_rev = 11, rr=30, rpm, pp_rot, total_rot, total_degrees;
    void setMotorDriverPins(uint8_t in1, uint8_t in2, uint8_t en);	// Pinos da ponte H L298N responsáveis pelo motor
    void setEncoderPins(uint8_t pinA, uint8_t pinB);		// Pinos do encoder do motor
    void setPPR(uint16_t ppr);							// Pulses per revolution, por padrão é 11, mas é alterável com essa função.
    void setRR(float rr);           // Reduction ratio

    void countPulses();
    void run(byte pwm);     // Aplica o pwm no motor

    void startCounting();   // Inicia a contagem de rotações
    float getRotations();   // Retorna o número de rotações acumulado
    float getDegrees();     // Retorna os graus acumulados
    void stopCounting();    // Para a contagem de rotações
    void stop(int time=50);    // Para o motor e espera alguns millisegundos

    volatile long int pulses[2] = {0, 0}; // pulses[0] - para contagem do RPM, pulses[1]- rotação
};


#endif
