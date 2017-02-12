//
// Copyright (c) 2013-2017 Christoph Malek
// See LICENSE for more information.
//

#ifndef MLK_JSONCPP_UTILS_JSON_ARRAY_H
#define MLK_JSONCPP_UTILS_JSON_ARRAY_H

#include <jsoncpp/json/value.h>

namespace mlk
{
	namespace json
	{
		// a shortcut for Json::Value{Json::arrayValue}
		struct array : public Json::Value
		{
			array() : Json::Value{Json::arrayValue} {}
		};
	}
}

#endif// MLK_JSONCPP_UTILS_JSON_ARRAY_H
