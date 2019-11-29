
//x: 38   ->   72
//y: 38   ->   66

void string() {

  double xof = x_init;// - 30; //38;
  double yof = y_init;// + 15; //38;
  int curn = 0;
  int dir = -1;
  int p = 0;

  double xn[max_n];
  double yn[max_n];

  double scale =  1.4;
  double n_min = .1;
  double n_max = .9;

  double s1 = 0;
  double s2 = 0;

  unsigned long prev_time = millis();
  unsigned long t2press = 0;

  double time_move = 0;

  xn[0] = xof;
  yn[0] = yof;
  for (int i = 1; i < max_n; i++) {
    xn[i] = 0;
    yn[i] = 0;
  }
  element(xn[curn], yn[curn]);

  while (1) { // (yn[curn] < 66 && xn[curn] < 72) {


    s1 = (double)max(min(loadCell_1.get_units() * 2, .2), 0);
    s2 = 1 + 4 * (double)max(min(loadCell_2.get_units() * 6, 1), 0);    

    if(s2 > 1.1){
      myFile = SD.open("d2.txt", FILE_WRITE);
      myFile.println(millis());
      myFile.println("s2");      
      myFile.println(s2);
      myFile.close();      
    }

    if (s1 > .05 ) {
      myFile = SD.open("d2.txt", FILE_WRITE);
      myFile.println(millis());
      myFile.println("s1");      
      myFile.println(s1);
      myFile.close();

      t2press = millis() - prev_time;
      prev_time = millis();
      time_move = min(t2press*.2/(5*60*1000),1.5); // .2 inches per 5 minutes
      
      xn[curn + 1] = xn[curn] + .4 + time_move;//randomDouble(.3, .5);
      yn[curn + 1] = yn[curn];// + randomDouble(.1, -.1);
      //bez_con_sense(return_X_pos(), return_Y_pos(), xn[curn + 1], yn[curn + 1], n_min, n_max, 1.2, 3*PI/2, 0);
      lineSeg(return_X_pos(), return_Y_pos(), return_X_pos() + .1, yof - .3, 0, spd);
      lineSeg(return_X_pos(), return_Y_pos(), xn[curn + 1] - .1, yof - .3, 0, spd);
      lineSeg(return_X_pos(), return_Y_pos(), xn[curn + 1], yn[curn + 1], 0, spd);
      element(xn[curn + 1], yn[curn + 1]);
      curn++;
      p = 0;
      dir = -1;
    }


    if (curn > 0) {

      Serial.println(curn + p);
      Serial.println(curn + p + dir);
      Serial.println();

      bez_con_sense(xn[curn + p], yn[curn + p] + .05, xn[curn + p + dir], yn[curn + p + dir] + .05, n_min, n_max, scale, PI / 2, 1);

      if (dir == -1) {
        p -= 1;
      }
      else if (dir == 1) {
        p += 1;
      }
      if ((curn + (p + 1) + dir) == 0) {
        dir = 1;
      }
      else if ((curn + (p - 1) + dir) == curn) {
        dir = -1;
      }
    }


  }


}
