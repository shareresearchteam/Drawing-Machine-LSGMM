void lift(int on_off) {
  int pos;

  if (on_off == 0) {
    if (servo1.read() != ang_max) {
      for (pos = ang_min; pos <= ang_max; pos += 1) {
        servo1.write(pos);
        delay(45);
      }
    }
  }

  else {
    if (servo1.read() != ang_min) {
      for (pos = ang_max; pos >= ang_min; pos -= 1) {
        servo1.write(pos);
        delay(45);
      }
    }
  }

}

void lift_to(double x_init, double y_init) {
  delay(20);
  lift(0);
  delay(20);
  motorStep(x_init, y_init, 350);
  delay(20);
  lift(1);
  delay(20);
}
