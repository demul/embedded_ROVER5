#define BRAKEVCC 0
#define CW   1
#define CCW  2
#define BRAKEGND 3
#define CS_THRESHOLD 100

#define DECODE(encoding, pwm, cw) cw = (encoding & (char)1) + 1;pwm = (encoding>>1)<<3;
                                  
                                  
int inApin[2] = {7, 4};  // INA: Clockwise input
int inBpin[2] = {8, 9}; // INB: Counter-clockwise input
int pwmpin[2] = {5, 6}; // PWM input
int cspin[2] = {2, 3}; // CS: Current sense ANALOG input
int enpin[2] = {0, 1}; // EN: Status of switches output (Analog pin)

int statpin = 13;


void setup()
{
  Serial.begin(115200);
  
  pinMode(statpin, OUTPUT);

  // Initialize digital pins as outputs
  for (int i=0; i<2; i++)
  {
    pinMode(inApin[i], OUTPUT);
    pinMode(inBpin[i], OUTPUT);
    pinMode(pwmpin[i], OUTPUT);
  }
  // Initialize braked
  for (int i=0; i<2; i++)
  {
    digitalWrite(inApin[i], LOW);
    digitalWrite(inBpin[i], LOW);
  }

}

char temp;
char encoding[2];
int pwm;
char cw;

void loop()
{
  while(Serial.available() <=0) // wait for incoming serial data
  {
  }

  temp = (char)Serial.read();
  switch(temp)  
  {
        case 'a':
              Serial.println("a");
              motorGo(0, CW, 400);
              motorGo(1, CW, 400);
              break;  

        case 'b':
              Serial.println("b");
              motorGo(0, CCW, 400);
              motorGo(1, CCW, 400);
              break;  

        case 'c':
              Serial.println("c");
              motorGo(0, CCW, 400);
              motorGo(1, CW, 400);
              break;  

        case 'd':
              Serial.println("d");
              motorGo(0, CW, 400);
              motorGo(1, CCW, 400);
              break;  

        case 'i':
              Serial.println("i");
              motorOff(0);
              motorOff(1);
              break;  
         
        case 'k':
              Serial.println("k");
              Serial.readBytes(encoding, 2);
              DECODE(encoding[0], pwm, cw);
              motorGo(0, cw, pwm);
              DECODE(encoding[1], pwm, cw);
              motorGo(1, cw, pwm);
              break;
  }
}

void motorOff(int motor)
{
  // Initialize braked
  for (int i=0; i<2; i++)
  {
    digitalWrite(inApin[i], LOW);
    digitalWrite(inBpin[i], LOW);
  }
  analogWrite(pwmpin[motor], 0);
}

void motorGo(uint8_t motor, uint8_t direct, uint8_t pwm)
{
  if (motor <= 1)
  {
    if (direct <=4)
    {
      // Set inA[motor]
      if (direct <=1)
        digitalWrite(inApin[motor], HIGH);
      else
        digitalWrite(inApin[motor], LOW);

      // Set inB[motor]
      if ((direct==0)||(direct==2))
        digitalWrite(inBpin[motor], HIGH);
      else
        digitalWrite(inBpin[motor], LOW);

      analogWrite(pwmpin[motor], pwm);
    }
  }
}

