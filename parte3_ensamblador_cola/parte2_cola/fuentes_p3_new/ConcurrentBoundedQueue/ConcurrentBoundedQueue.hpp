#ifndef CONCURRENT_BOUNDED_QUEUE
#define CONCURRENT_BOUNDED_QUEUE

#include <Semaphore.hpp>
#include <Logger.hpp>
#include <BoundedQueue.hpp>

using namespace std;

//-----------------------------------------------------
//  Compilación condicional: ¿quiero hacer "logging"?
#ifdef LOGGING_MODE
    #include <Logger.hpp>
    extern Logger logger;
    #define ADD_EVENT(e) {logger.addMessage(e);}  //generar evento
#else
    #define ADD_EVENT(e)  // nada
#endif
//-----------------------------------------------------

template <class T>
class ConcurrentBoundedQueue {
public:
    //-----------------------------------------------------
    //Pre:  0<N
    //Post: this->bq=< > AND #this=N AND this->log=nullptr
    //Com:  constructor

    ConcurrentBoundedQueue(const int N, char &c);
    //-----------------------------------------------------
    //Pre:
    //Post:
    //Com:  destructor
    ~ConcurrentBoundedQueue();

    //-----------------------------------------------------
    //Pre:  
    //Post: this->bq=<>
    void empty();

    //-----------------------------------------------------
    //Pre:  this->bq=< d_1 ... d_n >
    //Post: this->bq=< d_1 ... d_n d > 
    //Coms: se bloquea hasta que haya un hueco para insertar el dato
    void enqueue(int i);

    //-----------------------------------------------------
    //Pre:  this->bq=< d_1 ... d_n> and n>0
    //Post: this->bq=< d_2 ... d_n >
    //Coms: se bloquea hasta que this->bq=< d_1 ... d_n> and n>0
    void dequeue();

    //-----------------------------------------------------
    //Pre:  this->bq=< d_1 ... d_n> and n>0
    //Post: f=d_1
    //Coms: se bloquea hasta que this->bq=< d_1 ... d_n> and n>0
    void first(T &f);

    //-----------------------------------------------------
    //Pre:  this->bq=< d_1 ... d_n> and n>0
    //Post: f=d_1 and this->bq=< d_2 ... d_n>
    //Coms: se bloquea hasta que this->bq=< d_1 ... d_n> and n>0
    void firstR(T &f, bool &no_vacia, int * p_vector_comprobacion);

    //-----------------------------------------------------
    //Pre:  this->bq=< d_1 ... d_n >
    //Post: l=n
    void length(int &l);

    //-----------------------------------------------------
    //Pre:  
    //Post: s=#this->bq
    void size(int &s);

    //-----------------------------------------------------
    //Pre:
    //Post:
    //Com:  muestra la cola por la salida estándar, separando los elementos mediante comas
    void print();

    
private:
	int N;
	BoundedQueue<T> *bq;    
	Semaphore semaforo;       
	void AVISAR();   
};
#include "ConcurrentBoundedQueue.cpp"
#endif