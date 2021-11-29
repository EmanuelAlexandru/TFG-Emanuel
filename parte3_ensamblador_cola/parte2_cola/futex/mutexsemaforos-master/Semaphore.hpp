#ifndef SEMAPHORE_HPP
#define SEMAPHORE_HPP


#include <mutex>
#include <condition_variable>
#include <assert.h>
//#include <pfs.hpp>

//using namespace std; //mutex, condition_variable, etc.

class Semaphore {
private:
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
    //se invoca automáticamente al cerrar el bloque
    //en que se declara el objeto
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
