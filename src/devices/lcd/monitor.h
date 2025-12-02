#ifndef __MONITOR__
#define __MONITOR__

class Monitor {
public:
    virtual void switchOn() = 0;
    virtual void switchOff() = 0;
    virtual void show(String str1, String str2) = 0;
};

#endif