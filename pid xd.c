#pragma config(Sensor, S1,     sensordeluzN,   sensorEV3_Color)
#pragma config(Sensor, S2,     sensordeluzB,   sensorEV3_Color)
#pragma config(Motor,  motorB,          MotorD,        tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorC,          MotorIz,       tmotorEV3_Large, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

int Kp = 100;
//int Kd = 70;
//int Ki = 0;
//int integral = 0;
//int lastError = 120;
int offset = 25;
int Tp = 80;
int turn = 0;

int Pleft = 0;
int Pright = 0;
int error = 0;
int value = 0;
//int derivative = 0;

int sensor2;

task main() {
 do{
  sensor2 = getColorReflected(S2);
	value = getColorReflected(S1);
	error = value - offset;
	//integral=integral+error;
	//derivative= error-lastError;
	turn = Kp*error; //+ Ki*integral + Kd*derivative;
	turn = turn/100;
	Pright = Tp - turn;
	Pleft = Tp + turn;
	setMotorSpeed(MotorD,Pright);
	setMotorSpeed(MotorIz,Pleft);
}
while(sensor2>30);
	setMotorSpeed(MotorD,0);
	setMotorSpeed(MotorIz,0);
}
