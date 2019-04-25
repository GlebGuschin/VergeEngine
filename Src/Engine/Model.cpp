#include "Model.hpp"

namespace Verge3D {


uint32_t Model::getNumLevelOfDetails() const {

	return 0;

}
	
ModelLevelOfDetail* Model::getModelLevelOfDetailByDistance(float distance) const {

	return nullptr;

}

ModelLevelOfDetail* Model::addModelLevelOfDetail(float distance) const {

	return nullptr;

}

}

/*
		
		virtual Material* getMaterial(unsigned meshIndex) const { return nullptr; }
		virtual void setMaterial(Material*, unsigned meshIndex) {}
		

			bool getLodIndex(float distance, unsigned lod) {
				for (size_t index = 0; index < details.size(); index++) {
					if (distance <= details[index].distance) {
						lod = index;
						return true;
					}
				}
				return false;
			}

			void addDetailLevel(Mesh* mesh, float distance) {
				ModelDetailInfo info;
				info.mesh = mesh;
				info.distance = distance;
				details.push_back(info);
				std::sort(details.begin(), details.end());
			}

			Mesh* getMeshByDistance(float distance) const {
				for (auto m : details) {
					if (m.distance <= distance) {
						return m.mesh;
					}
				}
				return nullptr;
			}
		

		//const ModelDetailInfo& getDetailLevel(unsigned index = 0) const { return details[index]; }
		//size_t getNumDetailLevels() const { return details.size(); }


		//virtual Geometry* getGeometry(unsigned itemIndex, unsigned lodIndex = 0) const;
		//virtual Material* getMaterial(unsigned itemIndex, unsigned lodIndex = 0) const;

*/