
#ifndef STONECOLD_RESOURCE_H
#define STONECOLD_RESOURCE_H

#include <functional>
#include <string>

namespace StoneCold::Resources {

enum class ResourceType { Texture, Animation, Audio };

class Resource {
public:
	Resource(ResourceType type, const std::string& name, const std::string& path) 
		: Id(std::hash<std::string>()(path)), Type(type), Name(name), Path(path) {}

public:
	const hash64 Id;
	const ResourceType Type;
	const std::string Name;
	const std::string Path;
};

}

#endif
