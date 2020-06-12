#include <TimerOne.h>

#define TRIG_OUT  4 // Trigger signal to env generator
#define MULTI_IN  1 // active low pulse from trigger/gate of synth
#define LED 11 // wanted to flash the led when a timer cycle had finished to show it was working mono/multi mode.
#define DELAY_CV  A0 // Analogue signal 0-5v to determine delay time
long delaytime  = 0;
long newdelay = 0;
int keytrig = 0;

void setup() 
{
Serial.begin(19200);
pinMode(TRIG_OUT, OUTPUT);
pinMode(LED, OUTPUT);
pinMode(MULTI_IN, INPUT_PULLUP);

digitalWrite(TRIG_OUT, LOW);
digitalWrite(LED, LOW);

Timer1.initialize();
Timer1.start();
// Timer1.attachInterrupt(startLFO);
Timer1.stop();
}

void startLFO()
{
  Serial.println("Starting LFO");
  digitalWrite(LED, HIGH);
  digitalWrite(TRIG_OUT, HIGH);
  delayMicroseconds(100);
  digitalWrite(LED, LOW);
//  digitalWrite(TRIG_OUT, LOW);
  keytrig = 1;
}

void checkTrigger()
{
  keytrig = digitalRead(MULTI_IN);   // read the input pin
}

void getDelayTime()
{
  delaytime = analogRead(DELAY_CV);
  Serial.print("delay time ");
  Serial.println(delaytime);
}

void timerLoop()
{
    Serial.println(keytrig);
  if (keytrig == 0)
  {
    Serial.print("This is what the timer sees ");
    Serial.println(keytrig);
    newdelay = (delaytime * 6400);
    Serial.print("This is what the new delay time is ");
    Serial.println(newdelay);
    Timer1.setPeriod(newdelay); // to get upto 6.5 seconds delay
    Timer1.start();
//    Timer1.pwm(TRIG_OUT, 1023);
    Timer1.pwm(TRIG_OUT, 1);
    Timer1.disablePwm(TRIG_OUT);
    digitalWrite(TRIG_OUT, HIGH);
    delay(20);
    digitalWrite(TRIG_OUT, LOW);
  }
}

void loop() 
{
  checkTrigger();
  getDelayTime();
  timerLoop();
}
