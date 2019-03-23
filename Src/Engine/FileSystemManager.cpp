//#include "FileSystemManager.hpp"
//#include "MemoryManager.hpp"
#include "CoreModule.hpp"

#include <Windows.h>


namespace Verge3D {

		/*
	bool File::read() {

		}

			bool File::write();
			size_t File::getSize();
	
	};
	*/

File* FileSystemManager::createFile(const FileName&) {

	return nullptr;
}

void FileSystemManager::destroyFile(File*) {
}

MemoryBuffer* FileSystemManager::loadFile(const FileName& fileName) {

	MemoryBuffer* buffer = nullptr;
	HANDLE hFile;

	hFile = CreateFileW(fileName.getName().w_str(),
		GENERIC_READ,
		NULL,
		NULL,
		OPEN_EXISTING,
		NULL,
		NULL
	);

	if (hFile == INVALID_HANDLE_VALUE) {
		return(NULL);
	}

	DWORD fileSize = GetFileSize(hFile, NULL);

	buffer = coreModule->getMemoryManager()->createBuffer(fileSize);

	/*
	if (res != RES_OK) {
		return(NULL);
	}
	*/

	LPVOID ptr = (LPVOID)buffer->lock();


	DWORD length;


	ReadFile(hFile,
		ptr,
		fileSize,
		&length,
		NULL);

	buffer->unlock();

	if (length != fileSize) {
		return(NULL);
	}

	CloseHandle(hFile);

	//*fileBuffer = buffer;

	return buffer;

}

}