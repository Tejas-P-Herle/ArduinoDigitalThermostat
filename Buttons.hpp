
#define btnCount 2

typedef void (*voidFunction) (void *obj);

class Buttons {
  public:
    Buttons(int *buttonPins);
    void initialize();
    void checkAll();
    void setCallback(int buttonNo, voidFunction callback, void *obj);
  private:
    void (*callbacks[btnCount]) (void *obj);
    void *callbackObjs[btnCount];
    int count = btnCount;
    int *pins;
    int lockedBtns[btnCount] = {0};
};
