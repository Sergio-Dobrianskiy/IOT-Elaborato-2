#ifndef __PRESENCE__
#define __PRESENCE__

class PresenceSensor {
public:
    virtual bool isDetected() = 0;
    virtual void sync() = 0;
    virtual long getLastSyncTime() = 0;

protected:
    virtual void updateSyncTime(long time);
};

#endif