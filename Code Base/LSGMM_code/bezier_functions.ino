
double find_slope(double x1, double y1, double x2, double y2) {
  double slope = 0;
  if ((x2 - x1) != 0) {
    slope = (y2 - y1) / (x2 - x1);
  }
  return slope;
}

double find_b(double x1, double y1, double m) {
  double b;
  b = y1 - x1 * m;
  return b;
}

double x_btw(double x1, double x2, double m, double n) {
  double x = n * (x2 - x1) + x1;
  return x;
}

double y_btw(double x, double x1, double y1, double m) {
  double y = m * (x - x1) + y1;
  return y;
}


double rand_cp_x(double x1, double y1, double x2, double y2, double n, double phi, double scl) {
  double m = find_slope(x1, y1, x2, y2);
  double xr = x_btw(x1, x2, m, n);
  double ndx = cos(phi);
  double cx = xr + ndx * scl;
  return cx;
}

double rand_cp_y(double x1, double y1, double x2, double y2, double n, double phi, double scl) {
  double m = find_slope(x1, y1, x2, y2);
  double xr = x_btw(x1, x2, m, n);
  double yr = y_btw(xr, x1, y1, m);
  double ndy = sin(phi);
  double cy = yr + ndy * scl;
  return cy;
}

void bez_con(double x1, double y1, double x2, double y2, double n_min, double n_max, double scale ) {

  scale = randomDouble(-scale, scale);
  double phi = randomDouble(0, 2 * PI); //atan(-1/find_slope(x1, y1, x2, y2));
  double n = randomDouble(n_min, n_max);
  double cx1 = rand_cp_x(x1, y1, x2, y2, n, phi, scale);
  double cy1 = rand_cp_y(x1, y1, x2, y2, n, phi, scale);
  //ellipse(cx1, cy1, 4, 4);

  scale = randomDouble(-scale, scale);
  phi = randomDouble(0, 2 * PI); //atan(-1/find_slope(x1, y1, x2, y2));
  n = randomDouble(n_min, n_max);
  double cx2 = rand_cp_x(x1, y1, x2, y2, n, phi, scale);
  double cy2 = rand_cp_y(x1, y1, x2, y2, n, phi, scale);
  //ellipse(cx2, cy2, 4, 4);
  bezman(
    x1, y1,
    cx1, cy1,
    cx2, cy2,
    x2, y2
  );

}

double getPt( double n1, double n2, double perc )
{
  double diff = n2 - n1;

  return n1 + ( diff * perc );
}

void bezman(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4) {
  for ( double i = 0; i < 1; i += 0.03 )//.03
  {
    double xa, xb, xc, ya, yb, yc, xm, ym, xn, yn, x, y;
    // The Green Lines
    xa = getPt( x1, x2, i );
    ya = getPt( y1, y2, i );
    xb = getPt( x2, x3, i );
    yb = getPt( y2, y3, i );
    xc = getPt( x3, x4, i );
    yc = getPt( y3, y4, i );

    // The Blue Line
    xm = getPt( xa, xb, i );
    ym = getPt( ya, yb, i );
    xn = getPt( xb, xc, i );
    yn = getPt( yb, yc, i );

    // The Black Dot
    x = getPt( xm, xn, i );
    y = getPt( ym, yn, i );

    motorStep(x, y, spd);
  }
}

void bezman_sense(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4) {
  for ( double i = 0; i < 1; i += 0.03 )//.03
  {
    double xa, xb, xc, ya, yb, yc, xm, ym, xn, yn, x, y;
    // The Green Lines
    xa = getPt( x1, x2, i );
    ya = getPt( y1, y2, i );
    xb = getPt( x2, x3, i );
    yb = getPt( y2, y3, i );
    xc = getPt( x3, x4, i );
    yc = getPt( y3, y4, i );

    // The Blue Line
    xm = getPt( xa, xb, i );
    ym = getPt( ya, yb, i );
    xn = getPt( xb, xc, i );
    yn = getPt( yb, yc, i );

    // The Black Dot
    x = getPt( xm, xn, i );
    y = getPt( ym, yn, i );

    double speed_sense = 1 + 4 * (double)max(min(loadCell_2.get_units() * 6, 1), 0);
    motorStep(x, y, spd*speed_sense);
    double s1 = (double)max(min(loadCell_1.get_units() * 2, .2), 0);
    if (s1 > .1) {
      break;
    }
  }
}

void bez_con_sense(double x1, double y1, double x2, double y2, double n_min, double n_max, double scale, double ang, int sense) {

  scale = randomDouble(scale / 3, scale);
  double phi = ang;//randomDouble(0, PI); //atan(-1/find_slope(x1, y1, x2, y2));
  double n = randomDouble(.2, .5);
  double cx1 = rand_cp_x(x1, y1, x2, y2, n, phi, scale);
  double cy1 = rand_cp_y(x1, y1, x2, y2, n, phi, scale);
  //ellipse(cx1, cy1, 4, 4);

  scale = randomDouble(scale / 3, scale);
  phi = ang;//randomDouble(0, PI); //atan(-1/find_slope(x1, y1, x2, y2));
  n = randomDouble(.5, .8);
  double cx2 = rand_cp_x(x1, y1, x2, y2, n, phi, scale);
  double cy2 = rand_cp_y(x1, y1, x2, y2, n, phi, scale);
  //ellipse(cx2, cy2, 4, 4);
  if (sense == 1) {
    bezman_sense(
      x1, y1,
      cx1, cy1,
      cx2, cy2,
      x2, y2
    );
  }
  else {
    bezman(
      x1, y1,
      cx1, cy1,
      cx2, cy2,
      x2, y2
    );
  }

}

double randomDouble(double minf, double maxf)
{
  return minf + random(1UL << 31) * (maxf - minf) / (1UL << 31);  // use 1ULL<<63 for max double values)
}
