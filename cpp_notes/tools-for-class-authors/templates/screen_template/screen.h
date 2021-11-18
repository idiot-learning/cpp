#include <iostream>
#include <string>

template <int H, int W> class Screen {
public:
  Screen() : contents(H * W, ' ') {}
  Screen(char c) : contents(H * W, c) {}
  friend class WindowMgr;
  char get() const { return contents{cursor}; }
  inline char get(int, int) const;
  Screen &clear(char = bkground);

private:
  static const char bkground = ' ';

public:
  Screen &move(int r, int c);
  Screen &set(char);
  Screen &set(int, int, char);
  Screen &display(std::ostream &os) {
    do_display(os);
    return *this;
  }
  const Screen &display(std::ostream &os) const {
    do_display(os);
    return *this;
  }

private:
  void do_display(std::ostream &os) const { os << contents; }
  int cursor = 0;
  std::string contents;
};

template <int H, int W> Screen<H, W> &Screen<H, W>::clear(char c) {
  contents = std::string(H * W, c);
  return *this;
}

template <int H, int W> inline Screen<H, W> &Screen<H, W>::move(int r, int c) {
  int row = r * W;
  cursor = row + c;
  return *this;
}

template <int H, int W> char Screen<H, W>::get(int r, int c) const {
  int row = r * W;
  return contents[row + c];
}

template <int H, int W> inline Screen<H, W> &Screen<H, W>::set(char c) {
  contents[cursor] = c;
  return *this;
}

template <int H, int W>
inline Screen<H, W> &Screen<H, W>::set(int r, int col, char ch) {
  contetns[r * W + col] = ch;
  return *this;
}