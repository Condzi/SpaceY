/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include <Core/Exception.hpp>

#if defined _MSC_VER
#define __func__ __FUNCTION__
#endif //_MSC_VER

#define CON_ASSERT( condition, message ) \
{ \
	if(! ( condition ) ) \
	{ \
		throw con::BaseException( __FILE__, __func__, __LINE__, #condition, message );\
	} \
}

#define CON_STATIC_ASSERT static_assert