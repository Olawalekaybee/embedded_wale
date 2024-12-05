
#define Ctrl_M 2

#define activate_M 9     // digitalpin
#define activate_M_1 10  // digitalPin

int Isr_t_m[Ctrl_M] = {
  11,
  12
};





void init_isr_m() {
  // for (int p = 0; p < Ctrl_h; p++) {
  pinMode(Isr_t_m[0], INPUT_PULLUP);
  digitalWrite(Isr_t_m[0], LOW);
  pinMode(Isr_t_m[1], INPUT_PULLUP);
  digitalWrite(Isr_t_m[1], LOW);
  // }
}

void setup_M() {
  pinMode(activate_M, OUTPUT);
  digitalWrite(activate_M, LOW);
  pinMode(activate_M_1, OUTPUT);
  digitalWrite(activate_M_1, LOW);
}





void ctrl_Motors(bool m, bool n) {
  bool k = (m == NULL) ? 0 : m;
  bool l = (n == NULL) ? 0 : n;
  if (k) {
    digitalWrite(activate_M, HIGH);
  } else {
    digitalWrite(activate_M, LOW);
  }

  if (l) {
    digitalWrite(activate_M_1, HIGH);
  } else {
    digitalWrite(activate_M_1, LOW);
  }
}
