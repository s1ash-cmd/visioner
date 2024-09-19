#include <iostream>

using namespace std;

template <typename T> T check_input(T min, T max) {
  T x;
  while ((cin >> x).fail() || (cin).peek() != '\n' || x < min || x > max) {
    cin.clear();
    cin.ignore(10000, '\n');
    cout << "\nВведите корректное значение (" << min << " - " << max << ") ";
  }
  return x;
}

int main() {

  for (;;) {
    cout << "\n_____меню_____" << endl;
    cout << "\n1) Зашифровать данные" << endl;
    cout << "2) Расшифровать данные" << endl;
    cout << "0) Выход" << endl;
    cout << "===============================" << endl;
    cout << "Выберите пункт меню: ";

    int menu_item = check_input(0, 2);

    switch (menu_item) {
    case 1: {
      break;
    }
    case 2: {

      break;
    }
    case 0: {
      exit(0);
    }
    }
  }
  return 0;
}
