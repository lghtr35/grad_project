#include "inet/common/MessageDispatcher.h"
#include "inet/applications/common/SocketTag_m.h"
#include "inet/common/ProtocolTag_m.h"
#include "inet/linklayer/common/InterfaceTag_m.h"
#include <vector>

using namespace inet;
        class RandomisedMessageDispatcher : public MessageDispatcher
        {
            protected:
            int wlanInterfaceCount = 0;
            std::vector<int> wlanIds;

            virtual void initialize() override;

            public:
            int selectedWlan;
            virtual cGate *handlePacket(Packet *packet, cGate *inGate) override;
            virtual cGate *handleMessage(Message *message, cGate *inGate) override;
            virtual void handleRegisterInterface(const InterfaceEntry &interface, cGate *out,cGate *in) override;
        };



