// Relay
#define RY1           13
#define RY2           12
#define RY3           11
#define RY4           10
#define RY5           9

#define ON            1
#define OFF           0

void relay_control(unsigned char ch, unsigned char state)
{
    if((ch >= 1)&&( ch <= 5))
    {
      if(ch == 1)
        digitalWrite(RY1, state);
      else if (ch == 2)
        digitalWrite(RY2, state);
      else if (ch == 3)
        digitalWrite(RY3, state);
      else if (ch == 4)
        digitalWrite(RY4, state);
      else if (ch == 5)
        digitalWrite(RY5, state);
      
      Serial.print("Relay "); Serial.print(ch); Serial.print(" is ");
      if(state == ON)
        Serial.println("ON");
      else
        Serial.println("OFF");     
    }
    delay(1);
}

void process_command(String inputString)
{
  // Relay Control
  if(inputString.length() >= 4)
    if(inputString[0] == 'R' && inputString[1] == 'Y')
      if((inputString[2] >= 0x30)&&(inputString[2] <= 0x39))
        if((inputString[3] >= 0x30)&&(inputString[3] <= 0x39))
        {
          relay_control(inputString[2] - 0x30, inputString[3] - 0x30);
        }
}

void read_serial(void)
{
  String inputString = "";
  char inChar;
  
  while (Serial.available()) 
  {
    // get the new byte:
    inChar = (char)Serial.read();
    inputString += inChar;
    delay(1);
  }
  
  if(inputString.length() > 0)
  { 
    Serial.print("Receive: "); Serial.println(inputString);
    process_command(inputString);
  }
  Serial.flush();
}

void setup() 
{
  pinMode(RY1, OUTPUT);
  pinMode(RY2, OUTPUT);
  pinMode(RY3, OUTPUT);
  pinMode(RY4, OUTPUT);
  pinMode(RY5, OUTPUT);

  Serial.begin(115200);
  delay(10);
  Serial.println("System Start...");
}

void loop() 
{
  read_serial();
  delay(1);
}

