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