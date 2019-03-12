#pragma once

#include "Geometry.hpp"
#include "Material.hpp"

namespace Verge3D {


struct MeshItem {
		SharedPtr<Geometry> geometry;
		SharedPtr<Material> material;
		MeshItem(Geometry* geometry_, Material*  material_) : geometry(geometry_), material(material_) {}
};

/*
class Mesh : public Referenced {
		std::vector<MeshItem> items;
public:

		size_t getNumItems() const;
		void addItem(Geometry* geometry = nullptr, Material* material = nullptr);
		const MeshItem& getItem(size_t index) const;
		MeshItem& getItem(size_t index);
		void clearItems();

	};

	class MeshManager {

	public:

		//Geometry* createGeometry(unsigned flags, );
		virtual Mesh* createMesh(const MeshInfo&, const VertexLayout*, unsigned numVertices, unsigned numIndexes = 0);
		virtual void destroyMesh(Mesh*);

	};
*/


class ModelLevelOfDetail : public Referenceable {


};

class Model : public Referenceable {

	/*
		struct ModelDetailInfo {
			float distance;
			SharedPtr<Mesh> mesh;
			bool operator<(const ModelDetailInfo& other) const {
				return distance < other.distance;
			}
		};

		//size_t numDetailLevels;
		std::vector<ModelDetailInfo> details;
	*/

public:

	uint32_t getNumLevelOfDetails() const;
	ModelLevelOfDetail* getModelLevelOfDetailByDistance(float distance) const;
	ModelLevelOfDetail* addModelLevelOfDetail(float distance) const;


};


}