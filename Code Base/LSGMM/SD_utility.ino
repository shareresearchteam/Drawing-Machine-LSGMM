void SD_run() {

  double scale_factor = 120; //260 230
  double offsetx = 30;
  double offsety = 38;
  double x_c = 29;         //starting place
  double y_c = 21.331;
  char inChar = 't';
  /*
    while (inChar != '#') {
      inChar = 't';
      lift(0);
      motorStep(offsetx, offsety, 75);
      while (Serial.available() == 0)  {}
      inChar = (char)Serial.read();
      Serial.println(inChar);
      if (inChar == ',') offsetx -= 1;
      else if (inChar == '.') offsetx += 1;
    }
    inChar = 't';

    Serial.println(offsetx);


    while (inChar != '#') {
      inChar = 't';
      lift(0);
      motorStep(offsetx, offsety, 75);
      while (Serial.available() == 0)  {}
      inChar = (char)Serial.read();
      Serial.println(inChar);
      if (inChar == ',') offsety -= 1;
      else if (inChar == '.') offsety += 1;
    }
    Serial.println(offsety);
  */
  //lift(0);
  //motorStep(offsetx+492/scale_factor,offsety, 75);delay(4000);

  //lift(0);
  //motorStep(offsetx+492/scale_factor,offsety + 717/scale_factor, 75); delay(4000);


  if (!SD.begin(BUILTIN_SDCARD)) {
    Serial.println("initialization failed!");
    while (1);
  }

  //char file_name[11];

  // for (int j = 1; j <= 54; j++) {

  //sprintf(file_name, "leaf_%d.txt", j);
  //myFile = SD.open(file_name);
  myFile = SD.open("face1.txt");
  // Serial.println(file_name);


  /*if (j == 5) {
    lift(0);
    inChar = 't';
    Serial.println("Change Pen");
    while (inChar != '#') {
      inChar = 't';
      while (Serial.available() == 0)  {}
      inChar = (char)Serial.read();
      Serial.println(inChar);
    }
    Serial.println("Continuning w/ wm19.txt");
    }*/

  if (myFile) {
    while (myFile.available()) {
      SD_cr();
      Serial.print(SD_x);
      Serial.print("  ");
      Serial.println(SD_y);
      SD_x /=  scale_factor;
      SD_y /=  scale_factor;
      SD_x +=  offsetx;
      SD_y +=  offsety;
      //     Serial.print(SD_x);
      //     Serial.print("  ");
      //    Serial.println(SD_y);
      if (sqrt(pow(x_c - SD_x, 2) + pow(y_c - SD_y, 2)) > .1) {
        lift_to(SD_x, SD_y);
        delay(200);
        /*delay(20);
        lift(0);
        delay(20);
        motorStep(SD_x, SD_y, 350);
        delay(20);
        lift(1);
        delay(20);
        circle_solid(SD_x, SD_y, .03);*/

      }
      else {
        motorStep(SD_x, SD_y, 800);
       // circle_solid(SD_x, SD_y, .03);

      }
      x_c = SD_x;
      y_c = SD_y;
    }
    myFile.close();
  }
  //offsetx+=7;
  //}
}


void SD_cr() {

  int xin[5] = { -1, -1, -1, -1, -1};
  int yin[5] = { -1, -1, -1, -1, -1};

  for (int i = 0; i < 5; i++) {
    xin[i] = myFile.read() - 48;
    if (xin[i] == (10 - 48)) {
      xin[i] = -1;
      i = 5;
    }
  }

  for (int i = 0; i < 5; i++) {
    yin[i] = myFile.read() - 48;
    if (yin[i] == (10 - 48)) {
      yin[i] = -1;
      i = 5;
    }
  }

  int x = 0;
  int y = 0;


  if (xin[1] < 0 && xin[2] < 0 && xin[3] < 0) x = xin[0];
  else if (xin[1] >= 0 && xin[2] < 0 && xin[3] < 0) x = xin[0] * 10 + xin[1];
  else if (xin[1] >= 0 && xin[2] >= 0 && xin[3] < 0) x = xin[0] * 100 + xin[1] * 10 + xin[2];
  else if (xin[1] >= 0 && xin[2] >= 0 && xin[3] >= 0) x = xin[0] * 1000 + xin[1] * 100 + xin[2] * 10 + xin[3];

  if (yin[1] < 0 && yin[2] < 0 && yin[3] < 0) y = yin[0];
  else if (yin[1] >= 0 && yin[2] < 0 && yin[3] < 0) y = yin[0] * 10 + yin[1];
  else if (yin[1] >= 0 && yin[2] >= 0 && yin[3] < 0) y = yin[0] * 100 + yin[1] * 10 + yin[2];
  else if (yin[1] >= 0 && yin[2] >= 0 && yin[3] >= 0) y = yin[0] * 1000 + yin[1] * 100 + yin[2] * 10 + yin[3];


  SD_x = x;
  SD_y = y;
}
