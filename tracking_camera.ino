//Face Tracker using OpenCV and Arduino

#include <Servo.h>

Servo x, y;
double width = 640, height = 480;  // total resolution of the video
double xpos = 90, ypos = 90;  // initial positions of both Servos

void setup() {
  Serial.begin(38400);
  x.attach(6);
  y.attach(9);
  x.write(xpos);
  y.write(ypos);
}

const double power = 0.5;   // degree of increment or decrement

void loop() {
  Serial.flush();
  while (Serial.available() == 0); 
    double x_mid, y_mid;
    if (Serial.read() == 'X') {
      delay(5);
      x_mid = Serial.parseInt();  // read center x-coordinate
      if (Serial.read() == 'Y') {
        delay(5);
        y_mid = Serial.parseInt(); // read center y-coordinate

        // adjust the servo within the squared region if the coordinates are outside it
        if (x_mid > width / 2 + 30) {
          xpos += power;
          x.write(xpos);
        }
        if (x_mid < 320) {
          xpos += power;
          x.write(180-xpos);  
        }
        if (y_mid < height / 2 - 30) {
          ypos -= power;
          y.write(ypos);
        }
        if (y_mid > height / 2 + 30) {
          ypos += power;
          y.write(ypos);
        }

        // center the servo if the face is in the center of the screen
        if (x_mid > width / 2 - 10 && x_mid < width / 2 + 10) {
          xpos = 90;
        }
        if (y_mid > height / 2 - 10 && y_mid < height / 2 + 10) {
          ypos = 90;
        }

        // move the servos to their adjusted positions
        delay(9);
        x.write(90);
        y.write(90);

        // used for testing
        Serial.print("xpos: ");
        Serial.print(xpos);
        Serial.print(", ypos: ");
        Serial.println(ypos);
        Serial.print("x_mid: ");
        Serial.print(x_mid);
        Serial.print(", y_mid: ");
        Serial.println(y_mid);
      }
    }
  
}
