// Full orientation sensing using NXP's advanced sensor fusion algorithm.
//
// You *must* perform a magnetic calibration before this code will work.
//
// To view this data, use the Arduino Serial Monitor to watch the
// scrolling angles, or run the OrientationVisualiser example in Processing.

#include <NXPMotionSense.h>
#include <Wire.h>
#include <EEPROM.h>

NXPMotionSense imu;
NXPSensorFusion filter;

void setup() {
  Serial.begin(9600);
  imu.begin();
  filter.begin(100);
}

void loop() {
  float ax, ay, az;
  float gx, gy, gz;
  float mx, my, mz;
  float roll, pitch, heading;

  if (imu.available()) {
    // Read the motion sensors
    imu.readMotionSensor(ax, ay, az, gx, gy, gz, mx, my, mz);

    // Update the SensorFusion filter
    filter.update(gx, gy, gz, ax, ay, az, mx, my, mz);

    // print the heading, pitch and roll
    roll = filter.getRoll();
    pitch = filter.getPitch();
    heading = filter.getYaw();
    Serial.print("/ctrl,heading,");
    Serial.println(map(heading, 0, 360, 0, 1));
    Serial.print("/ctrl,pitch,");
    Serial.println(map(pitch, -90, 90, 0, 1));
    Serial.print("/ctrl,roll,");
    Serial.println(map(roll,-180, 180, 0, 1));
  }
}
