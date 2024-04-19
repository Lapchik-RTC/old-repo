void setup() {
}

double dist(double x1, double y1, double x2, double y2) {
  return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

void loop() {
  int X = analogRead(2);
  int Y = analogRead(3);
  double x1 = -512;
  double y1 = 0;
  double x2 = -512;
  double y2 = 512 * 0.57735026919;
  double x3 = -512 * 0.57735026919;
  double y3 = 512;
  double x4 = 0;
  double y4 = 512;
  double x5 = 512 * 0.57735026919;
  double y5 = 512;
  double x6 = 512;
  double y6 = 512 * 0.57735026919;
  double x7 = 512;
  double y7 = 0;
  double x8 = 512;
  double y8 = -512 * 0.57735026919;
  double x9 = 512 * 0.57735026919;
  double y9 = -512;
  double x10 = 0;
  double y10 = -512;
  double x11 = -512 * 0.57735026919;
  double y11 = -512;
  double x12 = -512;
  double y12 = -512 * 0.57735026919;
  double doubles[]  = {x1, y1, x2, y2, x3, y3, x4, y4, x5, y5, x6, y6, x7, y7, x8, y8, x9, y9, x10, y10, x11, y11, x12, y12};
  if (abs(X) > 50 && abs(Y) > 50) {
    int bestInd = 0;
    double bestDist = dist(X, Y, doubles[0], doubles[1]);
    double nowBD;
    for (int i = 0; i < 12; i++) {
      nowBD = dist(X, Y, doubles[2 * i], doubles[2 * i + 1]);
      if (nowBD < bestDist) {
        bestInd = i;
        bestDist = nowBD;
      }
    }

  } else {
    //motor1(0, 0);
    //motor2(0, 0);
    //motor3(0, 0);
  }
}
