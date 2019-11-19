#include <TMC2130Stepper.h>
#include <Gaussian.h>
#include <HX711.h>
#include <SD.h>
#include <SPI.h>
#include <Servo.h>

//#include <Encoder.h>

#define unit_num_1 1
#define unit_num_2 0
#define unit_num_3 0

// Motor Driver SPI Pins
// RM = Right Motor, LM = Left Motor
#if unit_num_1
#define DIR_PIN_RM     6
#define STEP_PIN_RM    5
#define CS_PIN_RM      4
#define DIR_PIN_LM     25
#define STEP_PIN_LM    24
#define CS_PIN_LM      2
#elif unit_num_2
#define DIR_PIN_RM     2
#define STEP_PIN_RM    1
#define CS_PIN_RM      8
#define DIR_PIN_LM     19
#define STEP_PIN_LM    20
#define CS_PIN_LM      7
#elif unit_num_3
#define DIR_PIN_RM     9
#define STEP_PIN_RM    8
#define CS_PIN_RM      7
#define DIR_PIN_LM     6
#define STEP_PIN_LM    5
#define CS_PIN_LM      4
#endif

// Enable pins grounded on both drivers, 19 is arbitrary
#define EN_PIN        17

#define DOUT1  33
#define CLK1  34
#define DOUT2  51
#define CLK2  52
const long LOADCELL_OFFSET  =  10682624;
const long LOADCELL_DIVIDER =  5895655;
HX711 loadCell_1;
HX711 loadCell_2;
Servo servo1;

//Encoder enc_left(19, 18);
//Encoder enc_right(20, 21);

#define usteps        256

// Initial Conditions (inches):
//************************************************
#define LM_initial_length     50//86//95
#define RM_initial_length     50//86//95
#define seperation_distance   60//162//186
#define step_rate_lm          (.0314159 * 0.75) // (radians/fullstep) * radius = arclength/fullstep
#define step_rate_rm          (.0314159 * 0.75) // corresponds to amount of string released per full step
// ***********************************************

#define spd  500  // Minimum microsecond delay between usteps, should be changed when usteps is changed

TMC2130Stepper driver1 = TMC2130Stepper(EN_PIN, DIR_PIN_LM, STEP_PIN_LM, CS_PIN_LM);
TMC2130Stepper driver2 = TMC2130Stepper(EN_PIN, DIR_PIN_RM, STEP_PIN_RM, CS_PIN_RM);

long lms = 0;  // Global variable that stores left motor string length in usteps
long lmss = 0;
long lmf = 0;  // Global variable that stores left motor encoder pulses converted to usteps
long rms = 0;  // Global variable that stores right motor string length in usteps
long ll_init;  // Global variable that stores initial left motor string length in usteps
long lr_init;  // Global variable that stores initial right motor string length in usteps

double x_init; // Global variable that stores initial cartesian x-coordinate in inches
double y_init; // Global variable that stores initial cartesian y-coordinate in inches

int ang_max = 160;
int ang_min = 150;

double SD_x = 0;
double SD_y = 0;

double sdx_prev = 0;
double sdy_prev = 0;

// Number of nodes in node bezier algorithm
#define n_nodes   2300
#define max_n  200
Gaussian myGaussian(85, 27);  // Initialize Gaussian RV -> (mean, variance)

File myFile;

void setup() {

  Serial.begin(19200);

  SPI.begin();
  pinMode(MISO, INPUT_PULLUP);

  driver1.begin();            // Initiate pins and registeries
  driver1.rms_current(450);   // Set stepper current
  driver1.stealthChop(1);     // Enable extremely quiet stepping
  driver2.begin();            // Initiate pins and registeries
  driver2.rms_current(450);   // Set stepper current to
  driver2.stealthChop(1);     // Enable extremely quiet stepping

  driver1.microsteps(usteps);
  driver1.interpolate(0);
  driver2.microsteps(usteps);
  driver2.interpolate(0);

  /*loadCell_1.begin(DOUT1, CLK1);
    loadCell_1.set_scale(LOADCELL_DIVIDER);
    loadCell_1.set_offset(LOADCELL_OFFSET);
    loadCell_1.tare();

    loadCell_2.begin(DOUT2, CLK2);
    loadCell_2.set_scale(LOADCELL_DIVIDER);
    loadCell_2.set_offset(LOADCELL_OFFSET);
    loadCell_2.tare();*/
//delay(5000);
  servo1.attach(23);
  lift(1);

  x_init = return_X_pos();
  y_init = return_Y_pos();
  ll_init = round(LM_initial_length / (step_rate_lm / usteps));
  lr_init = round(RM_initial_length / (step_rate_rm / usteps));


  /*Serial.print("Initializing SD card...");
    if (!SD.begin(BUILTIN_SDCARD)) {
    Serial.println("initialization failed!");
    //while(1){} // prevent from progressing if no SD card
    }
    Serial.println("initialization done.");*/

  //***********************************************


  //pinMode(23, OUTPUT);
  //analogWriteFrequency(23, 20000);
  //analogWrite(23, 39);
  //encoder_cal();
  //cal_menu();
  SD_run();
  //cal_menu();
  //bez_node();
  //ws();            // ----------------------> DAY ONE DRAWING
  //string2();      // ----------------------> DAY TWO DRAWING

  /*double is = return_X_pos()-3.5;
    double js = return_Y_pos();

    for (double i = is; i < is+7; i+=.05) {
      for (double j = js; j < js+4; j+=.05) {

      rect2(i, j, .05, .05)  ;

      }
    }*/


  //Serial.println(1 + 4 * (double)max(min(loadCell_2.get_units() * 6, 1), 0));

}

void loop() {
  // delay(35);
  // Serial.println(enc_right.read());
}

// Function that returns the number of steps needed for the left motor to reach
// the input coordinates (x,y) from current pen positions.  A negative step number
// corresponds to string retraction, while positive is extension.
long position_Request_LM(double x, double y) {
  long stepNum_LM;        // Relative length in steps
  double desiredLength;   // Absolute length in inches
  long desiredSteps;      // Absolute length in usteps
  desiredLength = x / (cos(atan(y / x)));  // Coordinate Transform from cartesian to left length
  desiredSteps = round(desiredLength / (step_rate_lm / usteps));
  stepNum_LM = desiredSteps - (lms + ll_init);
  return stepNum_LM;
}

// Function that returns the number of steps needed for the right motor to reach
// the input coordinates (x,y) from current pen positions.  A negative step number
// corresponds to string retraction, while positive is extension.
long position_Request_RM(double x, double y) {
  long stepNum_RM;        // Relative length in steps
  double desiredLength;   // Absolute length in inches
  long desiredSteps;      // Absolute length in usteps
  desiredLength = y / (sin(atan(-y / (x - seperation_distance))));  // Coordinate Transform from cartesian to right length
  desiredSteps = round(desiredLength / (step_rate_rm / usteps));
  stepNum_RM = desiredSteps - (rms + lr_init);
  return stepNum_RM;
}

// Function that adjusts timing such that both motors stop moving at the same time.
// Direction and step instructions are then sent to the motor drivers.  Due to the
// coordinate system, linear motion does not occur by calling this function.
void motorStep(double x, double y, double stepSpeed) {

  //lmf = round((double)enc_left.read()*2.0*3.14159265*.51/2400.0 / (step_rate_lm / usteps));  // convert enoder pulses to drive spool micro steps
  //long lme = lms - lmf; // error signal

  /*Serial.println(lms);
    Serial.println(lmf);
    Serial.println(lme);
    Serial.println();*/

  //lms = -round((double)enc_left.read()  * 19.5);
  //rms = -round((double)enc_right.read() * 19.5);

  long stepNum_RM = position_Request_RM(x, y); //refresh stepNum_RM
  long stepNum_LM = position_Request_LM(x, y); //refresh stepNum_LM

  rms += stepNum_RM;  // update global length variables
  //lmss += stepNum_LM;
  lms += stepNum_LM;


  //printDouble(return_X_pos(), 3);
  //printDouble(return_Y_pos(), 3);

  /*Serial.println(lms);
    Serial.println(stepNum_LM);
    Serial.println(return_X_pos());
    Serial.println(return_Y_pos());
    Serial.println("");/*


    Serial.println(lms);
    Serial.println(stepNum_LM);
    Serial.println(return_X_pos());
    Serial.println(return_Y_pos());
    Serial.println("");*/

  //Serial.println(enc_left.read());


  if (stepNum_LM < 0) {
    digitalWrite(DIR_PIN_LM, LOW);
    stepNum_LM = stepNum_LM * -1;
  }
  else
    digitalWrite(DIR_PIN_LM, HIGH);

  if (stepNum_RM < 0) {
    digitalWrite(DIR_PIN_RM, HIGH);
    stepNum_RM = stepNum_RM * -1;
  }
  else
    digitalWrite(DIR_PIN_RM, LOW);


  unsigned long previousMillis1 = 0;
  unsigned long previousMillis2 = 0;
  unsigned long currentMillis;

  double setSpeed_adjusted1 = stepSpeed;
  double setSpeed_adjusted2 = stepSpeed;

  long count_RM = 0;
  long count_LM = 0;

  // The motor that has a larger amount of steps gets a longer amount of time
  //    between steps.  The minimum speed always remains spd (define statement)
  if (stepNum_LM > stepNum_RM) {
    setSpeed_adjusted1 = ((double)stepNum_LM / (double)stepNum_RM) * stepSpeed;
    setSpeed_adjusted2 = stepSpeed;
  }
  else if (stepNum_LM < stepNum_RM) {
    setSpeed_adjusted1 = stepSpeed;
    setSpeed_adjusted2 = ((double)stepNum_RM / (double)stepNum_LM) * stepSpeed;
  }


  // send commands to driver modules in asychnrnous timing scheme
  while (count_RM < stepNum_RM || count_LM < stepNum_LM) {
    currentMillis = micros();

    if ((currentMillis - previousMillis1 >= setSpeed_adjusted1) && count_RM < stepNum_RM) {
      digitalWrite(STEP_PIN_RM, LOW);
      previousMillis1 = currentMillis;
      count_RM++;
    }
    digitalWrite(STEP_PIN_RM, HIGH);

    currentMillis = micros();

    if ((currentMillis - previousMillis2 >= setSpeed_adjusted2) && count_LM < stepNum_LM) {
      digitalWrite(STEP_PIN_LM, LOW);
      previousMillis2 = currentMillis;
      count_LM++;
    }
    digitalWrite(STEP_PIN_LM, HIGH);


  }

  //lms = -round((double)enc_left.read()  * 19.5);
  //rms = -round((double)enc_right.read() * 19.5);

  //Serial.println(lmss - lms);
  //rms = rms - (lmss-lms);
  //lmss=lms;
}

// This functions performs an inverse coordinate transform on the global
// length variables to extract cartesian X position
double return_X_pos() {
  double l1 = (double)lms * step_rate_lm / usteps + LM_initial_length;
  double l2 = (double)rms * step_rate_rm / usteps + RM_initial_length;
  double x = (l1 * l1 - l2 * l2 + pow(seperation_distance, 2)) / (2 * seperation_distance);
  return x;
}

// This functions performs an inverse coordinate transform on the global
// length variables to extract cartesian Y position
double return_Y_pos() {
  double l1 = (double)lms * step_rate_lm / usteps + LM_initial_length;
  double x = return_X_pos();
  double y = sqrt(l1 * l1 - x * x);
  return y;
}

void sd_test() {

  //for (int k = 0; k < 10; k++) {
  myFile = SD.open("te.txt", FILE_WRITE);

  // if the file opened okay, write to it:
  if (myFile) {
    Serial.print("Writing to te.txt...");
    myFile.println("testing hi hi hi 1, 2, 3.");
    // close the file:
    myFile.close();
    Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }

  // re-open the file for reading:
  myFile = SD.open("te.txt");
  if (myFile) {
    Serial.println("te.txt:");

    // read from the file until there's nothing else in it:
    while (myFile.available()) {
      Serial.write(myFile.read());
    }
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening te.txt");
  }
  // }
}
