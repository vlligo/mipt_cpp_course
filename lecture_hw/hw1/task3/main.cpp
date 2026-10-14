#include <cstring>
#include <iomanip>
#include <iostream>

template <int Height, int Width>
void clear(char (&table)[Height][Width]) {
  for (auto& row : table) {
    for (char& cell : row) {
      cell = ' ';
    }
  }
}

template <int Height, int Width>
bool put(char (&table)[Height][Width], int x, int y, char c) {
  if (x < 0 || x >= Width || y < 0 || y >= Height) {
    return false;
  }
  table[y][x] = c;
  return true;
}

template <int Height, int Width>
bool text(char (&table)[Height][Width], int x, int y,
          const char word[]) {
  const auto length = std::strlen(word);
  if (x < 0 || x >= Width || y < 0 || y >= Height) {
    return false;
  }
  if (length == 0 || length > static_cast<std::size_t>(Width - x)) {
    return false;
  }

  for (int i = 0; i < static_cast<int>(length); ++i) {
    put(table, x + i, y, word[i]);
  }
  return true;
}

template <int Height, int Width>
void print(const char (&table)[Height][Width]) {
  for (const auto& row : table) {
    for (char cell : row) {
      std::cout << cell;
    }
    std::cout << std::endl;
  }
}

int main() {
  const int width = 10;
  const int height = 5;
  char table[height][width];
  clear(table);

  char command[32];
  while (std::cin >> command) {
    if (std::strcmp(command, "quit") == 0) {
      break;
    }
    if (std::strcmp(command, "clear") == 0) {
      clear(table);
    } else if (std::strcmp(command, "put") == 0) {
      int x;
      int y;
      char c;
      std::cin >> x >> y >> c;
      if (!put(table, x, y, c)) {
        std::cout << "error" << std::endl;
      }
    } else if (std::strcmp(command, "text") == 0) {
      int x = 0;
      int y = 0;
      char word[width + 2];

      std::cin >> x >> y >> word;
      if (!text(table, x, y, word)) {
        std::cout << "error" << std::endl;
      }
    } else if (std::strcmp(command, "print") == 0) {
      print(table);
    }
  }
  return 0;
}
