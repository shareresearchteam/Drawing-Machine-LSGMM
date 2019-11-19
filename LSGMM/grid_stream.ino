

void grid_stream(float xof, float yof) {


  int   n_els   = 400;
  float sx      = 8;  // offset x
  float sy      = 8;   // offset y
  float _width  = 80;
  float _height = 36;
  float spc     = 0;
  long  t       = 0;

  double scale =  .35;
  double n_min = .25;
  double n_max = .75;

  spc = (_width - sx * 2) / (float)n_els;
  float xprev  = sx + spc  / 2 + xof;
  float yprev  = sy + yof;

  while (n_els > 0 && sy < (_height + sy - 8)) {
    spc = (_width - sx * 2) / (float)n_els;
    for (int j = 0; j < n_els; j++) {
      t++;
      if (low_bound(sx + spc / 2 + spc * j, sy, _height) && high_bound(sx + spc / 2 + spc * j, sy, _height)) {
        bez_con(xprev, yprev, xof + sx + spc / 2 + spc * j, yof + sy, n_min, n_max, scale);
        element(xof + sx + spc / 2 + spc * j, yof + sy);
        xprev = xof + sx + spc / 2 + spc * j;
        yprev = yof + sy;
      }
    }
    //sx +=spc/2;
    int _rand = 0; (int)random(-2, 6);
    n_els = n_els - _rand;
    //println(rand);
    sy += .2;
    for (int j = n_els; j > 0; j--) {
      t++;
      if (low_bound(sx + spc / 2 + spc * j, sy, _height) && high_bound(sx + spc / 2 + spc * j, sy, _height)) {
        bez_con(xprev, yprev, xof + sx + spc / 2 + spc * j, yof + sy, n_min, n_max, scale);
        element(xof + sx + spc / 2 + spc * j, yof + sy);
        xprev = xof + sx + spc / 2 + spc * j;
        yprev = yof + sy;
      }
    }
    _rand = 0; (int)random(-2, 6);
    n_els = n_els - _rand;
    //println(rand);
    sy += .2;
  }
}




boolean high_bound(float x, float y, float he) {
  if (y > (he - (-0.000857 * pow((x + 24), 2) + 24))) {
    return true;
  } else {
    return false;
  }
}

boolean low_bound(float x, float y, float he) {
  if (y < (he - (-x * .1 + 12))) {
    return true;
  } else {
    return false;
  }
}


void element(float x, float y) {
  circle_solid(x, y, .05);
  //motorStep(x,y,spd);
}
