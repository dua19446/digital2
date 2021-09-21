int outPin[] = {PD_0, PD_1, PD_2, PD_3, PE_1, PE_2, PE_3, PA_7};
const int P_1 = PUSH1;
 
int tiempo = 600;

volatile int state = LOW;
 
void setup()
{
  pinMode(P_1, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(P_1), JUGADOR1, RISING);
  int i = 0;
  for ( i = 0; i < 8; i++)
    pinMode(outPin[i], OUTPUT);
}
 
void loop()
{
 
}

void JUGADOR1()
{
   int i = 0, j=0;
 {
  for ( i = 0; i < 255; i++)
  {
     for ( j = 0; j < 8; j++)
     {
       if ( ( (i >> j) & 1 )  == 1 )
           digitalWrite(outPin[j], HIGH);
       else digitalWrite(outPin[j], LOW);
     }
     delay(tiempo);
  }
 }
}
