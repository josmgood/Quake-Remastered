#pragma once

/*Standard Library*/
#include <typeinfo>
#include <type_traits>
#include <iostream>

/*Custom Library*/
#include "..\..\Allocators\Include\base_allocator.h"

namespace traits
{
	//typedef std::true_type		Yes; ERRORENOUS IMPLEMENTATION
	//typedef std::false_type		No;

	enum TYPE_CHECK
	{
		NO = 0, /*Class has the method*/
		YES = 1 /*Class does not have the method.*/
	};

	/*Check if a class has the allocate(size_t) method.*/
	template<typename T>
	class has_allocate
	{
	private:
		/*
		Checks for the allocate(size_t) method.

		/tparam - reference to the allocate(size_t) method
		*/
		template<typename U, Block&(U::*)(size_t)> struct TCheck;

		/*
		Tests the allocate(size_t) method's existence.

		/tparam -	reference to the allocate(size_t) method
		/r -		the method exists in the class
		*/
		template<typename U> static constexpr TYPE_CHECK test(TCheck<U, &U::allocate>*) { return TYPE_CHECK::YES; }

		/*
		If allocate(size_t) was not found...

		/tparam -	reference to the allocate(size_t) method
		/r -		the method was not found in the class
		*/
		template<typename U> static constexpr TYPE_CHECK test(...) { return TYPE_CHECK::NO; }
	public:
		/*
		The outcome of the search.

		/v - YES : NO
		*/
		static constexpr TYPE_CHECK value = test<T>(nullptr);
	};

	/*Checks if a class has the allocateAll(size_t) method.*/
	template<typename T>
	class has_allocate_all
	{
	private:
		/*
		Checks for the allocateAll() method.

		/tparam - reference to the allocateAll() method.
		*/
		template<typename U, void(U::*)(size_t)> struct TCheck;

		/*
		Tests the allocateAll() method's existence

		/tparam -	reference to the allocateAll() method
		/r -		the method was found in the class
		*/
		template<typename U> static constexpr TYPE_CHECK test(TCheck<U, &U::allocateAll>*) { return TYPE_CHECK::YES; }

		/*
		If allocateAll() was not found...

		/tparam -	reference to the allocateAll() method
		/r			the method was not found in the class
		*/
		template<typename U> static constexpr TYPE_CHECK test(...) { return TYPE_CHECK::NO; }
	public:
		static constexpr TYPE_CHECK value = test<T>(nullptr);
	};

	/*Checks if a class has the deallocate(Block&) method.*/
	template<typename T>
	class has_deallocate
	{
	private:
		template<typename U, void(U::*)(Block&)> struct TCheck;
		template<typename U> static constexpr TYPE_CHECK test(TCheck<U, &U::deallocate>*) { return TYPE_CHECK::YES; }
		template<typename U> static constexpr TYPE_CHECK test(...) { return TYPE_CHECK::NO; }
	public:
		static constexpr TYPE_CHECK value = test<T>(nullptr);
	};

	/*Checks a class for the deallocateAll(void) method*/
	template<typename T>
	class has_deallocate_all
	{
	private:
		template<typename U, void(U::*)(void)> struct TCheck;
		template<typename U> static constexpr TYPE_CHECK test(TCheck<U, &U::deallocateAll>*) { return TYPE_CHECK::YES; }
		template<typename U> static constexpr TYPE_CHECK test(...) { return TYPE_CHECK::NO; }
	public:
		static constexpr TYPE_CHECK value = test<T>(nullptr);
	};

	/*Checks a class for the realloacate(Block&, size_t) method.*/
	template<typename T>
	class has_reallocate
	{
	private:
		template<typename U, void(U::*)(Block&, size_t)> struct TCheck;
		template<typename U> static constexpr TYPE_CHECK test(TCheck<U, &U::reallocate>*) { return TYPE_CHECK::YES; }
		template<typename U> static constexpr TYPE_CHECK test(...) { return TYPE_CHECK::NO; }
	public:
		static constexpr TYPE_CHECK value = test<T>(nullptr);
	};

	/*Checks a class for the reallocateAll(size_t) method.*/
	template<typename T>
	class has_reallocate_all
	{
	private:
		template<typename U, void(U::*)(size_t)> struct TCheck;
		template<typename U> static constexpr TYPE_CHECK test(TCheck<U, &U::reallocateAll>*) { return TYPE_CHECK::YES; }
		template<typename U> static constexpr TYPE_CHECK test(...) { return TYPE_CHECK::NO; }
	public:
		static constexpr TYPE_CHECK value = test<T>(nullptr);
	};

	/*Checks a class for the owns(Block) method.*/
	template<typename T>
	class has_owns
	{
	private:
		template<typename U, bool(U::*)(Block)> struct TCheck;
		template<typename U> static constexpr TYPE_CHECK test(TCheck<U, &U::owns>*) { return TYPE_CHECK::YES; }
		template<typename U> static constexpr TYPE_CHECK test(...) { return TYPE_CHECK::NO; }
	public:
		static constexpr TYPE_CHECK value = test<T>(nullptr);
	};

	/*template<typename AllocatorOne, typename AllocatorTwo>
	struct have_same_base : std::false_type{};

	template<typename Allocator>
	struct have_same_base<Allocator, Allocator> : std::true_type{};*/

	/*template<typename Allocator, typename Enabled = void>
	struct _allocate_<Allocator, typename std::enable_if<has_allocate<Allocator>::value>::type>
	{
	static Block& execute(Allocator& allocator, size_t size)
	{
	return(allocator.allocate(size));
	}
	};

	template<typename Allocator>
	struct _allocator_<Allocator, typename std::enable_if<!has_allocate<Allocator>::value>::type>
	{
	static Block& execute(Allocator& allocator, size_t size)
	{
	return(nullptr);
	}
	};

	template<typename Allocator, typename Enabled = void>
	struct _allocateAll_<Allocator, typename std::enable_if<has_allocate_all<Allocator>::value>::type>
	{
	static void execute(Allocator& allocator, size_t size)
	{
	allocator.allocateAll(size);
	}
	};

	template<typename Allocator>
	struct _allocateAll_< Allocator, typename std::enable_if<!has_allocate_all<Allocator>::value>::type>
	{
	static void execute(Allocator& allocator, size_t size)
	{
	}
	};

	template<typename Allocator, typename Enabled = void>
	struct _deallocate_<Allocator, typename std::enable_if<has_deallocate<Allocator>::value>::type>
	{
	static bool execute(Allocator& allocator, Block& block)
	{
	return(allocator.deallocate(block));
	}
	};

	template<typename Allocator>
	struct _deallocate_<Allocator, typename std::enable_if<!has_deallocate<Allocator>::value>::type>
	{
	static bool execute(Allocator& allocator, Block& block)
	{
	return(false);
	}
	};

	template<typename Allocator, typename Enabled = void>
	struct _deallocateAll_<Allocator, typename std::enable_if<has_deallocate_all<Allocator>::value>::type>
	{
	static bool execute(Allocator& allocator)
	{
	return(allocator.deallocateAll());
	}
	};

	template<typename Allocator>
	struct _deallocateAll_<Allocator, typename std::enable_if<!has_deallocate_all<Allocator>::value>::type>
	{
	static bool execute(Allocator& allocator)
	{
	return(false);
	}
	};

	template<typename Allocator, typename Enabled = void>
	struct _reallocate_<Allocator, typename std:enable_if<has_reallocate<Allocator>::value>::type>
	{
	static bool execute(Allocator& allocator, Block& block, size_t newSize)
	{
	return(allocate.reallocate(block, newSize));
	}
	};

	template<typename Allocator>
	struct _reallocate_<Allocator, typename std::enable_if<!has_reallocate<Allocator>::value>::type>
	{
	static bool execute(Allocator& allocator, Block& block, size_t newSize)
	{
	return(false);
	}
	};

	template<typename Allocator, typename Enabled = void>
	struct _reallocateAll_ <Allocator, typename std::enable_if<has_reallocate_all<Allocator>::value>::type>
	{
	static bool execute(Allocator& allocator, size_t newSize)
	{
	return(allocator.reallocateAll(newSize));
	}
	};

	template<typename Allocator>
	struct _reallocateAll_<Allocator, typename std::enable_if<!has_reallocate_all<Allocator>::value>::type>
	{
	static bool execute(Allocator& allocator, size_t newSize)
	{
	return(false);
	}
	};

	template<typename Allocator, typename Enabled = void>
	struct _owns_<Allocator, typename std::enable_if<has_owns<Allocator>::value>::type>
	{
	struct bool execute(Allocator& allocator, Block block)
	{
	return(allocator.owns(block));
	}
	};

	template<typename Allocator>
	struct _owns_ <Allocator, typename std::enable_if<!has_owns<Allocator>::value>::type>
	{
	struct bool execute(Allocator& allocator, Block block)
	{
	return(false);
	}
	};*/
}