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

struct XMLNode : public Referenceable {

	virtual const XMLString &getName() const = 0;
	virtual const XMLString &getValue() const = 0;

	virtual const XMLNodeAttribs&  getAttribs() const = 0;
	virtual XMLNodeAttribs&  getAttribs() = 0;

	virtual uint32_t getNumChildren() const = 0;
	virtual XMLNode* getChildNode(uint32_t index) const = 0;

	virtual XMLNode* addNode() = 0;
	virtual void removeNode(XMLNode*) = 0;

	virtual XMLNode* getParentNode() = 0;

};
	
struct XMLDocument : public Referenceable {
		
	//virtual bool readFrom(const XResourceName& fileName) = 0;
		//bool save( const XMLString &file );
	virtual XMLNode* getRoot() const = 0;

};


};