#ifndef AbstractPauseable_h
#define AbstractPauseable_h


class AbstractPauseable {

public:
    virtual bool resume() = 0;
    virtual bool stop()   = 0;

};

#endif // AbstractPauseable_h
