/* Sudo Code

  Define n as the number of concentric circles centered on xc, yc with r
  as the current radius and theta as 2nd coordinate of pen
  
  while current_circle < n{

    take windowed average of previous 50 (radius, theta) points, can wrap
    subtract windowed average from next radius point
    sample load cell sensor, subtract scaled value
    save radius information for next averageing action

  }

*/
void ws() {
  //ws(double xOf, double yOf, double radius_init)
#define circ_res  1000

  double xOf = x_init - 31;
  double yOf = 28+15;//y_init + 15;
  double radius_init =  4;

  for (int i = 0; i < 8; i++) {
    // ws(xOf + i, yOf, 3);

    // Declare history of circle radius and discrete angles
    double circPtsR[circ_res] ;
    double circPtsRn[circ_res];

    double x, y;
    double r = radius_init;
    double x_prev = xOf + r;
    double y_prev = yOf;
    double wig = 0; // boost section of initial circle for smooth testing
    double theta = 0;
    double theta_incr = (2 * PI / circ_res);
    long prev_touch = 0;

    for (int i = 0; i < circ_res; i++) {

      if (theta > .9 && theta < .5) {
        circPtsR[i] = (r - wig);
        x = xOf  + (r - wig) * cos(theta);
        y = yOf  + (r - wig) * sin(theta);
        lineSeg(x_prev, y_prev, x, y, 0, spd);
        x_prev = x;
        y_prev = y;
      } else {
        circPtsR[i] = r;
        x = xOf  + r * cos(theta);
        y = yOf  + r * sin(theta);
        //Serial.print(x);
        //Serial.print("  ");
        //Serial.println(y);
        lineSeg(x_prev, y_prev, x, y, 0, spd);
        x_prev = x;
        y_prev = y;
      }
      theta += theta_incr;
    }

    double r_incr = .02;
    double wind = 50;
    double mv_avg = 0;
    double r_boost = 0;
    double ru=0; 
    double r_boost_filt = 0;
    int flag = 0;
    double j_wrapped = 0;
    double speed_sense = 1;

    for (int k = 0; k < 1; k++) {
      myFile = SD.open("d1.txt", FILE_WRITE);
      wind = 50;///random(10,200);
      flag = 0;
      for (double i = 0; i < circ_res; i++) {
        mv_avg = 0;
        for (double j = i - wind / 2.0; j <= i + wind / 2.0; j++) {
          if (j < 0) {
            j_wrapped = circ_res + j;
            mv_avg += circPtsR[(int)j_wrapped];
          } else if (j >= circ_res) {
            j_wrapped = j - circ_res;
            mv_avg += circPtsR[(int)j_wrapped];
          } else {
            mv_avg += circPtsR[(int)j];
          }
        }
        mv_avg = mv_avg / (wind + 1);
        r_boost = -r_incr + mv_avg;
        //r_boost -= (double)map(analogRead(A14),0,1023,0,400)/1000.0;
        ru = (double)max(min(loadCell_1.get_units() * 2, .2), 0);;
        //r_boost -= (double)max(min(loadCell_1.get_units() * 2, .2), 0);
        r_boost_filt = r_boost_filt * .9 + ru * .1;
        r_boost -= r_boost_filt;
        speed_sense = 1 + 4 * (double)max(min(loadCell_2.get_units() * 6, 1), 0);

        if (myFile) {
          if ((r_boost > .03 || speed_sense > 1.1) && ((millis() - prev_touch)>2500)) {
            myFile.println(millis());
            myFile.println(r_boost);
            myFile.println(speed_sense);
            prev_touch = millis();
          }
        }
        else {
          Serial.println("Write Error");
        }


        /* if (flag == 0) {
           println(mv_avg);
           flag = 1;
          } */

        double dist = circPtsR[(int)i] - r_boost;
        if (dist <= 0) {
          r_boost -= (abs(dist) + .02);
        }


        if (i == 0 && k == 0) {
          x_prev = xOf  + r_boost;
          y_prev = yOf;
        }

        lineSeg(x_prev, y_prev, xOf  + r_boost * cos(i * theta_incr), yOf  + r_boost * sin(i * theta_incr), 0, spd * speed_sense);
        x_prev = xOf  + r_boost * cos(i * theta_incr);
        y_prev = yOf  + r_boost * sin(i * theta_incr);
        circPtsRn[(int)i] =  r_boost;
      }
      for (int p = 0; p < circ_res; p++) {
        circPtsR[p] =  circPtsRn[p];
      }
      myFile.close();
      myFile = SD.open("in.txt");
      if (myFile) {
        Serial.println("in.txt:");

        // read from the file until there's nothing else in it:
        while (myFile.available()) {
          Serial.write(myFile.read());
        }
        // close the file:
        myFile.close();
      } else {
        // if the file didn't open, print an error:
        Serial.println("error opening in.txt");
      }
    }

    xOf = xOf + 9;

  }

}
