//#include "FileSystemManager.hpp"
//#include "MemoryManager.hpp"
#include "CoreModule.hpp"

#include <Windows.h>


namespace Verge3D {

File::~File() {

	manager->destroyFile(this);

}

bool File::open(const FileName& fileName_, FileAccessType fileAccessType_, bool map_) {

	DWORD access = fileAccessType_ == FileAccessType::Read ? GENERIC_READ : GENERIC_WRITE;
	DWORD creation = CREATE_ALWAYS;
	creation = OPEN_EXISTING;

	access = GENERIC_READ | GENERIC_WRITE;

	hFile = CreateFileW(
		fileName_.getName().w_str(),
		access,
		NULL,
		NULL,
		creation,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);

	if (hFile == INVALID_HANDLE_VALUE) {
		return(false);
	}

	valid = true;
	fileAccessType = fileAccessType_;

	DWORD error = GetLastError();

	if (map_) {
		DWORD fileSize = GetFileSize(hFile, nullptr);
		hMapFile = CreateFileMappingW(
			hFile,          // current file handle
			NULL,           // default security
			PAGE_READWRITE, // read/write permission
			0,              // size of mapping object, high
			fileSize,  // size of mapping object, low
		//16,  // size of mapping object, low
			NULL);
		
		error = GetLastError();

		map = true;
	}
	

	return true;
}

void File::close() {

	if (map) {
		CloseHandle(hMapFile);
	}

	CloseHandle(hFile);

}

void File::flush() {

}

/*
virtual bool read(size_t size, void* ptr);
virtual bool write(size_t size, const void* ptr);
virtual size_t getSize();
virtual void setPos(size_t offset);
*/

bool File::read(size_t size_, void* ptr_) {

	bool result = true;
	
	DWORD read;
	//DWORD fileSize = size_;
	//fileSize = GetFileSize(hFile, nullptr);
	
	BOOL ok  = ReadFile(hFile, ptr_, size_, &read, NULL);
	check(ok);

	return result;

}

bool File::write(size_t size_, const void* ptr_) {

	bool result = true;
	DWORD written;

	BOOL ok = WriteFile(hFile, ptr_, size_, &written, NULL);
	check(ok);
	return result;

}

/*
size_t File::getSize() {

}
*/
	

File* FileSystemManager::createFile() {

	File* file = new File(this);

	files.add(file);

	return file;

}

void FileSystemManager::destroyFile(File* file) {

	files.remove(file);

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
	DebugLog("Loaded file %ws", fileName.getName().w_str());

	return buffer;

}

bool FileSystemManager::collectFiles(const String& path, const String& ext, DynamicArray<FileName>& files, bool recursive) {
	
	//files.clear();
	String searchInfo = path;
	searchInfo += String("\\*.*");
	FileName file(path );

	WIN32_FIND_DATAW findData;
	HANDLE hFile = FindFirstFileW(searchInfo.w_str(), &findData);
	if (hFile == INVALID_HANDLE_VALUE) {
		return false;
	}

	while (FindNextFileW(hFile, &findData)) {

		if (!(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {			
			FileName str(String(findData.cFileName));
			if (str.getExt() == ext) {
				String newPath = path;
				newPath += String("/");
				newPath += String(findData.cFileName);
				files.add(newPath);
			}
		} else {
			if (recursive) {
				String dir(findData.cFileName);
				if (dir != String("..")) {
					String newPath = path;
					newPath += String("/");
					newPath += dir;
					collectFiles(newPath, ext, files, true);
				}
			}
		}

	}

	FindClose(hFile);

	return true;

}

/*
	FindClose( hFile );

}

bool XFileSearch::findFirstFile( const XResourceName &fileMask ) {

	XResourceName resolvedResourceName;

	bool bResolved = manager->resolveFile( fileMask, resolvedResourceName );

	hFile = FindFirstFileW( fileMask.getName(), &findData );

	//return( hFile != 0xFFFFFFFF );
	return( hFile != NULL );

}


bool XFileSearch::findNextFile() {

	BOOL bFound = FindNextFileW( hFile, &findData );
	if( !bFound ) return( false );


	if( !( findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ) ) {
			current = (XWCHAR*)&findData.cFileName[ 0 ];
	}


*/

}