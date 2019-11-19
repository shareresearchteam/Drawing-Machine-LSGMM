void print_menu() {

  Serial.println(       "t = Return Home"                 );
  Serial.println(       "y = star pattern for min step"   );
  Serial.println(       "u = Line at different speeds"    );
  Serial.println(       "i = filled rectangle"            );
  Serial.println(       "o = filled circle"               );
  Serial.println(       "b = lift compensation"           );
  Serial.println(       "a = move left"                   );
  Serial.println(       "s = move down"                   );
  Serial.println(       "w = move up"                     );
  Serial.println(       "d = move right"                  );
  Serial.println(       "= = increase aswd move dist"     );
  Serial.println(       "- = decrease aswd move dist"     );
  Serial.println(       "p = print current position"      );
  Serial.println(       "x = single step RM");
  Serial.println(       "z = single step LM dir 1"        );
  Serial.println(       "x = single step RM dir 1"        );
  Serial.println(       "c = single step LM dir 2"        );
  Serial.println(       "v = single step RM dir 2"        );
  Serial.println(       "m = print menu"                  );
  Serial.println(       "/ = deceleration test"           );
  Serial.println(       "[ = left motor signals"          );


}

void cal_menu() {
  char inChar = '`';
  double incr = .5;
  print_menu();

  while (1) {

    while (Serial.available() == 0)  {}
    inChar = (char)Serial.read();
    switch (inChar) {

      case 't':
        return_home();
        break;

      case 'y':
        Serial.println("Minimum Step, 'q' to quit");
        step_star();
        break;

      case 'u':
        Serial.println("Line at different speeds");
        line_speed();
        break;

      case 'i':
        Serial.println("Filled Rectangle");
        frect(return_X_pos(), return_Y_pos(), 1, 1); //randomDouble(1,3.5), randomDouble(1,3.5));
        break;

      case 'o':
        Serial.println("Filled Circle");
        circle_solid(return_X_pos(), return_Y_pos(), 1);
        break;

      case 'b':
        Serial.println("Lift Compensation");
        down();
        break;

      case 'a':
        motorStep(return_X_pos() - incr, return_Y_pos(), 300);
        break;

      case 's':
        motorStep(return_X_pos(), return_Y_pos() + incr, 300);
        break;

      case 'w':
        motorStep(return_X_pos(), return_Y_pos() - incr, 300);

        break;

      case 'd':
        motorStep(return_X_pos() + incr, return_Y_pos(), 300);
        break;

      case '=':
        incr += .05;
        Serial.println(incr);
        break;

      case '-':
        incr -= .05;
        Serial.println(incr);
        break;

      case 'p':
        Serial.println("-----------");
        printDouble(return_X_pos(), 5);
        printDouble(return_Y_pos(), 5);
        Serial.println("-----------");
        break;

      case 'x':
        //one_step_RM(1);
        motorStep(return_X_pos() + incr, return_Y_pos() + incr, spd);
        break;

      case 'z':
        //one_step_LM(1);
        motorStep(return_X_pos() - incr, return_Y_pos() - incr, spd);
        break;

      case 'v':
        one_step_RM(0);
        break;

      case 'c':
        one_step_LM(0);
        break;

      case 'm':
        print_menu();
        break;

      case '/':
        for (int i = 0; i < 10; i++) {
          motorStep(return_X_pos() + incr, return_Y_pos(), spd);
          motorStep(return_X_pos() - incr, return_Y_pos(), spd);
        }
        break;
      case '[':
        // Serial.println(Etest.read());
        Serial.println(lms);
        Serial.println();
        break;

      case '?':
        for(int i=0; i<5; i++){
          rr();
        }
        break;


        //break;
    }

  }
}


void step_star() {

  int full_steps = 1;
  int _spd = spd * 5;
  char inChar = '`';
  double incr = 15.0;

  while (inChar != 'q') {

    inChar = (char)Serial.read();

    if (inChar == '=') {
      full_steps++;
      Serial.println(full_steps);
    }
    else if (inChar == '-') {
      full_steps--;
      Serial.println(full_steps);
    }

    for (int i = 0; i < (usteps * full_steps); i++) {
      digitalWrite(STEP_PIN_RM, LOW);
      delayMicroseconds(_spd);
      digitalWrite(STEP_PIN_RM, HIGH);
    }
    delay(1000);

    for (int i = 0; i < (usteps * full_steps); i++) {
      digitalWrite(STEP_PIN_LM, LOW);
      delayMicroseconds(_spd);
      digitalWrite(STEP_PIN_LM, HIGH);
    }
    delay(1000);

    for (int i = 0; i < (usteps * full_steps); i++) {
      digitalWrite(STEP_PIN_RM, LOW);
      digitalWrite(STEP_PIN_LM, LOW);
      delayMicroseconds(_spd);
      digitalWrite(STEP_PIN_RM, HIGH);
      digitalWrite(STEP_PIN_LM, HIGH);
    }
    delay(1000);

    for (int i = 0; i < (usteps * full_steps); i++) {
      digitalWrite(STEP_PIN_RM, LOW);
      digitalWrite(STEP_PIN_LM, LOW);
      delayMicroseconds(_spd);
      digitalWrite(STEP_PIN_RM, HIGH);
      digitalWrite(STEP_PIN_LM, HIGH);
    }

    if (inChar == 't') {
      return_home();
      inChar = 'q';
    }

    delay(1000);
  }

}

void line_speed() {

  int _spd = spd;
  char inChar = '`';
  double yl = y_init;

  Serial.print("Current Speed = ");
  Serial.println(_spd);
  while (inChar != 'q') {


    _spd = lineSeg_ser_spd(x_init, yl, x_init + 5, yl, 0, _spd);
    yl += .2;
    _spd = lineSeg_ser_spd(x_init + 5, yl, x_init, yl, 0, _spd);
    yl += .2;

    Serial.println("Continue with another line?");
    while (Serial.available() == 0)  {}
    inChar = (char)Serial.read();

    if (inChar == 't') {
      return_home();
      inChar = 'q';
    }

    delay(1000);
  }

}

void return_home() {
  Serial.println("Returning Home");
  Serial.print(return_X_pos());
  Serial.print("  ");
  Serial.print(return_Y_pos());
  Serial.print("  -->  ");
  Serial.print(x_init);
  Serial.print("  ");
  Serial.println(y_init);
  motorStep(x_init, y_init, spd);
}

void one_step_LM(int dir) {
  if (dir == 0) {
    digitalWrite(DIR_PIN_LM, LOW);
    lms -= 1;
  }
  else if (dir == 1) {
    digitalWrite(DIR_PIN_LM, HIGH);
    lms += 1;
  }

  for (int i = 0; i < (usteps); i++) {
    digitalWrite(STEP_PIN_LM, LOW);
    delay(2);
    digitalWrite(STEP_PIN_LM, HIGH);
  }
}


void one_step_RM(int dir) {

  if (dir == 0) {
    digitalWrite(DIR_PIN_RM, HIGH);
    rms -= 1;
  }
  else if (dir == 1) {
    digitalWrite(DIR_PIN_RM, LOW);
    rms += 1;
  }
  for (int i = 0; i < (usteps); i++) {
    digitalWrite(STEP_PIN_RM, LOW);
    delay(2);
    digitalWrite(STEP_PIN_RM, HIGH);
  }

}

void down() {

  digitalWrite(DIR_PIN_RM, HIGH);
  digitalWrite(DIR_PIN_LM, HIGH);

  for (int i = 0; i < (usteps); i++) {
    digitalWrite(STEP_PIN_RM, LOW);
    digitalWrite(STEP_PIN_LM, LOW);
    delayMicroseconds(1300);
    digitalWrite(STEP_PIN_RM, HIGH);
    digitalWrite(STEP_PIN_LM, HIGH);
  }

}

int lineSeg_ser_spd(double x1, double y1, double x2, double y2, bool lift, int Speed) {

  double m;
  if ((x2 - x1) == 0)
    m = 0;
  else
    m = (y2 - y1) / (x2 - x1);

  double b = y1 - m * x1;

  // if (lift == 1)
  //lift_to(x1, y1);

  if (x1 < x2) {
    for (double x = x1; x < x2; x = x + .005) {
      motorStep(x, m * x + b, Speed);
      Speed = spd_serial(Speed);
    }
  } else if (x1 > x2) {
    for (double x = x1; x > x2; x = x - .005) {
      motorStep(x, m * x + b, Speed);
      Speed = spd_serial(Speed);
    }
  } else if (x2 == x1) {
    if (y1 < y2) {
      for (double y = y1; y < y2; y = y + .005) {
        motorStep(x1, y, Speed);
        Speed = spd_serial(Speed);
      }
    } else if (y2 < y1) {
      for (double y = y1; y > y2; y = y - .005) {
        motorStep(x1, y, Speed);
        Speed = spd_serial(Speed);
      }
    }
  }
  return Speed;
}

int spd_serial(int Speed) {
  int incr = 25;
  char inChar = '`';
  inChar = (char)Serial.read();
  if (inChar == '=') {
    Speed += incr;
    Serial.println(Speed);
  }
  else if (inChar == '-') {
    Speed -= incr;
    Serial.println(Speed);
  }
  return Speed;
}

void decel_drift() {

  int spd_cnt = usteps * 150;
  int __spd = 600;
  for (int j = 0; j < 10; j++) {


    if (j % 2 == 0) {
      digitalWrite(DIR_PIN_RM, LOW);
      digitalWrite(DIR_PIN_LM, LOW);
    }
    else {
      digitalWrite(DIR_PIN_RM, HIGH);
      digitalWrite(DIR_PIN_LM, HIGH);
    }

    for (int i = 0; i < (usteps * 150); i++) {
      digitalWrite(STEP_PIN_RM, LOW);
      digitalWrite(STEP_PIN_LM, LOW);
      delayMicroseconds(__spd * spd_cnt / (usteps * 7));
      digitalWrite(STEP_PIN_RM, HIGH);
      digitalWrite(STEP_PIN_LM, HIGH);

      if (i < (usteps * 150) / 2)
        spd_cnt--;
      else
        spd_cnt++;
    }

  }
}

/*void encoder_cal() {

  // only pull in to avoid slippage - which wouldnt even lead to an accumulation problem, just an offset

  double length_cal = 50;

  double encl_start = enc_left.read();

  digitalWrite(DIR_PIN_LM, HIGH);
  for (int i = 0; i < (usteps * length_cal); i++) {
    digitalWrite(STEP_PIN_LM, LOW);
    delayMicroseconds(500);
    digitalWrite(STEP_PIN_LM, HIGH);
  }
  double encl_end = enc_left.read();

  double encr_start = enc_right.read();
  digitalWrite(DIR_PIN_RM, LOW);
  for (int i = 0; i < (usteps * length_cal); i++) {
    digitalWrite(STEP_PIN_RM, LOW);
    delayMicroseconds(500);
    digitalWrite(STEP_PIN_RM, HIGH);
  }
  double encr_end = enc_right.read();

  double CL = usteps * length_cal / (encl_end - encl_start);  // usteps / pulse
  double CR = usteps * length_cal / (encr_end - encr_start);  // usteps / pulse

  Serial.print("LEFT:   ");
  Serial.println(CL);
  printDouble(CL, 7);

  Serial.print("RIGHT:   ");
  Serial.println(CR);
  printDouble(CR, 7);

  }*/
