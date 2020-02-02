
#ifndef STONECOLD_MANAGER_H
#define STONECOLD_MANAGER_H

#include "Types.hpp"
#include <string>

namespace StoneCold::Resources {

class IManager {
public:
	virtual bool LoadResources() = 0;
	virtual bool UnloadResources() = 0;

protected:
	uint GenerateId(const std::string& str) {
	
	}

};

}

#endif
