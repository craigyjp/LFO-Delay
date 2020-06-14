unsigned long previousMillis = 0;
unsigned long interval = 1; //10 seconds
int LDRLED  = 11;            // select the input pin for the ldr
#define TRIG_OUT  0 // Trigger signal to env generator
#define GATE_IN  1 // active low pulse from trigger/gate of synth
#define TRIG1 2 // test for triggers
#define TRIG2 3 // test for triggers
#define TRIG3 4 // test for triggers
#define TRIG4 5 // test for triggers
#define TRIG5 6 // test for triggers
#define TRIG6 7 // test for triggers
#define MONO_MULT 8 // what mode for triggers are we in
#define DELAY_CV  A0 // Analogue signal 0-5v to determine delay time
long delaytime  = 0;
int keygate = 0;

void setup()
{
  pinMode(LDRLED, OUTPUT);
  pinMode(TRIG_OUT, OUTPUT);
  digitalWrite(TRIG_OUT, LOW);
  pinMode(GATE_IN, INPUT_PULLUP);
  pinMode(TRIG1, INPUT_PULLUP);
  pinMode(TRIG2, INPUT_PULLUP);
  pinMode(TRIG3, INPUT_PULLUP);
  pinMode(TRIG4, INPUT_PULLUP);
  pinMode(TRIG5, INPUT_PULLUP);
  pinMode(TRIG6, INPUT_PULLUP);
  pinMode(MONO_MULT, INPUT_PULLUP);
  //Start Serial port
  Serial.begin(9600);        // start serial for output - for testing
}

void getDelayTime()
{
  delaytime = analogRead(DELAY_CV);
  if (delaytime <= 0)
  {
    delaytime = 0.1;
  }
  interval = (delaytime * 10);
//  Serial.print("delay time ");
//  Serial.println(interval);
}

void loop()
{
  getDelayTime();
  unsigned long currentMillis = millis();
  if (digitalRead(MONO_MULT) <= 0)
  {
  if (digitalRead(TRIG1) <= 0 || digitalRead(TRIG2) <= 0 || digitalRead(TRIG3) <= 0 || digitalRead(TRIG4) <= 0 || digitalRead(TRIG5) <= 0 || digitalRead(TRIG1) <= 0)
  { 
    previousMillis = currentMillis;
  }
  }
  keygate = digitalRead(GATE_IN);   // read the gate pin
//  Serial.print("key trig ");
//  Serial.println(keygate);
  if (keygate <= 0) { 
    if (currentMillis - previousMillis >= interval) 
    {
      digitalWrite(LDRLED, HIGH);
      digitalWrite(TRIG_OUT, HIGH);
    }
  }
  else
  {
    digitalWrite(LDRLED, LOW);   // set the LED off
    digitalWrite(TRIG_OUT, LOW);
    previousMillis = currentMillis;//reset timer so its ready for the next time
  }
}
