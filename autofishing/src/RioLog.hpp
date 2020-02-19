#ifndef _RIO_LOG_
#define _RIO_LOG_
//#define BOOST_LOG_DYN_LINK 1
#include "singleton.h"
#include <ctime>
#include <cstddef>
#include <string>
#include <ostream>
#include <fstream>
#include <iomanip>
#include <iostream>

#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/smart_ptr/make_shared_object.hpp>
#include <boost/phoenix/bind.hpp>

#include <boost/log/support/date_time.hpp>
#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/attributes.hpp>
#include <boost/log/sources/basic_logger.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/severity_channel_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/sinks/sync_frontend.hpp>
#include <boost/log/sinks/text_ostream_backend.hpp>
#include <boost/log/attributes/scoped_attribute.hpp>
#include <boost/log/utility/value_ref.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>

//#include <boost/asio.hpp>
//#include <boost/bind.hpp>
//#include <boost/date_time/posix_time/posix_time.hpp>

#define LOG_DBG\
    BOOST_LOG_SEV(RioLog::Instance()->GetLogger(), debug) <<"["<<__FILE__<<":"<<__LINE__<<"] "

#define LOG_INFO\
    BOOST_LOG_SEV(RioLog::Instance()->GetLogger(), info) <<" ["<<__FILE__<<":"<<__LINE__<<"] "

#define LOG_ERR\
    BOOST_LOG_SEV(RioLog::Instance()->GetLogger(), error) <<"["<<__FILE__<<":"<<__LINE__<<"] "

namespace logging = boost::log;
namespace src = boost::log::sources;
namespace expr = boost::log::expressions;
namespace sinks = boost::log::sinks;
namespace attrs = boost::log::attributes;
namespace keywords = boost::log::keywords;

// We define our own severity levels
enum severity_level
{
    debug,
    info,
    error
};

BOOST_LOG_ATTRIBUTE_KEYWORD(severity, "Severity", severity_level)
// std::ostream& operator<< (std::ostream& strm, severity_level level)
// {
//     static const char* strings[] =
//     {
//         "DEBUG",
//         "INFO",
//         "ERROR"
//     };

//     if (static_cast< std::size_t >(level) < sizeof(strings) / sizeof(*strings))
//         strm << strings[level];
//     else
//         strm << static_cast< int >(level);

//     return strm;
// }

typedef src::severity_logger< severity_level > SLG;
class RioLog : public singleton<RioLog>
{
    public:
        void Init()
        {
            // Setup the common formatter for all sinks
            logging::formatter fmt = expr::stream
                << expr::format_date_time< boost::posix_time::ptime >("TimeStamp", "%Y-%m-%d,%H:%M:%S.%f ")
                << severity << " "
                << expr::smessage;

            // Initialize sinks
            typedef sinks::synchronous_sink< sinks::text_ostream_backend > text_sink;
            boost::shared_ptr< text_sink > sink = boost::make_shared< text_sink >();

            sink->locked_backend()->add_stream(
                    boost::make_shared< std::ofstream >("../log/FullLog.log", std::ios::app));

            sink->locked_backend()->auto_flush();

            sink->set_formatter(fmt);

            logging::core::get()->add_sink(sink);

            sink = boost::make_shared< text_sink >();

            sink->locked_backend()->add_stream(
                    boost::make_shared< std::ofstream >("../log/Error.log", std::ios::app));

            sink->set_formatter(fmt);

            sink->locked_backend()->auto_flush();

            sink->set_filter(severity >= error);

            logging::core::get()->add_sink(sink);

            logging::add_common_attributes();
        }

        SLG& GetLogger()
        {
            return slg;
        }
        


        SLG slg;
};

#endif
