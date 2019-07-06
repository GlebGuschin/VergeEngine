#pragma once

#include "Common.hpp"

namespace Verge3D {

class Name {

	//std::string name;
	const char*  name;

	unsigned id;
	//typedef std::map< std::string, unsigned > Map;
	//struct {};

	//ap::iterator it;
	enum {
		MAX_NAMES = 0xFFFF,
		MAX_NAME_LENGTH = 31
	};


	struct TableItem
	{
		char name[MAX_NAME_LENGTH];
		unsigned counter;
		TableItem() { name[0] = 0; counter = 0; }
	};

	Name(unsigned id_ ) { id = id_; Table[0].counter++; Counter++; }

public:

	Name() { Init();  Table[0].counter++; id = 0; Counter++; }

	Name(const char* name_);

	Name(const Name& name_);
	~Name();

	Name& operator=(const Name& rhs);

	const char* c_str() const { return Table[id].name; }
	operator const char*() const { return Table[id].name; }
	operator unsigned() const { return id; }

	bool operator==(const Name& rhs) const { return( id == rhs.id ); }

	bool operator<(const Name& rhs) const { return strcmp(Table[id].name, Table[rhs.id].name) == -1; }
	static void Dump();

private:

static void Init();
static void Finit();
//static std::unique_ptr<TableItem> Table;
static TableItem* Table;
static unsigned Counter;


};

}








