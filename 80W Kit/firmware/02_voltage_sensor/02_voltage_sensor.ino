/*
  FiSH Floating Solar Hydrogen Prototype — 80W Kit
  Voltage sensor test (resistor-divider module, 0-25V range)

  Reads a resistive voltage-divider module on analog pin A0 (divides the
  measured voltage by ~5, max input 25V) and prints the result to Serial.
  Used standalone before integration into the full FiSH DataLogger sketch.

  Wiring: Voltage sensor "S"/OUT -> A0, "+" -> 5V, "-" -> GND
*/

void setup()
{
  Serial.begin(9600);
}
void loop()
{
      int val;
      float temp;
      val=analogRead(0);//This divider module will divide the measured voltage by 5, the maximum voltage it can measure is 25V.
      temp=val/40.92; //
      val=(int)temp;//
      Serial.println(val);
      delay(100);
}
