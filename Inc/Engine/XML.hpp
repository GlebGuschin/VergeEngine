#pragma once
#include "String.hpp"
#include "DynamicArray.hpp"


namespace Verge3D {

typedef String XMLString;

struct XMLNodeAttribItem {
		XMLString key, value;
		XMLNodeAttribItem() {}
};

typedef DynamicArray<XMLNodeAttribItem> XMLNodeAttribs;

struct XMLNode;
struct XMLDocument;

class XMLNode : public Referenceable {

	DynamicArray<SharedPtr<XMLNode>> children;

public:

	const XMLString &getName() const;
	const XMLString &getValue() const;

	//const XMLNodeAttribs&  getAttribs() const = 0;
	//XMLNodeAttribs&  getAttribs() = 0;

	virtual uint32_t getNumChildren() const;
	virtual XMLNode* getChildNode(uint32_t index) const;

	XMLNode* addNode();
	void removeNode(XMLNode*);

	XMLNode* getParentNode();

};
	
struct XMLDocument : public Referenceable {
		
	//virtual bool readFrom(const XResourceName& fileName) = 0;
		//bool save( const XMLString &file );
	virtual XMLNode* getRoot() const = 0;

};


};