/**
 * This work copyright Chao Sun(qq:296449610) and licensed under
 * a Creative Commons Attribution 3.0 Unported License(https://creativecommons.org/licenses/by/3.0/).
 */

#include "../../../../../common/mem-pool.h"
#include "../../../../../common/buffer.h"

#include "net-stack-msg-worker.h"
#include "../../../../../common/common-utils.h"

namespace netty {
    namespace net {
        ANetStackMessageWorker::ANetStackMessageWorker(common::MemPool *memPool, uint32_t maxCacheMessageCnt) {
            m_pMemPool = memPool;
            m_bqMessages = new common::BlockingQueue<SndMessage*>(maxCacheMessageCnt);
            auto size = RcvMessage::HeaderSize();
            auto headerMemObj = m_pMemPool->Get(size);
            m_pHeaderBuffer = common::CommonUtils::GetNewBuffer(headerMemObj, size);
        }

        ANetStackMessageWorker::~ANetStackMessageWorker() {
            m_bqMessages->Clear();
            delete m_bqMessages;
        }

        bool ANetStackMessageWorker::SendMessage(SndMessage *m) {
            auto ret = m_bqMessages->TryPush(m);
            if (!ret) {
                return ret;
            }
        }

        void ANetStackMessageWorker::HandleMessage(RcvMessage *m) {
            auto pCb = RcvMessage::LookupCallback(m->GetId());
            if (pCb) {
                pCb->first(m, pCb->second);
            } else {
                delete m;
            }
        }
    } // namespace net
} // namespace netty