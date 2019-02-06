// ACS712 Demo Sketch
//

// Select sensitivity for appropriate ACS712 version:
//int Sens = 185;           // Sensitivity in mV/A for the 5A version
//int Sens = 100;           // Sensitivity in mV/A for the 20A version
int Sens = 66;              // Sensitivity in mV/A for the 30A version

const int analogIn = A0;  // Analog input pin

int OffsetVoltage = 2500; // 0 Current offset Voltage in mV @ 0 amps

int RawValue= 0;          // Init result variables
double Voltage = 0;       //
double Amps = 0;          //

void setup(){ 
 Serial.begin(9600);      // Start serial monitor
}

void loop(){
 
 RawValue = analogRead(analogIn);           // Read voltage from ASC712
 Voltage = (RawValue / 1024.0) * 5000;      // Convert to mV
 Amps = ((Voltage - OffsetVoltage) / Sens); // Convert to amps
 
 
 Serial.print("A/D Read Value = " );  // A/D read value 
 Serial.print(RawValue);              //
 
 Serial.print("\t mV = ");            // ACS712 Output voltage 
 Serial.print(Voltage,3);             //
 
 Serial.print("\t Amps = ");          // Current measured
 Serial.println(Amps,3);              // 
 
 delay(2500);                         // Wait a bit then do it again
 
}
