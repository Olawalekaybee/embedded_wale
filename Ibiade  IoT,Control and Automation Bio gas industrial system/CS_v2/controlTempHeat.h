#include "Bio_temp.h"

#define Ctrl_h 3
#define sigheat 1

bool T_safeZone[Ctrl_h - 1] = { false,
                                false };
float setHthres[Ctrl_h - 1] = {
  50,
  50
};


int heaters[Ctrl_h] = {
  2,
  4,
  13
};

void set_hdist() {
  // for (int j = 0; j < Ctrl_h; j++) {
  pinMode(heaters[0], OUTPUT);
  digitalWrite(heaters[0], LOW);
  // }
  pinMode(heaters[1], OUTPUT);
  digitalWrite(heaters[1], LOW);

  pinMode(heaters[2], OUTPUT);
  digitalWrite(heaters[2], LOW);
}

void set_Hsafezone(float ha, float hb) {
  setHthres[0] = ha;  // adjusted from firebase
  setHthres[1] = hb;  // adjusted from firebase
  T_safeZone[0] = (Htemp[0] <= setHthres[0]) ? true : false;
  T_safeZone[1] = (Htemp[1] <= setHthres[1]) ? true : false;
}

void heatdistributor(float x, int y, int z) {
  if (((x) > -1) && (T_safeZone[0] == true)) {

    if ((x) < (y)) {

      digitalWrite(heaters[0], HIGH);

    } else if (((x) > (y)) && ((x) < ((z) + 0.8))) {

      digitalWrite(heaters[0], HIGH);


    } else {

      digitalWrite(heaters[0], LOW);
    }
  } else {

    digitalWrite(heaters[0], LOW);
  }
}


void heatdistributor1(float x, int y, int z) {
  if (((x) > -1) && (T_safeZone[1] == true)) {

    if ((x) < (y)) {

      digitalWrite(heaters[1], HIGH);

    } else if (((x) > (y)) && ((x) < ((z) + 0.8))) {

      digitalWrite(heaters[1], HIGH);


    } else {

      digitalWrite(heaters[1], LOW);
    }
  } else {

    digitalWrite(heaters[1], LOW);
  }
}

void heatdistributor2(float x, int z) {
  if ((x) > -1) {

    if ((x) < (z + 2)) {

      digitalWrite(heaters[2], HIGH);

    } else {

      digitalWrite(heaters[2], LOW);
    }
  } else {

    digitalWrite(heaters[2], LOW);
  }
}
