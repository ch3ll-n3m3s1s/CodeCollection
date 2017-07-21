//
// @brief   
// @details 
// @author  Steffen Peikert (ch3ll)
// @email   n3m3s1s.games+github@gmail.com
// @version 1.0.0
// @date    19.07.2017 10:40
// @project CodeCollection
//

#pragma once

#include "codecollection/TwoState/TwoStateCommon.hpp"
#include <memory>
#include <sstream>

namespace TWOSTATE
{
	template<typename T>
	class TwoStateArray
	{
	private:
		struct Node
		{
			T Value;
			Elevation NodeState;
		};

		Node* _data;

	public:
		unsigned int Capacity;

	public:
		/*!
		 * Creates an empty twostate array.
		 */
		TwoStateArray()
		{
			_data = nullptr;

			Capacity = 0;
		}

		/*!
		 * Creates a twostate array of given size with default value.
		 * @param capacity Initial capacity of twostate array.
		 */
		explicit TwoStateArray(unsigned int capacity) : TwoStateArray(capacity, T()) {}

		/*!
		 * Creates a twostate array of given size. Each element gets initialized with the given value.
		 * @param capacity		Initial capacity of twostate array.
		 * @param initializer	The inital value of each element.
		 * @param elevateAll	True if each element should be initialized elevated.
		 */
		TwoStateArray(unsigned int capacity, T const& initializer, bool const& elevateAll = false)
		{
			_data = static_cast<Node*>(malloc(capacity * sizeof(Node)));

			Capacity = capacity;

			for (unsigned int i = 0; i < Capacity; i++)
			{
				_data[i] = { T(initializer), Elevation(elevateAll) };
			}
		}

		/*!
		 * Creates a copy of an two state array.
		 * @param other	The twostate array to copy.
		 */
		TwoStateArray(TwoStateArray<T> const& other)
		{
			_data = static_cast<Node*>(malloc(other.Capacity * sizeof(Node)));

			for (unsigned int i = 0; i < other.Capacity; i++)
			{
				_data[i] = { T(other[i]), other.GetState(i) };
			}

			Capacity = other.Capacity;
		}


		/*!
		 * Frees the array.
		 */
		~TwoStateArray()
		{
			free(_data);
		}


		/*!
		 * Copy assignment for twostate array.
		 * @param other	The twostate array to copy.
		 * @return	A self reference to the updated twostate array.
		 */
		TwoStateArray& operator=(TwoStateArray<T> const& other)
		{
			if (this != &other)
			{
				//clear current data
				free(_data);

				// copy
				_data = static_cast<Node*>(malloc(other.Capacity * sizeof(Node)));

				for (unsigned int i = 0; i < other.Capacity; i++)
				{
					_data[i] = { T(other[i]), other.GetState(i) };
				}

				Capacity = other.Capacity;
			}

			return *this;
		}

		/*!
		 * Gets the element at a given position.
		 * If the position is out of bounds, an std::out_of_range exception is thrown.
		 * @param position	The position of the element to return.
		 * @return	Reference to the requested element.
		 */
		T const& At(size_t position) const
		{
			if (Capacity < position)
			{
				std::stringstream what;
				what << "Cannot access element at position " << position << ".";
				throw std::out_of_range(what.str());
			}

			return _data[position].Value;
		}

		/*!
		 * Gets the element at a given position.
		 * If the position is out of bounds, an std::out_of_range exception is thrown.
		 * @param position	The position of the element to return.
		 * @return	Reference to the requested element.
		 */
		T& At(size_t position)
		{
			if (Capacity < position)
			{
				std::stringstream what;
				what << "Cannot access element at position " << position << ".";
				throw std::out_of_range(what.str());
			}

			return _data[position].Value;
		}

		/*!
		 * Gets the element at a given position. No bounds check is performed.
		 * @param position	The position of the element to return.
		 * @return	Reference to the requested element.
		 */
		T const& operator[](size_t position) const
		{
			return _data[position].Value;
		}


		/*!
		 * Sets the element at a given position.
		 * If the position is out of bounds, an std::out_of_range exception is thrown.
		 * @param position	The position of the element to set.
		 * @param val		The element.
		 * @param isElevated	True if the element should be set elevated.
		 */
		void Set(size_t position, T const& val, bool isElevated = false)
		{
			if (Capacity < position)
			{
				std::stringstream what;
				what << "Cannot access element at position " << position << ".";
				throw std::out_of_range(what.str());
			}

			_data[position] = { T(val), Elevation(isElevated) };
		}


		/*!
		 * Gets the elevation of the element at the given position. No bounds check is performed.
		 * @param position	The position of the element.
		 * @return	The elevation of the element at the given position.
		 */
		Elevation GetState(size_t position) const
		{
			return _data[position].NodeState;
		}

		/*!
		 * Checks if the element at the given position is in high state. No bounds check is performed.
		 * @param position	The position of the element.
		 * @return	True if the element is in high state, false otherwise.
		 */
		bool IsHigh(size_t position) const
		{
			return _data[position].NodeState;
		}

		/*!
		 * Checks if the element at the given position is in low state. No bounds check is performed.
		 * @param position	The position of the element.
		 * @return	True if the element is in low state, false otherwise.
		 */
		bool IsLow(size_t position) const
		{
			return !_data[position].NodeState;
		}

		/*!
		 * Elevates the given element.
		 * If the element was already elevated, nothing is done.
		 * If the position is out of bounds, an std::out_of_range exception is thrown.
		 * @param position	The position of the element.
		 * @return	True if the element has been elevated, false otherwise.
		 */
		bool Elevate(size_t position)
		{
			if (Capacity < position)
			{
				std::stringstream what;
				what << "Cannot access element at position " << position << ".";
				throw std::out_of_range(what.str());
			}

			if (_data[position].NodeState)
			{
				return false;
			}

			_data[position].NodeState = Elevation::HIGH;
			return true;
		}

		/*!
		 * Decreases the given element.
		 * If the element was already low, nothing is done.
		 * If the position is out of bounds, an std::out_of_range exception is thrown.
		 * @param position	The position of the element.
		 * @return	True if the element has been decreased, false otherwise.
		 */
		bool Decrease(size_t position)
		{
			if (Capacity < position)
			{
				std::stringstream what;
				what << "Cannot access element at position " << position << ".";
				throw std::out_of_range(what.str());
			}

			if (!_data[position].NodeState)
			{
				return false;
			}

			_data[position].NodeState = Elevation::LOW;
			return true;
		}

		/*!
		 * Resizes the container to the new capacity.
		 * If the new capacity is smaller, all excess elements at the end of the array will be removed.
		 * @param capacity	The new container capacity.
		 */
		void Resize(unsigned int const capacity)
		{
			_data = static_cast<Node*>(realloc(_data, capacity * sizeof(Node)));

			Capacity = capacity;
		}




	public:
		class iterator
		{
		private:
			T* _pointer;
		public:
			iterator(T *ptr) : _pointer(ptr) {};

			iterator& operator++(){ _pointer++; return *this; };
			iterator& operator++(int step) { _pointer += step; return *this; }

			T& operator*() const { return *_pointer; }
			T* operator->() const { return _pointer; }
		};
	};
}