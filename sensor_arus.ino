#include <ACS7xx_Allegro.h>

// example for ACS712 : bidir = true, A0 is the sensor pin, 5.0 is the volatge board, 0.1 is the sensibility of the chip
ACS7XX_ALLEGRO mysensor(true, 0, 5.0, 0.1);

double readcurrent;
double mAH;
double timeframehour;
//double _lastMillis ;
void setup() {

  Serial.begin(9600);
  while (!Serial) ; //wait until Serial ready

  mysensor.begin();

  Serial.println("Starting...");
  //check serial output now
  mysensor.printDebugDeviceInit();
}

double kaloutput;
double kalman(double U) {
  static const double R = 40;
  static const double H = 1.00;
  static double Q = 10;
  static double P = 0;
  static double U_hat = 0;
  static double K = 0;
  K = P * H / (H * P * H + R);
  U_hat += + K * (U - H * U_hat);
  P = (1 - K * H) * P + Q;
  return U_hat;
}

void loop() {
  mysensor.instantCurrent(&readcurrent);
  
//  Serial.print("Current mesure: ");
//  Serial.print(readcurrent, DEC);
//  Serial.print("\t");
//  Serial.print(mysensor.getMovingAvgExp(), DEC);
//  Serial.print("\t");
  kaloutput=kalman(mysensor.getMovingAvgExp());
  Serial.print(kaloutput);
  Serial.println("\t");
  delay(300);

  //  mysensor.ampereHourCount(&mAH);
  //  mysensor.instantCurrent(&readcurrent);
  //  unsigned long currentmillis = millis();
  //  timeframehour = (double)(currentmillis - _lastMillis) / 3600000.0;
  //  _lastMillis = currentmillis;

  //  Serial.print("AmpHour: ");
  //  Serial.print(mAH, DEC);
  //  Serial.print(" mAh");
  //  Serial.print("\t");
  //  Serial.print("timeframe ");
  //  Serial.print(timeframehour, DEC);
  //  Serial.println(" hour");
  //  delay(1000);

}
