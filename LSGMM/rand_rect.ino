

void rr(){

  double x0 = return_X_pos();
  double y0_rand = (double)random(-200,200)/100;
  double y0 = return_Y_pos() + y0_rand;
  double wid = (double)random(0,300)/100;
  double len = (double)random(0,500)/100;
  //Serial.println(wid);
  //Serial.println(len);
  
  double ex_len = -len/(double)random(1,10);
  //lift_to(x0,y0);
  /*motorStep(x0+wid,y0,600);
  motorStep(x0+wid,y0+len,600);
  motorStep(x0,y0+len,600);
  motorStep(x0,y0,600);*/
  lift(1);
  frect(x0,y0,wid, len);
  //circle(x0,y0+ex_len,.03);

 double ex_wid = (double)random(-50,50)/100;

 lift(0);
 motorStep(x0+wid+.2, y0-y0_rand,800);
 //lift_to(x0+wid+.2, y0-y0_rand);
 //lift(0);
 //wid = random(-100,100)/100;
 //rr();
   
}

/*void frect(double xz,double yz,double w, double l){

  double lim = 0;
  double ox;
  double oy;
  if(w>l){
    lim = l/2;
  }
  else{
    lim = w/2;
  }

  for(double p=0; p<lim; p+=.015){
    ox = p;
    oy = p;
    //lift_to(xz+ox,yz+oy);
    motorStep(xz+ox,yz+oy,800);
    motorStep(xz+w-ox,yz+oy,800);
    motorStep(xz+w-ox,yz+l-oy,800);
    motorStep(xz+ox,yz+l-oy,800);
    motorStep(xz+ox,yz+oy,800);  
  }
}*/
