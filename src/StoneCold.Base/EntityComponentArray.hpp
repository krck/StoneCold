
#ifndef STONECOLD_ENTITYCOMPONENTARRAY_H
#define STONECOLD_ENTITYCOMPONENTARRAY_H

#include "Types.hpp"
#include <exception>
#include <unordered_map>
#include <algorithm>

namespace StoneCold::Types {

template <typename T>
class EntityComponentArray {
public:
	EntityComponentArray(size_t ms) noexcept
		: _entityIndexMap(std::unordered_map<Entity, size_t>()), _maxSize(ms), _size(0), _data(new T[ms]) {
		// Always initialize the array with empty values
		for (size_t i = 0; i < _maxSize; i++)
			_data[i] = {};
	}

	inline T& operator[](Entity entity) { return _data[_entityIndexMap[entity]]; }
	inline const T& operator[](Entity entity) const { return _data[_entityIndexMap[entity]]; }

	T& at(Entity entity) {
		if (_entityIndexMap.find(entity) != _entityIndexMap.end())
			return _data[_entityIndexMap[entity]];
		throw std::out_of_range("Index not available");
	}

	const T& at(Entity entity) const {
		if (_entityIndexMap.find(entity) != _entityIndexMap.end())
			return _data[_entityIndexMap[entity]];
		throw std::out_of_range("Index not available");
	}

	inline constexpr size_t max_size() const noexcept { return _maxSize; }
	inline constexpr size_t size() const noexcept { return _size; }
	inline constexpr bool empty() const noexcept { return (_size == 0); }

	bool insert(Entity entity, T component) {
		if (_size >= _maxSize)
			return false;

		if (_entityIndexMap.find(entity) == _entityIndexMap.end()) {
			// Create a new Entity - Index pair and store the Compnent value, if the Entity
			// has no Component in this array already(Use the current size as the index)
			_entityIndexMap[entity] = _size;
			_data[_size] = component;
			_size++;
		}
		else {
			// If Entity has an index already ? Just update the Component value
			_data[_entityIndexMap[entity]] = component;
		}
		return true;
	}

	void erase(Entity entity) {
		if (_entityIndexMap.find(entity) != _entityIndexMap.end()) {
			// Get the last Entity-Index value, based on the last item in the _data array (_size - 1)
			auto lastEntity = std::find_if(_entityIndexMap.begin(), _entityIndexMap.end(), [](const auto& p) { return p.second == (_size - 1); });
			auto currentIndex = _entityIndexMap[entity];

			// Swap the last Component value with the one to erase (and clear the last)
			_data[_entityIndexMap[entity]] = _data[_entityIndexMap[lastEntity.first]];
			_data[_entityIndexMap[lastEntity.first]] = {};
			_size--;

			// Swap the last Entities Index value with the one to erase (and clear from map)
			_entityIndexMap[lastEntity.first] = currentIndex;
			_entityIndexMap.erase(entity);
		}
	}

	inline const T* GetRawData() const noexcept { return _data; }
	inline const std::unordered_map<Entity, size_t>& GetEntityIndexMap() const noexcept { return _entityIndexMap; }

	~EntityComponentArray() {
		delete[] _data;
		_entityIndexMap.clear();
		_maxSize = 0;
		_size = 0;
	}

private:
	std::unordered_map<Entity, size_t> _entityIndexMap;
	size_t _maxSize;
	size_t _size;
	T* _data;

};

}

#endif
