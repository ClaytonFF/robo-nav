/**
  Robô NAV (desvia obstáculos)
  @authors Clayton, Tainara e João
  @version 1.0
  @link https://github.com/ClaytonFF/robo-nav/tree/main
*/
// Sensor utralssônico
#define echo 11  //recebe o pulso
#define trig 12  //envia o pulso
// Led indicador
#define led 13  //led indicador
// Motores
#define M1A 5   //motor da esquerda
#define M1B 6   //motor da esquerda
#define M2A 9   //motor da direita
#define M2B 10  //motor da direita
// Variáveis para ajuste de velocidade
int velM1 = 135;  //velocidada do motor M1 (0 a 255)Direita
int velM2 = 120;  //velocidada do motor M2 (0 a 255)

void setup() {
  pinMode(led, OUTPUT);   //Led provisório
  pinMode(trig, OUTPUT);  //Sensor
  pinMode(echo, INPUT);   //Sensor
  pinMode(M1A, OUTPUT);   //Motor esquerda
  pinMode(M1B, OUTPUT);   //Motor esquerda
  pinMode(M1B, OUTPUT);   //Motor direita
  pinMode(M1B, OUTPUT);   //Motor direita
  Serial.begin(9600);     //Teste do sonar (provisório)
}


void loop() {
  //executa a função ping (dispara o pulso) e guarda na variáivel distancia
  int distancia = ping();
  Serial.print(distancia);
  Serial.println("cm");

  //lógica principal
  if (distancia < 30) {
    digitalWrite(led, HIGH);
    parar();
    delay(1000); //ficar parado por 1 segundo
    direita();   //girar sentido horário
    delay(300);  //por 300ms
  } else {
    digitalWrite(led, LOW);
    frente();
  }


  delay(60);  //60ms entre leituras para evitar eco residual
}

//Fução para ler o sensor e retornar o valor em cm.
int ping() {
  // iniciar trig desligado
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  //enviar pulso de 10 mirosegundos
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  // ler o tempo de duração (retorno) no echo

  long duracao = pulseIn(echo, HIGH);
  //converter para centímetros
  int distancia = duracao / 58.0;
  //retorna o valor da distância em cm

  return distancia;
}

// função para mover o robô para frente
void frente() {

  analogWrite(M1A, velM1);
  analogWrite(M1B, 0);
  analogWrite(M2A, velM2);
  analogWrite(M2B, 0);
}

// função para mover o robô de ré
void re(){

  analogWrite(M1B, velM1);
  analogWrite(M1A, 0);
  analogWrite(M2B, velM2);
  analogWrite(M2A, 0);
}

// função para girar o robô no sentito horário(direita)
void direita(){

  analogWrite(M1B, velM1);
  analogWrite(M1A, 0);
  analogWrite(M2A, velM2);
  analogWrite(M2B, 0);
}

// função para girar o robô no sentito anti-horário(esquerda)
void esquerda(){

  analogWrite(M1A, velM1);
  analogWrite(M1B, 0);
  analogWrite(M2B, velM2);
  analogWrite(M2A, 0);
}

// função parar o robô
void parar() {

  analogWrite(M1A, 0);
  analogWrite(M1B, 0);
  analogWrite(M2A, 0);
  analogWrite(M2B, 0);
}
