#ifndef __SHAREDMEMORY_H_
#define __SHAREDMEMORY_H_

#ifndef __STRING__
#include <string>
#define __STRING__
#endif

#ifndef __SHAREDMEMORYEXCEPTION_H_
#include <SharedMemoryException.h>
#define __SHAREDMEMORYEXCEPTION_H_
#endif

#ifndef __ERRNO_H_
#include <errno.h>
#define __ERRNO_H_
#endif

#ifndef __SYS_TYPES_H_
#include <sys/types.h>
#define __SYS_TYPES_H_
#endif

#ifndef __SYS_MMAN_H_
#include <sys/mman.h>
#define __SYS_MMAN_H_
#endif

#ifndef __FCNTL_H_
#include <fcntl.h>
#define __FCNTL_H_
#endif

#ifndef __ERRNO_H_
#include <errno.h>
#define __ERRNO_H_
#endif

#ifndef __CSTRING__
#include <cstring>
#define __CSTRING__
#endif

#ifndef __CSTDIO__
#include <cstdio>
#define __CSTDIO__
#endif

using namespace std;

template<class T>
class SharedMemory {
	T *mem;
	string name;
	int buffer;
	
public:
	SharedMemory(const string &n) throw(SharedMemoryException);
	virtual ~SharedMemory();

	T &operator()() {
		return *mem;
	};
};


template<class T>
SharedMemory<T>::SharedMemory(const string &n) throw(SharedMemoryException) {
	name = n;
	buffer = shm_open(name.c_str(), O_RDWR | O_CREAT, S_IRWXU);
	if (buffer == -1) {
		perror("shm_open");
		throw new SharedMemoryException(name + ":" + strerror(errno));
	}
	if (ftruncate(buffer, sizeof(T)) == -1) {
		perror("ftruncate");
		close(buffer);
		shm_unlink(name.c_str());
		throw new SharedMemoryException(name + ":" + strerror(errno));
	}
	mem = (T *) mmap(NULL, sizeof(T), PROT_READ | PROT_WRITE, MAP_SHARED, buffer, 0);
}

template<class T>
SharedMemory<T>::~SharedMemory() {
	close(buffer);
	shm_unlink(name.c_str());
}


#endif /*__SHAREDMEMORY_H_*/
