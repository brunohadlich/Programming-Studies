int f3(int p1, int p2) {
  int c = 13;
  int d = 17;
  return c + d + p1 + p2;
}

int f2(int p1, int p2) {
  return f3(p1, p2);
}

int f1() {
  int a = 3;
  int b = 11;
  return a + b + f2(13, 9);
}

int main() {
	f1();
}
