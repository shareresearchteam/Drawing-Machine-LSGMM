// Rectangle
void rect(double x, double y, double wid, double len) {
  // smove  (  x, y);
  lineSeg(  x,       y,       x + wid, y         , 0, 3000);
  Serial.println("seg 1");
  lineSeg(  x + wid, y,       x + wid, y + len    , 0, 3000 );
  Serial.println("seg 2");
  lineSeg(  x + wid, y + len, x,       y + len  , 0, 3000 );
  Serial.println("seg 3");
  lineSeg(  x,       y + len, x,       y, 0, 5000);
}

// Filled Rectangle
void frect(double xz, double yz, double w, double l) {

  double lim = 0;
  double ox;
  double oy;
  int _spd = 1000;
  if (w > l) {
    lim = l / 2;
  }
  else {
    lim = w / 2;
  }

  for (double p = 0; p < lim; p += 0.01) {  //.01
    ox = p;
    oy = p;
    _spd = lineSeg_ser_spd(xz + ox, yz + oy, xz + w - ox, yz + oy, 0, _spd);
    _spd = lineSeg_ser_spd(xz + w - ox, yz + oy, xz + w - ox, yz + l - oy, 0, _spd);
    _spd = lineSeg_ser_spd(xz + w - ox, yz + l - oy, xz + ox, yz + l - oy, 0, _spd);
    _spd = lineSeg_ser_spd( xz + ox, yz + l - oy, xz + ox, yz + oy + .1, 0,  _spd);
  }
}

void rect2(double xz, double yz, double w, double l){
 
  double lim = 0;
  double ox=0;
  double oy=0;
  int _spd = 1000;
  if (w > l) {
    lim = l / 2;
  }
  else {
    lim = w / 2;
  }
    _spd = lineSeg_ser_spd(xz + ox, yz + oy, xz + w - ox, yz + oy, 0, _spd);
    _spd = lineSeg_ser_spd(xz + w - ox, yz + oy, xz + w - ox, yz + l - oy, 0, _spd);
    _spd = lineSeg_ser_spd(xz + w - ox, yz + l - oy, xz + ox, yz + l - oy, 0, _spd);
    _spd = lineSeg_ser_spd( xz + ox, yz + l - oy, xz + ox, yz + oy + .1, 0,  _spd);

}

void circle(double xs, double ys, double r) {
  double x, y;
  for (double theta = 0; theta < (2 * PI); theta += .04) {
    x = r * cos(theta);
    y = r * sin(theta);
    motorStep(x + xs, y + ys, 400);
  }
}


void circle_solid(double xs, double ys, double r) {
  for (double r_int = r; r_int > .005; r_int -= .01) {
    circle(xs, ys, r_int);
  }
}
