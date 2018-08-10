#define BOOST_LOG_DYN_LINK 1
#ifndef __RIO_TICK__
#define __RIO_TICK__

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <functional>
#include <vector>

#include "singleton.h"

typedef boost::asio::deadline_timer TIMER;
typedef void(*HANDLER)(void);
typedef std::function<void(const boost::system::error_code&)> WHANDLER;

class RioTick : public singleton<RioTick>
{
    public:
        RioTick():_iTimerCount(0)
    {

    }

        void DeclareTick(HANDLER handler, unsigned int iSecond)
        {
            std::shared_ptr<TIMER> pTimer(new TIMER(_io, boost::posix_time::seconds(iSecond)));
            int iTimerID = _iTimerCount + 1;
            WHANDLER *wHandler = new WHANDLER([this, handler, iSecond, wHandler, pTimer, iTimerID](const boost::system::error_code&)
            {
                (*handler)();
                pTimer->expires_at(pTimer->expires_at() + boost::posix_time::seconds(iSecond));
                pTimer->async_wait(*(_vec[iTimerID - 1]));
            });

            _vec.push_back(wHandler);
            ++_iTimerCount;
            pTimer->async_wait(*wHandler);
        }

        void Run()
        {
           _io.run();
        }

        void Stop()
        {
            _io.stop();
        }

    private:
        unsigned int _iTimerCount;
        std::vector<WHANDLER*> _vec;
        boost::asio::io_service _io;

};


#endif
