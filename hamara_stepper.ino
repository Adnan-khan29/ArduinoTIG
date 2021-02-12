const int ena = 2; //habilita o motor
const int dir = 3; //determina a direção
const int pul = 4; //executa um passo
const int intervalo = 200;   //this determines the speed of motor
   // mudanças de estado do pulso
boolean pulso = LOW; //estado do pulso
 
void setup()
{
pinMode(ena, OUTPUT);
pinMode(dir, OUTPUT);
pinMode(pul, OUTPUT);
digitalWrite(ena, LOW); //habilita em low invertida 
digitalWrite(dir, HIGH); // low +x / high for -X
digitalWrite(pul, HIGH); //borda de descida
}
 
void loop()
{
pulso = !pulso; //inverte o estado da variável
digitalWrite(pul, pulso); //atribui o novo estado à porta
delayMicroseconds(intervalo); 
}
