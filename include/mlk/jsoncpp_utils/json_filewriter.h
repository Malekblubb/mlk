//
// Copyright (c) 2013-2017 Christoph Malek
// See LICENSE for more information.
//

#ifndef MLK_JSONCPP_UTILS_JSON_FILEWRITER_H
#define MLK_JSONCPP_UTILS_JSON_FILEWRITER_H

#include <jsoncpp/json/value.h>
#include <jsoncpp/json/writer.h>

#include <fstream>
#include <string>

namespace mlk
{
	namespace json
	{
		namespace internal
		{
			template <typename WriterType>
			class json_filewriter : public WriterType
			{
				std::ofstream m_stream;
				std::string m_writer_output;

			public:
				json_filewriter() : WriterType{} {}

				bool write_to_file(const Json::Value& root,
								   const std::string& filepath)
				{
					// clear old output
					m_writer_output.clear();

					// open file (override)
					m_stream.open(filepath);
					if(!m_stream.is_open()) return false;

					m_writer_output = this->write(root);
					m_stream << m_writer_output;
					m_stream.close();
					return true;
				}

				const std::string& writer_output() const noexcept
				{
					return m_writer_output;
				}
			};
		}

		using fast_filewriter = internal::json_filewriter<Json::FastWriter>;
		using styled_filewriter = internal::json_filewriter<Json::StyledWriter>;
	}
}

#endif// MLK_JSONCPP_UTILS_JSON_FILEWRITER_H
