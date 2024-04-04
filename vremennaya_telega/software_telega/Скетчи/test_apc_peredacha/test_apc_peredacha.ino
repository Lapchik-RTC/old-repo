void setup() {
  Serial1.begin(9600);
 // Serial1.begin(9600);

}

void loop() 
{
  for (int i=0; i<256; i++)
  {
    Serial1.write(i);
   // Serial.println(i);
    delay(50);
  }

}
