#pragma once

/*Standard Library*/
#include <typeinfo>
#include <type_traits>
#include <iostream>

/*Custom Library*/
#include "..\..\Allocators\Include\base_allocator.h"

#define YES		true
#define NO		false

/*
* ===========================================================================================
*
* TRAITS NAMESPACE
*
* Contains meta-functions that aid memory management.
* Not all allocators have the same methods and need to be handled on a case-to-case basis.
*
* ===========================================================================================
*/

namespace traits
{
	//typedef std::true_type		Yes; ERRORENOUS IMPLEMENTATION
	//typedef std::false_type		No; Implementation would find the function but not accurately according to method signature

	/*Check if a class has the allocate(size_t) method.*/
	template<typename T>
	class has_allocate
	{
	private:
		/*
		Checks for the allocate(size_t) method.
		Helper struct that actually finds the method.

		/tparam - reference to the allocate(size_t) method
		*/
		template<typename U, Block(U::*)(size_t)> struct TCheck;

		/*
		Tests the allocate(size_t) method's existence.

		/tparam -	reference to the allocate(size_t) method
		/r -		the method exists in the class
		*/
		template<typename U> static constexpr bool test(TCheck<U, &U::allocate>*) { return YES; }

		/*
		If allocate(size_t) was not found...

		/tparam -	reference to the allocate(size_t) method
		/r -		the method was not found in the class
		*/
		template<typename U> static constexpr bool test(...) { return NO; }
	public:
		/*
		The outcome of the search.

		/v - YES : NO
		*/
		static constexpr bool value = test<T>(nullptr);
	};

	//===========================================================================================================================

	/*Checks if a class has the allocateAll(size_t) method.*/
	template<typename T>
	class has_allocate_all
	{
	private:
		/*
		Checks for the allocateAll() method.
		Helper struct that actually finds the method.

		/tparam - reference to the allocateAll() method.
		*/
		template<typename U, void(U::*)(size_t)> struct TCheck;

		/*
		Tests the allocateAll() method's existence

		/tparam -	reference to the allocateAll() method
		/r -		the method was found in the class
		*/
		template<typename U> static constexpr bool test(TCheck<U, &U::allocateAll>*) { return YES; }

		/*
		If allocateAll() was not found...

		/tparam -	reference to the allocateAll() method
		/r			the method was not found in the class
		*/
		template<typename U> static constexpr bool test(...) { return No; }
	public:
		/*
		The outcome of the search.

		/v - YES : NO
		*/
		static constexpr bool value = test<T>(nullptr);
	};

	//===========================================================================================================================

	/*Checks if a class has the deallocate(Block&) method.*/
	template<typename T>
	class has_deallocate
	{
	private:
		/*
		Checks for the deallocate(Block&) method.
		Helper struct that actually finds the method.
		
		/tparam - reference to the deallocate(Block&) method.
		*/
		template<typename U, void(U::*)(Block&)> struct TCheck;

		/*
		Tests the deallocate(Block&)'s existence.

		/tparam -	reference to the deallocate(Block&) method
		/r -		the method exists in the class
		*/
		template<typename U> static constexpr bool test(TCheck<U, &U::deallocate>*) { return YES; }
		
		/*
		If deallocate(Block&) was not found...
		
		/tparam -	reference to the deallocate(Block&) method
		/r -		the method was not found in the class
		*/
		template<typename U> static constexpr bool test(...) { return No; }
	public:
		/*
		The outcome of the search.
		
		/v - YES : NO
		*/
		static constexpr bool value = test<T>(nullptr);
	};

	//===========================================================================================================================

	/*Checks a class for the deallocateAll(void) method*/
	template<typename T>
	class has_deallocate_all
	{
	private:
		/*Checks for the deallocateAll() method.
		Helper struct that actually finds the method.
		
		/tparam - reference to the deallocateAll() method
		*/
		template<typename U, void(U::*)(void)> struct TCheck;

		/*
		Tests the deallocateAll() method's existence
		
		/tparam -	reference to the deallocateAll() method
		/r -		the method exists in the class
		*/
		template<typename U> static constexpr bool test(TCheck<U, &U::deallocateAll>*) { return YES; }
		
		/*
		If deallocateAll() was not found...
		
		/tparam -	reference to the deallocateAll() method
		/r -		the method does not exist
		*/
		template<typename U> static constexpr bool test(...) { return No; }
	public:
		/*
		The outcome of the search.
		
		/v YES : NO
		*/
		static constexpr bool value = test<T>(nullptr);
	};

	//===========================================================================================================================

	/*Checks a class for the reallocate(Block&, size_t) method.*/
	template<typename T>
	class has_reallocate
	{
	private:
		/*
		Checks for the reallocate(Block&, size_t) method.
		Helper struct that actually binds the method.
		
		/tparam - reference to the reallocate(Block&, size_t) method.
		*/
		template<typename U, void(U::*)(Block&, size_t)> struct TCheck;

		/*
		Tests the reallocate(Block&, size_t) method's existence.
		
		/tparam -	reference to the reallocate(Block&, size_t) method.
		/r -		the method exists in the class
		*/
		template<typename U> static constexpr bool test(TCheck<U, &U::reallocate>*) { return YES; }
		
		/*
		If reallocate(Block&, size_t) was not found...
		
		/tparam -	reference to the reallocate(Block&, size_t) method
		/r -		the method does not exist in the class
		*/
		template<typename U> static constexpr bool test(...) { return No; }
	public:
		/*
		The outcome of the search.
		
		/v - YES : NO
		*/
		static constexpr bool value = test<T>(nullptr);
	};

	//===========================================================================================================================

	/*Checks a class for the reallocateAll(size_t) method.*/
	template<typename T>
	class has_reallocate_all
	{
	private:
		/*
		Checks for the reallocateAll(size_t) method.
		Helper struct that actually finds the method.
		
		/tparam - reference to the reallocate(size_t) method
		*/
		template<typename U, void(U::*)(size_t)> struct TCheck;

		/*
		Tests the reallocateAll(size_t) method's existence.
		
		/tparam -	reference to the reallocateAll(size_t) method
		/r -		the method exists in the class
		*/
		template<typename U> static constexpr bool test(TCheck<U, &U::reallocateAll>*) { return YES; }
		
		/*
		If reallocate(size_t) was not found...
		
		/tparam -	reference to the reallocate(size_t) method
		/r -		the method was not found in the class
		*/
		template<typename U> static constexpr bool test(...) { return No; }
	public:
		/*
		The outcome of the search.
		
		/v - YES : NO
		*/
		static constexpr bool value = test<T>(nullptr);
	};

	//===========================================================================================================================

	/*Checks a class for the owns(Block) method.*/
	template<typename T>
	class has_owns
	{
	private:
		/*
		Checks for the owns(Block) method.
		Helper struct that actually finds the method.
		
		/tparam - reference to the owns(Block) method
		*/
		template<typename U, bool(U::*)(Block)> struct TCheck;

		/*
		Tests for owns(Block) method's existence.
		
		/tparam -	reference to the owns(Block) method
		/r -		the method exists in the class
		*/
		template<typename U> static constexpr bool test(TCheck<U, &U::owns>*) { return YES; }
		
		/*
		If owns(Block) was not found...
		
		/tparam -	reference to the owns(Block) method
		/r -		the method was not found in the class
		*/
		template<typename U> static constexpr bool test(...) { return No; }
	public:
		/*
		The outcome of the search.
		
		/r - YES : NO
		*/
		static constexpr bool value = test<T>(nullptr);
	};

	//===========================================================================================================================

	/*Checks a class for the expand(size_t) method.*/
	template<typename T>
	class has_expand
	{
	private:
		/*
		Checks for the expand(size_t) method.
		Helper struct that actually finds the method.
		
		/tparam - reference to the expand(size_t) method
		*/
		template<typename U, void(U::*)(size_t)> struct TCheck;

		/*
		Tests for expand(size_t) method's existence.
		
		/tparam -	reference to the expand(size_t) method
		/r -		the method exists in the class
		*/
		template<typename U> static constexpr bool test(TCheck<U, &U::owns>*) { return YES; }

		/*
		If expand(size_t) was not found...
		
		/tparam -	reference to the expand(size_t) method
		/r -		the method was not found in the class
		*/
		template<typename U> static constexpr bool test(...) { return No; }
	public:
		/*
		The outcome of the search.
		
		/r - YES : NO
		*/
		static constexpr bool value = test<T>(nullptr);
	};

	//===========================================================================================================================

	/*template<typename AllocatorOne, typename AllocatorTwo>
	struct have_same_base : std::false_type{};

	template<typename Allocator>
	struct have_same_base<Allocator, Allocator> : std::true_type{};*/

	//===========================================================================================================================

	/*
	////////////////////////////////////////////////////////////////////////////////////////
	///	Determines the appropriate implementation of the allocator's allocate(size_t) method
	///	relative to the method's existence.
	///
	///	If the allocate(size_t) method is found...
	///		-> use the allocators' implementation; return allocated block
	///	else...
	///		-> return a nullptr
	////////////////////////////////////////////////////////////////////////////////////////
	*/

	/*
	If the class tests positive for allocate(size_t), its implementation is used.
	
	/tparam -	allocator being tested
	/r -		the allocated block
	/*/
	template<typename Allocator, typename Enabled = void>
	struct _allocate_;

	template<typename Allocator>
	struct _allocate_
		<Allocator, typename std::enable_if<has_allocate<Allocator>::value>::type>
	{
		static Block execute(Allocator& allocator, size_t size)
		{
			return(allocator.allocate(size));
		}
	};

	/*
	The class tests positive for NOT having allocate(size_t)
	
	/tparam -	allocator being tested
	/r -		nullptr
	*/
	template<typename Allocator>
	struct _allocate_
		<Allocator, typename std::enable_if<!has_allocate<Allocator>::value>::type>
	{
		static Block execute(Allocator& allocator, size_t size)
		{
			return(nullptr);
		}
	};

	//===========================================================================================================================

	/*
	///////////////////////////////////////////////////////////////////////////////////////////
	///	Determines the appropriate implementation of the allocator's allocateAll(size_t) method
	///	relative to the method's existence.
	///
	///	If the allocateAll(size_t) method is found...
	///		-> use the allocator's implementation; return success of method
	///	else...
	///		-> return false
	///////////////////////////////////////////////////////////////////////////////////////////
	*/

	/*
	_allocateAll_ meta-function prototype
	
	/tparam - allocator being tested
	/tparam - does the method exist
	*/
	template<typename Allocator, typename Enabled = void>
	struct _allocateAll_;

	/*
	If the class tests positive for allocateAll(size_t), its implementation is used.
	
	/tparam -	allocator being tested
	/r -		the success of the allocator's implementation
	*/
	template<typename Allocator>
	struct _allocateAll_
		<Allocator, typename std::enable_if<has_allocate_all<Allocator>::value>::type>
	{
	static bool execute(Allocator& allocator, size_t size)
		{
			allocator.allocateAll(size);
		}
	};

	/*
	If the class tests positive for NOT having allocateAll(size_t), return false.
	
	/tparam -	allocator being tested
	/r -		false
	*/
	template<typename Allocator>
	struct _allocateAll_
		< Allocator, typename std::enable_if<!has_allocate_all<Allocator>::value>::type>
	{
		static bool execute(Allocator& allocator, size_t size)
		{
			return(false);
		}
	};

	//===========================================================================================================================

	/*
	//////////////////////////////////////////////////////////////////////////////////////////
	///	Determines the appropriate implementation of the allocator's deallocate(Block&) method
	///	relative to the method's existence
	///
	///	If the deallocate(Block&) method is found...
	///		-> use the allocator's implementation; return success of method
	///	else...
	///		-> do nothing
	//////////////////////////////////////////////////////////////////////////////////////////
	*/

	/*
	_deallocate_ meta-function prototype
	
	/tparam - allocator being tested
	/tparam - does the method exist
	*/
	template<typename Allocator, typename Enabled = void>
	struct _deallocate_;

	/*
	If the class tests positive for deallocate(Block&), its implementation is used.
	
	/tparam -	allocator being tested
	*/
	template<typename Allocator>
	struct _deallocate_
		<Allocator, typename std::enable_if<has_deallocate<Allocator>::value>::type>
	{
		static void execute(Allocator& allocator, Block& block)
		{
			allocate.deallocate(block);
		}
	};

	/*
	If the class tests positive for NOT having deallocate(Block&), do nothing
	
	/tparam -	allocator being tested
	*/
	template<typename Allocator>
	struct _deallocate_
		<Allocator, typename std::enable_if<!has_deallocate<Allocator>::value>::type>
	{
		static void execute(Allocator& allocator, Block& block)
		{
		}
	};

	//===========================================================================================================================

	/*
	///////////////////////////////////////////////////////////////////////////////////////
	///	Determines the appropriate implementation of the allocator's deallocateAll() method
	///	relative to the method's existence.
	///
	///	If the deallocateAll() method is found....
	///		-> use the allocator's implementation; return success of method
	///	else...
	///		-> return false
	///////////////////////////////////////////////////////////////////////////////////////
	*/

	/*
	_deallocateAll_ meta-function prototype
	
	/tparam - allocator being tested
	/tparam - does the method exist
	*/
	template<typename Allocator, typename Enabled = void>
	struct _deallocateAll_;

	/*
	If the class tests positive for deallocateAll(), its implementation is used.
	
	/tparam -	allocator being tested
	/r -		the success of the allocator's implementation
	*/
	template<typename Allocator>
	struct _deallocateAll_
		<Allocator, typename std::enable_if<has_deallocate_all<Allocator>::value>::type>
	{
		static bool execute(Allocator& allocator)
		{
			return(allocator.deallocateAll());
		}
	};

	/*
	If the class tests positive for NOT having deallocateAll(), return false.
	
	/tparam -		allocator being tested
	/r -			false
	*/
	template<typename Allocator>
	struct _deallocateAll_
		<Allocator, typename std::enable_if<!has_deallocate_all<Allocator>::value>::type>
	{
		static bool execute(Allocator& allocator)
		{
			return(false);
		}
	};

	//===========================================================================================================================

	/*
	//////////////////////////////////////////////////////////////////////////////////////////////////
	///	Determines the appropriate implementation of the allocator's reallocate(Block&, size_t) method
	///	relative to the method's existence.
	///
	///	If the reallocate(Block&, size_t) method is found...
	///		-> use the allocator's implementation; return success of method
	///	else...
	///		-> return false
	//////////////////////////////////////////////////////////////////////////////////////////////////
	*/

	/*
	_reallocate_ meta-function prototype
	
	/tparam - allocator being tested
	/tparam - does the method exist
	*/
	template<typename Allocator, typename Enabled = void>
	struct _reallocate_;

	/*
	If the class tests positive for reallocate(Block&, size_t), its implementation is used.
	
	/tparam -	allocator being tested
	/r -		the success of the allocator's implementation
	*/
	template<typename Allocator>
	struct _reallocate_
		<Allocator, typename std::enable_if<has_reallocate<Allocator>::value>::type>
	{
		static bool execute(Allocator& allocator, Block& block, size_t newSize)
		{
			return(allocate.reallocate(block, newSize));
		}
	};

	/*
	If the class tests positive for NOT having reallocate(Block&, size_t), return false
	
	/tparam -	allocator being tested
	/r -		false
	*/
	template<typename Allocator>
	struct _reallocate_
		<Allocator, typename std::enable_if<!has_reallocate<Allocator>::value>::type>
	{
		static bool execute(Allocator& allocator, Block& block, size_t newSize)
		{
			return(false);
		}
	};

	//===========================================================================================================================

	/*
	/////////////////////////////////////////////////////////////////////////////////////////////
	///	Determines the appropriate implementation of the allocator's reallocateAll(size_t) method
	///	relative to the method's existence.
	///
	///	If the reallocateAll(size_t) method is found...
	///		-> use the allocator's implementation; return success of the method
	///	else...
	///		-> return false
	/////////////////////////////////////////////////////////////////////////////////////////////
	*/

	/*
	_reallocateAll_ meta-function prototype
	
	/tparam - allocator being tested
	/tparam - does the method exist
	*/
	template<typename Allocator, typename Enabled = void>
	struct _reallocateAll_;

	/*
	If the class tests positive for reallocateAll(size_t), its implementation is used.

	/tparam -	allocator being tested
	/r -		the success of the allocator's implementation
	*/

	template<typename Allocator>
	struct _reallocateAll_
		<Allocator, typename std::enable_if<has_reallocate_all<Allocator>::value>::type>
	{
		static bool execute(Allocator& allocator, size_t newSize)
		{
			return(allocator.reallocateAll(newSize));
		}
	};

	/*
	If the class tests positive for NOT having reallocateAll(size_t), return false.
	
	/tparam -	allocator being tested
	/r -		false
	*/
	template<typename Allocator>
	struct _reallocateAll_
		<Allocator, typename std::enable_if<!has_reallocate_all<Allocator>::value>::type>
	{
		static bool execute(Allocator& allocator, size_t newSize)
		{
			return(false);
		}
	};

	//===========================================================================================================================

	/*
	///////////////////////////////////////////////////////////////////////////////////
	///	Determines the appropriate implementation of the allocator's owns(Block) method
	///	relative to the method's existence.
	///
	///	If the owns(Block) method is found...
	///		-> use the allocator's implementation; return success of method
	///	else...
	///		-> return false
	///////////////////////////////////////////////////////////////////////////////////
	*/

	/*
	_owns_ meta-function prototype
	
	/tparam - allocator being tested
	/tparam - does the method exist
	*/
	template<typename Allocator, typename Enabled = void>
	struct _owns_;

	/*
	If the class tests position for owns(Block), its implementation is used.
	
	/tparam -	allocator being used
	/r -		the success of the allocator's implementation
	*/
	template<typename Allocator>
	struct _owns_
		<Allocator, typename std::enable_if<has_owns<Allocator>::value>::type>
	{
		static bool execute(Allocator& allocator, Block block)
		{
			return(allocator.owns(block));
		}
	};

	/*
	If the class tests position for NOT having owns(Block), return false.
	
	/tparam -	allocator being tested
	/r -		false
	*/
	template<typename Allocator>
	struct _owns_
		<Allocator, typename std::enable_if<!has_owns<Allocator>::value>::type>
	{
		static bool execute(Allocator& allocator, Block block)
		{
			return(false);
		}
	};

	//===========================================================================================================================

	/*
	/////////////////////////////////////////////////////////////////////////////////////
	///	Determines the appropriate implementation of the allocators expand(size_t) method
	///	relative to the method's existence.
	///
	///	If the expand(size_t) method is found...
	///		-> use the allocator's implementation; return success of method
	///	else...
	///		-> return false
	/////////////////////////////////////////////////////////////////////////////////////
	*/

	/*
	_expand_ meta-function prototype
	
	/tparam - allocator being tested
	/tparam - does the method exist
	*/
	template<typename Allocator, typename Enabled = void>
	struct _expand_;

	/*
	If the class tests positive for expand(size_t), its implementation is used.

	/tparam - allocator being tested
	*/
	template<typename Allocator>
	struct _expand_
		<Allocator, typename std::enable_if<has_expand<Allocator>::value>::type>
	{
		static void execute(Allocator& allocator, size_t amount)
		{
			allocator.expand(amount);
		}
	};

	/*
	If the class tests positive for NOT having expand(size_t), do nothing.
	
	/tparam - allocator being tested
	*/
	template<typename Allocator>
	struct _expand_
		<Allocator, typename std::enable_if<!has_expand<Allocator>::value>::type>
	{	
		static void execute(Allocator& allocator, size_t amount)
		{
		}
	};
}