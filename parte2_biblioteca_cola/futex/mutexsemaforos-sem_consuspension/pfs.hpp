#ifndef PFS_HPP
#define PFS_HPP

class mutex
{
  private:
    volatile char interlock;
    char type = 'n'; //s, n, K
    int print = 1;
  public:
  mutex();
  ~mutex();
    void lock();
    void unlock();
    void setMutexType(char &c);
  private:
};

#endif
