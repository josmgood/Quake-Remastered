//#include "..\Include\smart_ptr.hpp"
//
//template<typename Type>
//SmartPtr<Type>::SmartPtr()
//	: _ptr(nullptr)
//{
//}
//
//template<typename Type>
//SmartPtr<Type>::SmartPtr(const Type& value)
//	: _ptr(value)
//{
//}
//
//template<typename Type>
//SmartPtr<Type>::SmartPtr(Type* ptr)
//	: _ptr(ptr)
//{
//}
//
//template<typename Type>
//SmartPtr<Type>::~SmartPtr()
//{
//	release();
//}
//
//template<typename Type>
//Type& SmartPtr<Type>::operator*() const
//{
//	return(_ptr);
//}
//
//template<typename Type>
//void SmartPtr<Type>::set(const Type& value)
//{
//	_ptr = value;
//}
//
//template<typename Type>
//void SmartPtr<Type>::set(Type* ptr)
//{
//	_ptr = ptr;
//}
//
//template<typename Type>
//Type* SmartPtr<Type>::get() const
//{
//	return(_ptr);
//}
//
//template<typename Type>
//void SmartPtr<Type>::release()
//{
//	delete _ptr;
//}
//
//template<typename Type>
//SmartPtr<Type>::operator bool() const
//{
//	return(_ptr != nullptr);
//}