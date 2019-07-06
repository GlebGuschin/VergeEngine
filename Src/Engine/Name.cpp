
//#include "stdafx.h"
#include "Name.hpp"

using namespace Verge3D;

Name::Name(const Name& name_) {
	id = name_.id;
	Table[id].counter++;
	Counter++;
	name = &Table[id].name[0];
}

Name::~Name() {

	Counter--;

	if (Counter == 0) {
		Finit();
	}
	else {
		Table[id].counter--;
	}

}

Name& Name::operator=(const Name& rhs) {
	Table[rhs.id].counter++;
	Counter++;
	id = rhs.id;
	name = Table[rhs.id].name;
	return *this;
}

Name::Name(const char* name_) {

	Init();
	assert(strlen(name_) <= MAX_NAME_LENGTH);

	for (unsigned i = 1; i < MAX_NAMES; i++) {
		if (strcmp(name_, Table[i].name) == 0) {
			Table[i].counter++;
			id = i;
			Counter++;
			name = &Table[i].name[0];
			return;
		}

	}

	for (unsigned i = 1; i < MAX_NAMES; i++) {
		if (Table[i].counter == 0) {
			strcpy_s(&Table[i].name[0], MAX_NAME_LENGTH, name_);
			Table[i].counter = 1;
			id = i;
			Counter++;
			name = &Table[i].name[0];
			return;
		}
	}


	assert(0);

}


void Name::Dump() {
	printf("Dump names...\n");
	for (unsigned i = 1; i < MAX_NAMES; i++) {
		if (Table[i].counter) {
			printf("Name: %s counter: %u \n ", Table[i].name, Table[i].counter);
			//OutputDebugStringA();
		}
	}
}

void Name::Init() {

	if (!Table) {
			Table = new TableItem[ MAX_NAMES ];
	}

}

void Name::Finit() {

	if (Counter == 0) {
		delete Table;
		Table = NULL;
	}

}

Name::TableItem* Name::Table = NULL;
unsigned Name::Counter = 0;


/*
	Name::Name( const char* name ) {

		std::string string( name );
		Map::iterator it = map.find( string );
		if( it == map.end() ) {
		    map.insert( Map::value_type( string, 1 ) );		
		    this->it = map.begin();	
		} else {
		    it->second++;	
		    this->it = it;
		}	

	}

        Name::~Name() {

		 //Map::iterator it = map.find( string );
 		 //assert( it != map.end() );					
		 
		 if( it->second == 1 ) {
    		     map.erase( it );	
		 } else {
                     it->second--; 
		 }
		
	}


Name::Map Name::map;

*/

