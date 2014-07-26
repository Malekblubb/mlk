//
// Copyright (c) 2013-2014 Christoph Malek
// See LICENSE for more information.
//

#ifndef MLK_JSONCPP_UTILS_JSON_ARRAY_H
#define MLK_JSONCPP_UTILS_JSON_ARRAY_H


#include <jsoncpp/json/value.h>


// a shortcut for Json::Value{Json::arrayValue}
struct json_array : public Json::Value
{
	json_array() :
		Json::Value{Json::arrayValue}
	{ }
};


#endif // MLK_JSONCPP_UTILS_JSON_ARRAY_H 
