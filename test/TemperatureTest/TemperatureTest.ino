/*
 * File:   TemperatureTest.ino
 * Author: Karl Kangur, ESA/ESTEC
 * Date:   2017-03-17
 */
  
// Temperature sensor array
float temperatures[4] = {0};

void setup()
{
  Serial.begin(9600);
  pinMode(13, OUTPUT);
}

void loop()
{
  // Define temperatures as dummy random values
  temperatures[0] = (float)(random(0, 1000) / 1000.0f);
  temperatures[1] = (float)(random(0, 1000) / 1000.0f);
  temperatures[2] = (float)(random(0, 1000) / 1000.0f);
  temperatures[3] = (float)(random(0, 1000) / 1000.0f);
  
  sendTemperatures();
  
  delay(200);
  digitalWrite(13, !digitalRead(13));
}

void sendTemperatures()
{
  // Header signature
  static const byte header[4] = {0xFE, 0x81, 0xFF, 0x55};
  
  // Sequential counter, loops back to 0 after 127
  static byte sequence = 0;

  // Transmit header
  int i;
  for(i = 0; i < sizeof(header) / sizeof(header[0]); i++)
  {
    Serial.write(header[i]);
  }

  // Write out the sequence and increase by 1
  Serial.write(sequence++);

  // Loop sequence back to 0
  if(sequence == 128)
  {
    sequence = 0;
  }

  // Send out the temperature values
  for(i = 0; i < sizeof(temperatures); i++)
  {
    // Write out all the bytes of the temperature array
    byte * b = (byte *) &temperatures + i;
    Serial.write(*b);
  }
}



