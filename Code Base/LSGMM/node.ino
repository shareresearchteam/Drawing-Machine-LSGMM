 /*double xn[n_nodes];
  double yn[n_nodes];
  int    used[n_nodes];

  for (int i = 0; i < n_nodes; i++) {
    xn[i] = randomDouble(25, 125); //i*50+200;
    yn[i] = randomDouble(17, 60); //j*50+200;
    used[i] = 0;
    //ellipse(xn[i], yn[i], 4, 4);
  }


  double scale = .4;
  double n_min = .25;
  double n_max = .75;
  int curn = 0;
  int ncnt = 0;
  while (ncnt < n_nodes - 1) {

    float min_dist = 5000;
    int min_ind = -1;
    for (int k = 0; k < n_nodes; k++) {
      float to_n = sqrt(pow((xn[curn] - xn[k]), 2) + pow((yn[curn] - yn[k]), 2));
      if (to_n < min_dist && k != curn) {
        int flag = 0;
        for (int p = 0; p < n_nodes; p++) {
          if (k == used[p])
            flag = 1;
        }
        if (flag != 1) {
          min_dist = to_n;
          min_ind = k;
        }
      }
    }
    used[ncnt] = curn;

    circle_solid(xn[curn], yn[curn], .07);

    for (int j = 0; j < n_nodes; j++) {
      //Serial.println(sqrt(pow((xn[curn] - xn[j]), 2) + pow((yn[curn] - yn[j]), 2)));
      if (curn != j && sqrt(pow((xn[curn] - xn[j]), 2) + pow((yn[curn] - yn[j]), 2)) < 1.3) {
        bez_con(xn[curn], yn[curn], xn[j], yn[j], n_min, n_max, scale);
        bez_con(xn[j], yn[j], xn[curn], yn[curn], n_min, n_max, scale);
      }
    }
    bez_con(xn[curn], yn[curn], xn[min_ind], yn[min_ind], n_min, n_max, scale);
    ncnt++;
    curn = min_ind;
  }*/
