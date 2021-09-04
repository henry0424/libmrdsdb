/**
* @brief Database Exception
* @author Henry Tsai
* @date 2020-12-04
* @version 1.0
*/

#ifndef LIBMRDSDB_EXCEPTION_H
#define LIBMRDSDB_EXCEPTION_H

#include <exception>

namespace Database::Exception
{
    
    class ConnectException : public std::exception
    {
    public:
        virtual const char *what() const throw()
        {
            return "Connect Error.";
        }
    };

    class NoDataException : public std::exception
    {
    public:
        virtual const char *what() const throw()
        {
            return "No Data Error.";
        }
    };

    class QueryException : public std::exception
    {
    public:
        virtual const char *what() const throw()
        {
            return "Query Error.";
        }
    };

    class NonImplException : public std::exception
    {
    public:
        virtual const char *what() const throw()
        {
            return "Non Implement Error.";
        }
    };

} // namespace imcs::exception::database

#endif