const int P_1 = PF_4;
const int P_2 = PF_0;

const byte L_R = PF_1;
const byte L_G = PF_3;
const byte L_B = PF_2;

int start = 0; //Bandera indicadora para que el juego comience 
int J1 = 0; // Variable contador para el jugador 1
int J2 = 0; // Variable contador para el jugador 2

//leds para el jugador 1
const int L1J1 = PD_0;
const int L2J1 = PD_1;
const int L3J1 = PD_2;
const int L4J1 = PD_3;
const int L5J1 = PE_1;
const int L6J1 = PE_2;
const int L7J1 = PE_3;
const int L8J1 = PA_7;

//leds para el jugador 2
const int L1J2 = PB_3;
const int L2J2 = PC_4;
const int L3J2 = PC_5;
const int L4J2 = PC_6;
const int L5J2 = PC_7;
const int L6J2 = PD_6;
const int L7J2 = PD_7;
const int L8J2 = PA_2;

volatile int state = LOW;

void setup() {
 pinMode(L1J1, OUTPUT);
 pinMode(L2J1, OUTPUT);
 pinMode(L3J1, OUTPUT);
 pinMode(L4J1, OUTPUT);
 pinMode(L5J1, OUTPUT);
 pinMode(L6J1, OUTPUT);
 pinMode(L7J1, OUTPUT);
 pinMode(L8J1, OUTPUT);// Se ponen los leds del jugador 1 como salida.

 pinMode(L1J2, OUTPUT);
 pinMode(L2J2, OUTPUT);
 pinMode(L3J2, OUTPUT);
 pinMode(L4J2, OUTPUT);
 pinMode(L5J2, OUTPUT);
 pinMode(L6J2, OUTPUT);
 pinMode(L7J2, OUTPUT);
 pinMode(L8J2, OUTPUT);// Se ponen los leds del jugador 2 como salida.

 pinMode(L_R, OUTPUT);
 pinMode(L_B, OUTPUT);
 pinMode(L_G, OUTPUT);// Se ponen los pines del led RGB como salidas.

 pinMode(P_1, INPUT_PULLUP);
 pinMode(P_2, INPUT_PULLUP);// Se ponen los botones como pull-up.
 attachInterrupt(digitalPinToInterrupt(P_1), JUGADOR1, RISING);
 attachInterrupt(digitalPinToInterrupt(P_2), JUGADOR2, RISING);// interrupciones de los botones de los dos jugadores.
}

void loop() {
  if ((digitalRead(P_1) == 0 || digitalRead(P_2) == 0) && start == 0){
    digitalWrite(L_R, HIGH);
    digitalWrite(L_G, LOW);// se prende la led roja.
    delay(1000);
    digitalWrite(L_R, HIGH);
    digitalWrite(L_G, HIGH);// se prende la led roja.
    delay(1000);
    digitalWrite(L_R, LOW);
    digitalWrite(L_G, HIGH);// se prende la led roja.
    delay(1000);
    digitalWrite(L_R, LOW);
    digitalWrite(L_G, LOW);// se prende la led roja.
    start = 1; //Se enciende la bandera para el inicio de la carrera.
  }
}

//Funcion de interrupcion para el primer jugador
void JUGADOR1(){
  if (start == 1)
  {
    delay(600);
    J1 = J1 + 1;// Se aumenta el contador del jugador 1 para dar los diferentes casos.
      switch (J1) 
    {
      case 1:
        //do something when var equals 1
        digitalWrite(L1J1, HIGH);
        digitalWrite(L2J1, LOW);
        digitalWrite(L3J1, LOW);
        digitalWrite(L4J1, LOW);
        digitalWrite(L5J1, LOW);
        digitalWrite(L6J1, LOW);
        digitalWrite(L7J1, LOW);
        digitalWrite(L8J1, LOW);
        break;
      case 2:
        //do something when var equals 
        digitalWrite(L1J1, LOW);
        digitalWrite(L2J1, HIGH);
        digitalWrite(L3J1, LOW);
        digitalWrite(L4J1, LOW);
        digitalWrite(L5J1, LOW);
        digitalWrite(L6J1, LOW);
        digitalWrite(L7J1, LOW);
        digitalWrite(L8J1, LOW);
        break;
      case 3:
        //do something when var equals 
        digitalWrite(L1J1, LOW);
        digitalWrite(L2J1, LOW);
        digitalWrite(L3J1, HIGH);
        digitalWrite(L4J1, LOW);
        digitalWrite(L5J1, LOW);
        digitalWrite(L6J1, LOW);
        digitalWrite(L7J1, LOW);
        digitalWrite(L8J1, LOW);
        break;
      case 4:
        //do something when var equals 
        digitalWrite(L1J1, LOW);
        digitalWrite(L2J1, LOW);
        digitalWrite(L3J1, LOW);
        digitalWrite(L4J1, HIGH);
        digitalWrite(L5J1, LOW);
        digitalWrite(L6J1, LOW);
        digitalWrite(L7J1, LOW);
        digitalWrite(L8J1, LOW);
        break;            
      case 5:
        //do something when var equals 1
        digitalWrite(L1J1, LOW);
        digitalWrite(L2J1, LOW);
        digitalWrite(L3J1, LOW);
        digitalWrite(L4J1, LOW);
        digitalWrite(L5J1, HIGH);
        digitalWrite(L6J1, LOW);
        digitalWrite(L7J1, LOW);
        digitalWrite(L8J1, LOW);
        break;
      case 6:
        //do something when var equals 
        digitalWrite(L1J1, LOW);
        digitalWrite(L2J1, LOW);
        digitalWrite(L3J1, LOW);
        digitalWrite(L4J1, LOW);
        digitalWrite(L5J1, LOW);
        digitalWrite(L6J1, HIGH);
        digitalWrite(L7J1, LOW);
        digitalWrite(L8J1, LOW);
        break;
      case 7:
        //do something when var equals 
        digitalWrite(L1J1, LOW);
        digitalWrite(L2J1, LOW);
        digitalWrite(L3J1, LOW);
        digitalWrite(L4J1, LOW);
        digitalWrite(L5J1, LOW);
        digitalWrite(L6J1, LOW);
        digitalWrite(L7J1, HIGH);
        digitalWrite(L8J1, LOW);
        break;
      case 8:
        //do something when var equals 
        digitalWrite(L1J1, LOW);
        digitalWrite(L2J1, LOW);
        digitalWrite(L3J1, LOW);
        digitalWrite(L4J1, LOW);
        digitalWrite(L5J1, LOW);
        digitalWrite(L6J1, LOW);
        digitalWrite(L7J1, LOW);
        digitalWrite(L8J1, HIGH);
        digitalWrite(L_B, HIGH);// se prede la led indicadora que gano el jugador uno.
        start = 0;
        J1 = 0;
        J2 = 0;// se resetea la bandera y tambien lo contadores de cada jugador para iniciar nuevamente la partida.
        delay(2000);
        digitalWrite(L1J1, LOW);
        digitalWrite(L2J1, LOW);
        digitalWrite(L3J1, LOW);
        digitalWrite(L4J1, LOW);
        digitalWrite(L5J1, LOW);
        digitalWrite(L6J1, LOW);
        digitalWrite(L7J1, LOW);
        digitalWrite(L8J1, LOW);
        digitalWrite(L_B, LOW);
        digitalWrite(L1J2, LOW);
        digitalWrite(L2J2, LOW);
        digitalWrite(L3J2, LOW);
        digitalWrite(L4J2, LOW);
        digitalWrite(L5J2, LOW);
        digitalWrite(L6J2, LOW);
        digitalWrite(L7J2, LOW);
        digitalWrite(L8J2, LOW);                
        break;             
    }
  }
}
//Funcion de interrupcion para el segundo jugador
void JUGADOR2(){
  if (start == 1)
  {
    delay(600);
    J2 = J2 + 1;// Se aumenta el contador del jugador 1 para dar los diferentes casos.
    switch (J2) 
    {
      case 1:
        //do something when var equals 1
        digitalWrite(L1J2, HIGH);
        digitalWrite(L2J2, LOW);
        digitalWrite(L3J2, LOW);
        digitalWrite(L4J2, LOW);
        digitalWrite(L5J2, LOW);
        digitalWrite(L6J2, LOW);
        digitalWrite(L7J2, LOW);
        digitalWrite(L8J2, LOW);
        break;
      case 2:
        //do something when var equals 
        digitalWrite(L1J2, LOW);
        digitalWrite(L2J2, HIGH);
        digitalWrite(L3J2, LOW);
        digitalWrite(L4J2, LOW);
        digitalWrite(L5J2, LOW);
        digitalWrite(L6J2, LOW);
        digitalWrite(L7J2, LOW);
        digitalWrite(L8J2, LOW);
        break;
      case 3:
        //do something when var equals 
        digitalWrite(L1J2, LOW);
        digitalWrite(L2J2, LOW);
        digitalWrite(L3J2, HIGH);
        digitalWrite(L4J2, LOW);
        digitalWrite(L5J2, LOW);
        digitalWrite(L6J2, LOW);
        digitalWrite(L7J2, LOW);
        digitalWrite(L8J2, LOW);
        break;
      case 4:
        //do something when var equals 
        digitalWrite(L1J2, LOW);
        digitalWrite(L2J2, LOW);
        digitalWrite(L3J2, LOW);
        digitalWrite(L4J2, HIGH);
        digitalWrite(L5J2, LOW);
        digitalWrite(L6J2, LOW);
        digitalWrite(L7J2, LOW);
        digitalWrite(L8J2, LOW);
        break;            
      case 5:
        //do something when var equals 1
        digitalWrite(L1J2, LOW);
        digitalWrite(L2J2, LOW);
        digitalWrite(L3J2, LOW);
        digitalWrite(L4J2, LOW);
        digitalWrite(L5J2, HIGH);
        digitalWrite(L6J2, LOW);
        digitalWrite(L7J2, LOW);
        digitalWrite(L8J2, LOW);
        break;
      case 6:
        //do something when var equals 
        digitalWrite(L1J2, LOW);
        digitalWrite(L2J2, LOW);
        digitalWrite(L3J2, LOW);
        digitalWrite(L4J2, LOW);
        digitalWrite(L5J2, LOW);
        digitalWrite(L6J2, HIGH);
        digitalWrite(L7J2, LOW);
        digitalWrite(L8J2, LOW);
        break;
      case 7:
        //do something when var equals 
        digitalWrite(L1J2, LOW);
        digitalWrite(L2J2, LOW);
        digitalWrite(L3J2, LOW);
        digitalWrite(L4J2, LOW);
        digitalWrite(L5J2, LOW);
        digitalWrite(L6J2, LOW);
        digitalWrite(L7J2, HIGH);
        digitalWrite(L8J2, LOW);
        break;
      case 8:
        //do something when var equals 
        digitalWrite(L1J2, LOW);
        digitalWrite(L2J2, LOW);
        digitalWrite(L3J2, LOW);
        digitalWrite(L4J2, LOW);
        digitalWrite(L5J2, LOW);
        digitalWrite(L6J2, LOW);
        digitalWrite(L7J2, LOW);
        digitalWrite(L8J2, HIGH);
        digitalWrite(L_R, HIGH);
        digitalWrite(L_B, HIGH);// se prede la led indicadora que gano el jugador uno.
        start = 0;
        J1 = 0;
        J2 = 0;// se resetea la bandera y tambien lo contadores de cada jugador para iniciar nuevamente la partida.
        delay(2000);
        digitalWrite(L1J1, LOW);
        digitalWrite(L2J1, LOW);
        digitalWrite(L3J1, LOW);
        digitalWrite(L4J1, LOW);
        digitalWrite(L5J1, LOW);
        digitalWrite(L6J1, LOW);
        digitalWrite(L7J1, LOW);
        digitalWrite(L8J1, LOW);
        digitalWrite(L_B, LOW);
        digitalWrite(L_R, LOW);
        digitalWrite(L1J2, LOW);
        digitalWrite(L2J2, LOW);
        digitalWrite(L3J2, LOW);
        digitalWrite(L4J2, LOW);
        digitalWrite(L5J2, LOW);
        digitalWrite(L6J2, LOW);
        digitalWrite(L7J2, LOW);
        digitalWrite(L8J2, LOW);                
        break;             
   }
  }
}
