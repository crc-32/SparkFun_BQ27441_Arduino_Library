#include <SparkFunBQ27441.h>

const unsigned int BATTERY_CAPACITY = 850; // e.g. 850mAh battery
unsigned int fullCapacity;
void setupBQ27441(void)
{
  if (!lipo.begin())
  {
    Serial.println("Error: Unable to communicate with BQ27441.");
    Serial.println("  Check wiring and try again.");
    Serial.println("  (Battery must be plugged into Battery Babysitter!)");
    while (1) ;
  }
  Serial.println("Connected to BQ27441!");
  
  lipo.setCapacity(BATTERY_CAPACITY);
  fullCapacity = lipo.capacity(FULL);
  Serial.print("Full charge capacity set to: ");
  Serial.println(String(fullCapacity) + " mAh");
}

void printBatteryStats()
{
  unsigned int soc = lipo.soc();
  unsigned int volts = lipo.voltage();
  int current = lipo.current(AVG);
  unsigned int capacity = lipo.capacity(REMAIN);
  int power = lipo.power();
  int health = lipo.soh();

  String toPrint = String(soc) + "% | ";
  toPrint += String(volts) + " mV | ";
  toPrint += String(current) + " mA | ";
  toPrint += String(capacity) + " / ";
  toPrint += String(fullCapacity) + " mAh | ";
  toPrint += String(power) + " mW | ";
  toPrint += String(health) + "%";
  
  Serial.println(toPrint);
}

void setup()
{
  Serial.begin(115200);
  setupBQ27441();
}

void loop() 
{
  printBatteryStats();
  delay(1000);
}