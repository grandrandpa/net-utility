/**
 * This work copyright Chao Sun(qq:296449610) and licensed under
 * a Creative Commons Attribution 3.0 Unported License(https://creativecommons.org/licenses/by/3.0/).
 */

#ifndef NET_CORE_POSIX_TCP_CONNECTION_EVENT_HANDLER_H
#define NET_CORE_POSIX_TCP_CONNECTION_EVENT_HANDLER_H

#include "ievent-handler.h"

namespace net {
class PosixTcpConnectionEventHandler : public IEventHandler {
public:
    virtual int HandleReadEvent() override;
    virtual int HandleWriteEvent() override;
};
}

#endif //NET_CORE_POSIX_TCP_CONNECTION_EVENT_HANDLER_H