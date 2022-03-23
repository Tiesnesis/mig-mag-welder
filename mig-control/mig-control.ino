// Defin pins

int driverPUL = 7;    // PUL- pin
int driverDIR = 6;    // DIR- pin
int spd = A0;     // Potentiometer
int gas = 10;  // Gas relay pin
int power = 11; // Welding power relay
int weldSwitch = 13; // Welding gun switch

// Variables

int pd = 500;       // Pulse Delay period
boolean setdir = LOW; // Set Direction
boolean weldState = false; // Is welding in progress?

// Interrupt Handler

void setup() {

  pinMode (driverPUL, OUTPUT);
  pinMode (driverDIR, OUTPUT);
  pinMode (gas, OUTPUT);
  pinMode (power, OUTPUT);
  pinMode (weldSwitch, INPUT);

  digitalWrite(power,HIGH);
  digitalWrite(gas,HIGH);

  
}

void loop() {

    if(digitalRead(weldSwitch)){
      if(weldState){
        pd = map((analogRead(spd)),0,1023,2000,50);
        digitalWrite(driverDIR,setdir);
        digitalWrite(driverPUL,HIGH);
        delayMicroseconds(pd);
        digitalWrite(driverPUL,LOW);
        delayMicroseconds(pd);
      }
      else{
        digitalWrite(gas,LOW);
        delay(100);
        digitalWrite(power,LOW);
        weldState = true;
      }
    }
    else{
      if(weldState){
        digitalWrite(power,HIGH);
        delay(500);
        digitalWrite(gas,HIGH);
        weldState = false;
      }
    }
}
