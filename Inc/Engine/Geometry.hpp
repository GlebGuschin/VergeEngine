#pragma once
#include "RenderCommon.hpp"


namespace Verge3D {


enum class PrimitiveType {
	Triangles,
	Lines,
	Patch3
};

struct Primitive {

	bool indexable;
	PrimitiveType type;
	unsigned startVertex;
	unsigned vertexCount;
	unsigned indexCount;
	unsigned startIndexLocation;
	int baseVertexLocation;

		Primitive(PrimitiveType type_, unsigned startVertex_, unsigned vertexCount_) :
			type(type_), startVertex(startVertex_), vertexCount(vertexCount_), indexable(false) {}

		Primitive(PrimitiveType type_, unsigned indexCount_, unsigned startIndexLocation_, int baseVertexLocation_) :
			type(type_), indexCount(indexCount_), startIndexLocation(startIndexLocation_), baseVertexLocation(baseVertexLocation_), indexable(true) {}

		/*
		bool operator==(const Primitive& other) const {

			return indexable == other.indexable;
		}*/

};

class Primitives {
	std::vector<Primitive> primitives;
public:
	uint32_t getNumPrimitives() const { return (uint32_t)primitives.size(); }
	const Primitive& getPrimitive(uint32_t index) const { return primitives[index]; }
};


enum IndexType { 
	Index16,
	Index32 
};

enum class VertexAttributeType {
	Float
};

enum class VertexLayoutItemType {
	Position, 
	Color0,
	Color1,
	Normal,
	Tangent,
	TexCoord0
};

class VertexBuffer : public Referenceable {
public:
};


class IndexBuffer : public Referenceable {
		IndexType type;
public:
};

enum class VertexBufferType {
	Default,
	Depth,
	Max
};

class Geometry : public Referenceable {
	
	Primitives primitives;

public:

	VertexBuffer* getVertexBuffer(VertexBufferType type = VertexBufferType::Default) const { return nullptr; }
	IndexBuffer* getIndexBuffer() const { return nullptr; }

	const Primitives& getPrimitives() const { return primitives; }
	void setPrimitives(const Primitives& primitives_) { primitives = primitives_; }
	
};

}