const int dataSize =8;

int data[dataSize];
char req=0;

void setup() {
  // put your setup code here, to run once:
  Serial1.begin(115200);
  Serial1.setTimeout(1);
//  Serial.begin(115200);
  pinMode(13,OUTPUT);
  digitalWrite(13,0);
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i=0;i<dataSize;i++)  {
    data[i]=analogRead(i);
  }

//  for(int i=0;i<8;i++)  {
//    Serial.print(data[i]);
//  }
//  Serial.println();
  
  if(Serial1.available())  {
    req=Serial1.read();
    if(req==48) {
      digitalWrite(13,1);
      for(int i=0;i<dataSize;i++)  {
        Serial1.write(data[i]);
      }
      digitalWrite(13,0);
    }
    Serial1.flush();
  }
  
}
