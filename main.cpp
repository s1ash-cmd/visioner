#include <fstream>
#include <iostream>
#include <string>

using namespace std;

string encrypt(const string &text, const string &key) {
  string result = text;
  int key_length = key.length();
  int key_index = 0;

  for (int i = 0; i < text.length(); ++i) {
    if (isalpha(text[i])) {
      char base = isupper(text[i]) ? 'A' : 'a';
      result[i] =
          ((text[i] - base + (toupper(key[key_index]) - 'A')) % 26) + base;
      key_index = (key_index + 1) % key_length;
    }
  }
  return result;
}

string decrypt(const string &text, const string &key) {
  string result = text;
  int key_length = key.length();
  int key_index = 0;

  for (int i = 0; i < text.length(); ++i) {
    if (isalpha(text[i])) {
      char base = isupper(text[i]) ? 'A' : 'a';
      result[i] =
          ((text[i] - base - (toupper(key[key_index]) - 'A') + 26) % 26) + base;
      key_index = (key_index + 1) % key_length;
    }
  }
  return result;
}

string readFromFile(const string &filename) {
  ifstream file(filename);
  if (!file) {
    throw runtime_error("Ошибка при открытии файла");
  }
  return string((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
}

void writeToFile(const string &filename, const string &content) {
  ofstream file(filename);
  if (!file) {
    throw runtime_error("Ошибка при открытии файла");
  }
  file << content;
}

template <typename T> T check_input(T min, T max) {
  T x;
  while ((cin >> x).fail() || (cin).peek() != '\n' || x < min || x > max) {
    cin.clear();
    cin.ignore(10000, '\n');
    cout << "\nВведите корректное значение (" << min << " - " << max << ") ";
  }
  return x;
}

bool check_key(const string &key) {
  for (char c : key) {
    if (!isalpha(c)) {
      cout << "Ключ шифрования содержит недопустимые символы" << endl;
      return false;
    }
  }
  return true;
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

    string inputFile, outputFile, key;

    switch (menu_item) {
    case 1: {
      cout << "Введите имя входного файла для шифрования: ";
      cin >> inputFile;

      cout << "Введите имя выходного файла для зашифрованных данных: ";
      cin >> outputFile;

      cout << "Введите ключ шифрования: ";
      cin >> key;

      if (!check_key(key)) {
        continue;
      }

      try {
        string content = readFromFile(inputFile);
        string result = encrypt(content, key);

        writeToFile(outputFile, result);

        cout << "Данные успешно зашифрованы и записаны в " << outputFile
             << endl;
      } catch (const exception &e) {
        cerr << "Ошибка при шифровании: " << e.what() << endl;
      }
      break;
    }
    case 2: {
      cout << "Введите имя входного файла для расшифровки: ";
      cin >> inputFile;

      cout << "Введите имя выходного файла для расшифрованных данных: ";
      cin >> outputFile;

      cout << "Введите ключ расшифровки: ";
      cin >> key;

      if (!check_key(key)) {
        continue;
      }

      try {
        string content = readFromFile(inputFile);
        string result = decrypt(content, key);

        writeToFile(outputFile, result);

        cout << "Данные успешно расшифрованы и записаны в " << outputFile
             << endl;
      } catch (const exception &e) {
        cerr << "Ошибка при расшифровке: " << e.what() << endl;
      }
      break;
    }
    case 0: {
      exit(0);
      return 0;
    }
    }
  }
  return 0;
}
