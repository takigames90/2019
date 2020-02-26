int BR = 0;// variable que se utiliza para darle valor a las variables de color
int A = 0;//azul
int V = 0;//verde
int AM = 0; //amarillo
int R = 0;//rojo
int V1 = 0;
int V2 = 0;

void avanza(){
	setMotorSync(motorB,motorC,90,75);
	delay(100);
}
void leer(){ // no tengo calculado los grados pero avanza al primer recuadro del codigo binario
	setMotorSync(motorB,motorC,90,75);
	V1 = getColorReflected(S1);
	setMotorSync(motorB,motorC,90,75);
	V2 = getColorReflected(S1);
}
void restablecer(){//estoy checando bien como hacer para que si le digo A es igual a 1 pero BR camia a 2 no cambie con BR
	A = A;
	V = V;
	AM= AM;
	R = R;
}
task Dvariable() // va a designar el valor a la variable BR
	{
	while(true){
		if(A == 0){ // mientras A no tenga valor
			A = BR;//A va a ser igual valor de BR
			stopTask(Dvariable);//dejara de realizar la tarea/indicar el valor de las variables
		}
		else if(A > 0 && V == 0){
			V = BR;
			stopTask(Dvariable);
		}
		else if(V > 0 && AM == 0){
			AM = BR;
			stopTask(Dvariable);
		}
		else if(AM > 0 && R == 0){
			R = BR;
			stopTask(Dvariable);
		}
		else{//evita que se confundan los datos de las variables
			A = A;
			V = V;
			AM = AM;
			R = R;
		}
	}
}
task Avalor()// va a asignar el valor a las variables de los colores utilisando las variables v1 y v2
{
	if(V1 == 0 && V2 == 0){
		BR =  1; //1 es para indicar el recoger la nieve
}
	else if(V1 == 1 && V2 == 0){
		BR = 2; //2 es para indicar que se esparce el material abrasivo negro
	}
	else if (V1 == 0 && V2 == 1){
		BR = 3; //3 es para indicar que se esparce el material abrasivo azul
	}
}

task main()
{

	if(getColorName(S1) == colorRed || getColorName(S1) == colorYellow){ //si ve rojo o amarillo para
		V1 = +1;
		delay(2000);
	}
	while(V1 == 0){ //mientras no vea rojo o amarillo avanza
		avanza();
	}
	while(V1 == 1){//empieza a leer el codigo binario
		leer();
		startTask(Dvariable);
		startTask(Avalor);
		restablecer();
		delay(100);
	}
}
