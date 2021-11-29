#include <Semaphore.hpp>
#include <iostream> //para cout


//----------------------------------------------------------
Semaphore::Semaphore(int n) {
    assert(n >= 0);           //aborta si se viola la Pre
    count = n;
    initialized = true;       //ya está inicializad
	
}
//----------------------------------------------------------
Semaphore::Semaphore() {
    initialized = false;      //habrá que inicializarlo
}
//----------------------------------------------------------
Semaphore::~Semaphore() {
    //nada que hacer

}
//----------------------------------------------------------
void Semaphore::setInitValue(int n, char &c) {
    c='m';

    if (print == 1) {
        fprintf(stderr, "%c\t", c);
        print = 0;
    }

    std::unique_lock<std::mutex> lck(mtx); //std::mutex para atomicidad de la función

    assert(!initialized && n >= 0);

    count = n;
    initialized = true;
    //std::cout << "setInitValue master \n";


}
//----------------------------------------------------------
void Semaphore::signal() {
    std::unique_lock<std::mutex> lck(mtx);

    assert(initialized);

    count++;
    cv.notify_all(); //podemos cambiar la semántica con cv.notify_one()
    //std::cout << "signal master \n";

}
//----------------------------------------------------------
void Semaphore::wait() {
    std::unique_lock<std::mutex> lck(mtx);

    assert(initialized);

    while(count == 0) {
        cv.wait(lck);
    }
    count--;
    //std::cout << "wait master \n";
}
//----------------------------------------------------------
void Semaphore::signal(int n) {
    std::unique_lock<std::mutex> lck(mtx);

    assert(initialized && n>0);

    count = count+n;
    cv.notify_all(); //podemos cambiar la semántica con cv.notify_one()

}
//----------------------------------------------------------
void Semaphore::wait(int n) {
    std::unique_lock<std::mutex> lck(mtx);

    assert(initialized && n>0);

    while(count < n) {
        cv.wait(lck);
    }
    count = count-n;

}
