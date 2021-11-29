#ifndef PFS_HPP
#define PFS_HPP

class mutex
{
  private:
    char type = 'n'; //s, n, K
    int mi_mutex=0; // mutex para utilizar con las funciones definidas en ensamblador
  public:
  mutex();
  ~mutex();
    void lock();
    void unlock();
    void setMutexType(char &c);
  private:
};

#endif
