#ifndef INPUT_H
#define INPUT_H

class Input {
 private:
  bool up;
  bool down;
  bool left;
  bool right;
  bool space;

 public:
  bool getUp() const;
  bool getDown() const;
  bool getLeft() const;
  bool getRight() const;
  bool getSpace() const;
  void update();
  
};


#endif

