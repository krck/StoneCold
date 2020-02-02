
#ifndef STONECOLD_MANAGER_H
#define STONECOLD_MANAGER_H

#include "Types.hpp"
#include "Resource.hpp"
#include <string>
#include <vector>

namespace StoneCold::Resources {

class IManager {
public:
	virtual bool LoadResources(const std::vector<Resource>& resources) = 0;
	virtual bool UnloadResources(const std::vector<uint>& resourceIds) = 0;

protected:
	uint GenerateId(const std::string& str) {
	
	}

};

}

#endif
