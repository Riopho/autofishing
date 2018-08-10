#include <ctime>
#include <cstddef>
#include <string>
#include <ostream>
#include <fstream>
#include <iomanip>

#define BOOST_LOG_DYN_LINK 1
#include <boost/log/support/date_time.hpp>
#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/smart_ptr/make_shared_object.hpp>
#include <boost/phoenix/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
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
#define LOG_DBG\
    BOOST_LOG_SEV(slg, debug) <<"["<<__FILE__<<":"<<__LINE__<<"] "

#define LOG_INFO\
    BOOST_LOG_SEV(slg, info) <<" ["<<__FILE__<<":"<<__LINE__<<"] "

#define LOG_ERROR\
    BOOST_LOG_SEV(slg, error) <<"["<<__FILE__<<":"<<__LINE__<<"] "

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

// The operator puts a human-friendly representation of the severity level to the stream
std::ostream& operator<< (std::ostream& strm, severity_level level)
{
    static const char* strings[] =
    {
        "DEBUG",
        "INFO",
        "ERROR"
    };

    if (static_cast< std::size_t >(level) < sizeof(strings) / sizeof(*strings))
        strm << strings[level];
    else
        strm << static_cast< int >(level);

    return strm;
}

//[ example_tutorial_filtering
BOOST_LOG_ATTRIBUTE_KEYWORD(severity, "Severity", severity_level)

void init()
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
        boost::make_shared< std::ofstream >("FullLog.log"));

    sink->set_formatter(fmt);

    logging::core::get()->add_sink(sink);

    sink = boost::make_shared< text_sink >();

    sink->locked_backend()->add_stream(
        boost::make_shared< std::ofstream >("Error.log"));

    sink->set_formatter(fmt);

    sink->set_filter(severity >= error);

    logging::core::get()->add_sink(sink);

    logging::add_common_attributes();
}

void logging_function()
{
    src::severity_logger< severity_level > slg;

    LOG_DBG<<"A debug message";
    LOG_INFO<< "info message";
    LOG_ERROR<< "error message";
}

int main(int, char*[])
{
    init();

    logging_function();

    return 0;
}
