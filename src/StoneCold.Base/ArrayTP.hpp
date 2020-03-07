
#ifndef STONECOLD_ARRAYTP_H
#define STONECOLD_ARRAYTP_H

namespace StoneCold::Types {

template <typename T>
class ArrayTP {
public:
	ArrayTP(size_t s) noexcept : _size(s), _data(new T[s]) { }

	ArrayTP(size_t s, T val) noexcept : _size(s), _data(new T[s]) {
		for (size_t i = 0; i < _size; i++)
			_data[i] = val;
	}

	ArrayTP(const ArrayTP& rhs) {
		_size = rhs.size();
		_data = new T[_size];
		for (size_t i = 0; i < _size; i++)
			_data[i] = rhs[i];
	}

	ArrayTP(ArrayTP&& rhs) noexcept {
		_size = rhs.size();
		_data = new T[_size];
		for (size_t i = 0; i < _size; i++)
			_data[i] = std::move(rhs[i]);
	}

	ArrayTP& operator=(const ArrayTP& rhs) {
		// Resize in case of different arrays
		auto rhsSize = rhs.size();
		if (_size != rhsSize) {
			delete[] _data;
			_data = new T[rhsSize];
			_size = rhsSize;
		}

		for (size_t i = 0; i < _size; i++)
			_data[i] = rhs[i];

		return *this;
	}

	ArrayTP& operator=(ArrayTP&& rhs) noexcept {
		// Resize in case of different arrays
		auto rhsSize = rhs.size();
		if (_size != rhsSize) {
			delete[] _data;
			_data = new T[rhsSize];
			_size = rhsSize;
		}

		for (size_t i = 0; i < _size; i++)
			_data[i] = std::move(rhs[i]);

		return *this;
	}

	T& operator[](size_t pos) { return _data[pos]; }
	const T& operator[](size_t pos) const { return _data[pos]; }

	T& at(size_t pos) {
		if (pos > 0 && pos < _size) return _data[pos];
		else throw std::out_of_range("Index out of range");
	}
	const T& at(size_t pos) const {
		if (pos > 0 && pos < _size) return _data[pos];
		else throw std::out_of_range("Index out of range");
	}

	inline constexpr size_t size() const noexcept { return _size; }
	inline constexpr bool empty() const noexcept { return (_size == 0); }

	void insert(size_t pos, const T& value) { _data[pos] = value; }
	void insert(size_t pos, T&& value) { _data[pos] = value; }
	void erase(size_t pos) { _data[pos] = {}; }

	T* data() noexcept { return _data; }
	const T* data() const noexcept { return _data; }

	bool operator==(const ArrayTP& rhs) const {
		if (_size != rhs.size()) return false;
		auto comparison = rhs.data();
		for (size_t i = 0; i < _size; i++)
			if (_data[i] != comparison[i])
				return false;
		return true;
	}

	bool operator!=(const ArrayTP& rhs) const { return !(*this == rhs); }

	~ArrayTP() { delete[] _data; _size = 0; };

private:
	size_t _size;
	T* _data;
};

}

#endif
