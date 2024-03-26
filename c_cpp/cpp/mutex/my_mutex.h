//
// Created by 张宜鹏 on 2023/1/29.
//

#ifndef CPP_MY_MUTEX_H
#define CPP_MY_MUTEX_H

#include <iostream>
#include <memory>

class Mutex {
public:
    Mutex() {
        pthread_mutex_init(&mMutex, NULL);
    }
    int lock() {
        return -pthread_mutex_lock(&mMutex);
    }
    void unlock() {
        pthread_mutex_unlock(&mMutex);
    }
    ~Mutex() {
        pthread_mutex_destroy(&mMutex);
    }

    // A simple class that locks a given mutex on construction
    // and unlocks it when it goes out of scope.
    class Autolock {
    public:
        Autolock(Mutex &mutex) : lock(&mutex) {
            lock->lock();
        }
        ~Autolock() {
            lock->unlock();
        }
    private:
        Mutex *lock;
    };

private:
    pthread_mutex_t mMutex;

    // Disallow copy and assign.
    Mutex(const Mutex&);
    Mutex& operator=(const Mutex&);
};


#endif //CPP_MY_MUTEX_H
