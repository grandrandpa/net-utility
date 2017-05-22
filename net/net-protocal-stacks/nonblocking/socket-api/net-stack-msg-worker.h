/**
 * This work copyright Chao Sun(qq:296449610) and licensed under
 * a Creative Commons Attribution 3.0 Unported License(https://creativecommons.org/licenses/by/3.0/).
 */

#ifndef NET_CORE_NETSTACKMESSAGEWORKER_H
#define NET_CORE_NETSTACKMESSAGEWORKER_H

#include "../../../../common/common-def.h"
#include "../../../../common/blocking-queue.h"
#include "../../../message.h"

namespace netty {
    namespace net {
        /**
         * 本类负责对message的处理。具体的socket实现类要继承于此类。
         * 事件管理器有事件了会调用读写。
         */
        class GCC_INTERNAL ANetStackMessageWorker {
        public:
            /**
             *
             * @param maxCacheMessageCnt 消息缓冲队列的最大消息个数。0为无限制。
             */
            ANetStackMessageWorker(uint32_t maxCacheMessageCnt = 0);
            ~ANetStackMessageWorker();
            /**
             *
             */
            bool SendMessage(Message *m);

            void HandleMessage();

            /**
             * 错误: 返回false(无论是[socket错误或对端关闭]还是[codec校验错误])
             * 正常: 返回true(即便是遇到了EAGAIN，只要没有发生错误)
             * @return
             */
            virtual bool Recv() = 0;

            /**
             * 发送缓冲队列里面的数据。
             * @return
             */
            virtual bool Write() = 0;

        private:
            common::BlockingQueue<Message*> m_bqMessages;

        };
    } // namespace net
} // namespace netty

#endif //NET_CORE_NETSTACKMESSAGEWORKER_H