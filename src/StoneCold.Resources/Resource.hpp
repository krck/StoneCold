
#ifndef STONECOLD_RESOURCE_H
#define STONECOLD_RESOURCE_H

#include "Types.hpp"
#include <functional>
#include <string>

namespace StoneCold::Resources {

class Resource {
public:
	Resource(const std::string& name)
		: Id(std::hash<std::string>()(name)), Name(name) {}

public:
	const hash64 Id;
	const std::string Name;
};

}

#endif