#ifndef SEMAPHORE_HPP
#define SEMAPHORE_HPP


#include <mutex>
#include <condition_variable>
#include <assert.h>
//#include <pfs.hpp>

//using namespace std; //mutex, condition_variable, etc.

class Semaphore {
private:
//	mipthread_mutex_t mi_mutex;
//    char MUTEX_IMPLE = 's';   // Seleccion de implmetaciÃ³n de mutex con futex: s, spinlock; n, naive; y K, Kdrepper 
    std::mutex mtx;       
    std::condition_variable_any cv;
    int count;                    
    bool initialized;          
    int print = 1; // imprimir una vez el tipo de mutex para asegurarme de que uso el correcto


public:
	//------------------------- constructores
    //Pre:
    //Post: NOT initialized
    Semaphore();

    //Pre: n>=0
    //Post: count=n AND initialized
    Semaphore(int n);

    //------------------------- destructor
    ~Semaphore();

    //Pre: n>=0 AND NOT initialized
    //Post: initialized AND count=n
    void setInitValue(int n, char &c);
    //------------------------- operaciones estándar
    //Pre: initialized
    //Post: <count++>
    void signal();

    //Pre: initialized
    //Post: <await count>0 
    //          count-- 
    //      >
    void wait();

    //------------------------- operaciones extendidas
    //Pre: n>0 AND initialized
    //Post: <count=count+n>
    void signal(int n);

    //Pre: n>0 AND initialized
    //Post: <await count>=n 
    //          count = count-n
    //      >
    void wait(int n);

};

#endif 
