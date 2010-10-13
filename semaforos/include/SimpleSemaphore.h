#ifndef __SIMPLESEMAPHORE_H_
#define __SIMPLESEMAPHORE_H_

#ifndef __STRING_
#include <string>
#define __STRING_
#endif

#ifndef __SEMAPHORE_H_
#include <semaphore.h>
#define __SEMAPHORE_H_
#endif

#ifndef __SIMPLESEMAPHOREEXCEPTION_H_
#include <SimpleSemaphoreException.h>
#define __SIMPLESEMAPHOREEXCEPTION_H_
#endif

#ifndef __FCNTL_H_
#include <fcntl.h>
#define __FCNTL_H_
#endif

#ifndef __ERRNO_H_
#include <errno.h>
#define __ERRNO_H_
#endif

#ifndef __IOSTREAM_
#include <iostream>
#define __IOSTREAM_
#endif

#ifndef __CSTRING__
#include <cstring>
#define __CSTRING__
#endif

#ifndef __CSTDIO_
#include <cstdio>
#define __CSTDIO_
#endif

using namespace std;

class SimpleSemaphore {
	
	sem_t *semaphore;
	string semName;
	
  public:
	SimpleSemaphore(const string &name, int value = 1) throw (SimpleSemaphoreException);
	virtual ~SimpleSemaphore();
	
	void Wait() {while (sem_wait(semaphore) == EINTR) ;};
	void Signal() {sem_post(semaphore);};;
};

inline SimpleSemaphore::SimpleSemaphore(const string &name, int value) throw (SimpleSemaphoreException) {
	
	semName = name;
	semaphore = sem_open(semName.c_str(), O_CREAT, S_IRWXU, value);
	if (semaphore == SEM_FAILED) {
		perror("sem_open");
		throw new SimpleSemaphoreException(name+":"+strerror(errno));
	}
	
}

inline SimpleSemaphore::~SimpleSemaphore() {
	
	sem_close(semaphore);
	sem_unlink(semName.c_str());
}

#endif /* __SIMPLESEMAPHORE_H_ */
