void lineSeg(double x1, double y1, double x2, double y2, bool lift, double Speed) {


  double m;
  if ((x2 - x1) == 0)
    m = 0;
  else
    m = (y2 - y1) / (x2 - x1);

  double b = y1 - m * x1;

  // if (lift == 1)
  //lift_to(x1, y1);

  if (x1 < x2) {
    for (double x = x1; x < x2; x = x + .02) {
      motorStep(x, m * x + b, Speed);
    }
  } else if (x1 > x2) {
    for (double x = x1; x > x2; x = x - .02) {
      motorStep(x, m * x + b, Speed);
    }
  } else if (x2 == x1) {
    if (y1 < y2) {
      for (double y = y1; y < y2; y = y + .02) {
        motorStep(x1, y, Speed);
      }
    } else if (y2 < y1) {
      for (double y = y1; y > y2; y = y - .02) {
        motorStep(x1, y, Speed);
      }
    }
  }
}
