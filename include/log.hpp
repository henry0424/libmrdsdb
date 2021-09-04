/**
* @brief Log Tool
* @author Henry Tsai
* @date 2021-01-19
* @version 1.1
*/

#ifndef LIBMRDSDB_LOG_H
#define LIBMRDSDB_LOG_H

#include <iostream>

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>

namespace Database::Log
{
    using namespace boost::log::trivial;

    enum LogOutput
    {
        NOUSE = 0b00,
        SCEEN = 0b01,
        FILE = 0b10
    };

    class LogTool
    {

    public:
        static void _log_init(const int output = (int)LogOutput::NOUSE, const std::string logDir = "log", const std::string fileName = "")
        {
            boost::log::register_simple_formatter_factory<boost::log::trivial::severity_level, char>("Severity");
            //std::string logFormat = "[%TimeStamp%] (%LineID%) [%ProcessID%] [%Severity%]:%Message%";
            std::string log_format = "[%TimeStamp%] (%LineID%) [%ProcessID%] [%Severity%]:%Message%";
            if ((output | LogOutput::SCEEN) & LogOutput::FILE)
            {
                auto pid = getpid();
                boost::log::add_file_log(
                    boost::log::keywords::file_name = logDir + "/%Y-%m-%d_%H:%M:%S#%N#[" + std::to_string(pid) + "]" + fileName + ".log",
                    boost::log::keywords::rotation_size = 10 * 1024 * 1024,
                    boost::log::keywords::time_based_rotation = boost::log::sinks::file::rotation_at_time_point(0, 0, 0),
                    boost::log::keywords::auto_flush = true,
                    boost::log::keywords::format = log_format,
                    boost::log::keywords::open_mode = std::ios_base::app);
            }
            if ((output | LogOutput::FILE) & LogOutput::SCEEN)
            {
                boost::log::add_console_log(std::cout, boost::log::keywords::format = log_format);
            }

            boost::log::add_common_attributes();
        }

        static void _set_filter_level(boost::log::trivial::severity_level level)
        {
            boost::log::core::get()->reset_filter();
            boost::log::core::get()->set_filter(boost::log::trivial::severity >= level);
        }

        static void _log(const std::string message, boost::log::trivial::severity_level messageLevel = boost::log::trivial::info)
        {
            static boost::log::sources::severity_logger_mt<boost::log::trivial::severity_level> logger;
            _draw_color_(messageLevel);
            BOOST_LOG_SEV(logger, messageLevel) << message;
            _clean_draw_color_();
        }

        static void _log(const std::string message, const std::string owner, boost::log::trivial::severity_level messageLevel = boost::log::trivial::info)
        {
            static boost::log::sources::severity_logger_mt<boost::log::trivial::severity_level> logger;
            _draw_color_(messageLevel);
            BOOST_LOG_SEV(logger, messageLevel) << " [" << owner << "] " << message;
            _clean_draw_color_();

        }

    protected:
        LogTool(/* args */)
        {
        }

        ~LogTool() = default;

    private:
        static void _draw_color_(boost::log::trivial::severity_level messageLevel) {
            switch (messageLevel) {
                case boost::log::trivial::warning:
                    std::cout << "\033[33m";
                    break;
                case boost::log::trivial::error:
                    std::cout << "\033[31m";
                    break;
                case boost::log::trivial::fatal:
                    std::cout << "\033[31m";
                    break;
                default:
                    std::cout << "\033[0m";
                    break;
            }
        }

        static void _clean_draw_color_() {
            std::cout << "\033[0m";
        }
    };
} // namespace Gyro

#endif