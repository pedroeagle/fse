#ifndef PID_H_
#define PID_H_

void pid_configura_constantes(double Kp_, double Ki_, double Kd_);
void set_reference_temperature(float referencia_);
float get_reference_temperature();
double pid_controle(double saida_medida);

#endif /* PID_H_ */
