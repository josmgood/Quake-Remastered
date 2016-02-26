//#pragma once
//
//template<typename Type>
//class SmartPtr
//{
//public:
//	SmartPtr();
//	SmartPtr(const Type& value);
//	SmartPtr(Type* ptr);
//	~SmartPtr();
//
//	Type& operator*() const;
//	void set(const Type& value);
//	void set(Type* ptr);
//	Type* get() const;
//	void release();
//
//	operator bool() const;
//private:
//	Type* _ptr;
//};
//
//#include "..\Source\smart_ptr.inl"