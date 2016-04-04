//#include "..\Include\file.h"
//
//File::File()
//	: _name(), _position()
//{
//}
//
//File::File(std::ifstream& input, size_t position)
//	: _name(), _position(position)
//{
//	_name << input;
//}
//
//File::File(const String& name, size_t position)
//	: _name(name), _position(position)
//{
//}
//
//void File::open(const String& name)
//{
//	_name = name;
//}
//
//void File::setPosition(size_t position)
//{
//	_position = position;
//}
//
//void File::clear()
//{
//	_name.clear();
//	_position = 0;
//}
//
//const String& File::name() const
//{
//	return _name;
//}
//
//size_t File::position() const
//{
//	return _position;
//}