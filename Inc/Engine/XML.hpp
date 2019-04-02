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
	XMLNode* parent;
	XMLString name;

public:

	XMLNode(XMLNode* parent_ = nullptr) : parent(parent_) {}

	const XMLString &getName() const;
	const XMLString &getValue() const;

	//const XMLNodeAttribs&  getAttribs() const = 0;
	//XMLNodeAttribs&  getAttribs() = 0;

	virtual uint32_t getNumChildren() const { return children.size(); }
	virtual XMLNode* getChildNode(uint32_t index) const { return children[index]; }

	XMLNode* addNode(const XMLString& name_) {
		XMLNode* node = new XMLNode(this);
		children.add(node);
		return node;
	}

	void removeNode(XMLNode* child) {
		check(children.find(child));
		children.remove(child);
	}

	XMLNode* getParentNode() const { return parent; }

};
	
struct XMLDocument : public Referenceable {
		
	//virtual bool readFrom(const XResourceName& fileName) = 0;
		//bool save( const XMLString &file );
	virtual XMLNode* getRoot() const = 0;

};


};