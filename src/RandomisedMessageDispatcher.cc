#include <string>
#include <algorithm>
#include "RandomisedMessageDispatcher.h"
#include <omnetpp.h>
#include "inet/networklayer/common/L3AddressTag_m.h"

using namespace inet;
Define_Module(RandomisedMessageDispatcher);

    void RandomisedMessageDispatcher::initialize()
    {
        srand(time(0));
        WATCH_MAP(socketIdToGateIndex);
        WATCH_MAP(interfaceIdToGateIndex);
        WATCH_MAP(serviceToGateIndex);
        WATCH_MAP(protocolToGateIndex);
        wlanInterfaceCount = par("wlanInterfaceCount");
        this->selectedWlan = par("selectedWlan");
        std::cout<<wlanInterfaceCount<<std::endl;
    }

    cGate * RandomisedMessageDispatcher::handleMessage(Message* message, cGate* inGate)
    {
        std::cout<<"Message"<<std::endl;
        auto socketReq = message->findTag<SocketReq>();
        if (socketReq != nullptr) {
            int socketReqId = socketReq->getSocketId();
            auto it = socketIdToGateIndex.find(socketReqId);
            if (it == socketIdToGateIndex.end())
                socketIdToGateIndex[socketReqId] = inGate->getIndex();
            else if (it->first != socketReqId)
                throw cRuntimeError("handleMessage(): Socket is already registered: id = %d, gate = %d, new gate = %d", socketReqId, it->second, inGate->getIndex());
        }
        auto socketInd = message->findTag<SocketInd>();
        if (socketInd != nullptr) {
            int socketId = socketInd->getSocketId();
            auto it = socketIdToGateIndex.find(socketId);
            if (it != socketIdToGateIndex.end())
                return gate("out", it->second);
            else
                throw cRuntimeError("handleMessage(): Unknown socket, id = %d", socketId);
        }
        auto dispatchProtocolReq = message->findTag<DispatchProtocolReq>();;
        if (dispatchProtocolReq != nullptr) {
            auto servicePrimitive = dispatchProtocolReq->getServicePrimitive();
            // TODO: KLUDGE: eliminate this by adding ServicePrimitive to every DispatchProtocolReq
            if (servicePrimitive == static_cast<ServicePrimitive>(-1))
                servicePrimitive = SP_REQUEST;
            auto protocol = dispatchProtocolReq->getProtocol();
            auto it = serviceToGateIndex.find(Key(protocol->getId(), servicePrimitive));
            if (it != serviceToGateIndex.end())
                return gate("out", it->second);
            else
                throw cRuntimeError("handleMessage(): Unknown protocol: id = %d, name = %s", protocol->getId(), protocol->getName());
        }
        auto interfaceReq = message->findTag<InterfaceReq>();
        if (interfaceReq != nullptr) {
            int interfaceId = interfaceReq->getInterfaceId();
            auto it = interfaceIdToGateIndex.find(interfaceId);
            if (it != interfaceIdToGateIndex.end())
                return gate("out", it->second);
            else
                throw cRuntimeError("handleMessage(): Unknown interface: id = %d", interfaceId);
        }
        throw cRuntimeError("handleMessage(): Unknown message: %s(%s)", message->getName(), message->getClassName());
    }

    cGate *RandomisedMessageDispatcher::handlePacket(Packet *packet, cGate *inGate)
    {
        std::cout<<"Packet"<<std::endl;
        auto socketInd = packet->findTag<SocketInd>();
        if (socketInd != nullptr) {
            int socketId = socketInd->getSocketId();
            std::cout<<"socketID"<<socketId<<std::endl;
            auto it = socketIdToGateIndex.find(socketId);
            if (it != socketIdToGateIndex.end())
                return gate("out", it->second);
            else
                throw cRuntimeError("handlePacket(): Unknown socket, id = %d", socketId);
        }
        auto dispatchProtocolReq = packet->findTag<DispatchProtocolReq>();;
        if (dispatchProtocolReq != nullptr) {
            auto packetProtocolTag = packet->findTag<PacketProtocolTag>();;
            auto servicePrimitive = dispatchProtocolReq->getServicePrimitive();
            // TODO: KLUDGE: eliminate this by adding ServicePrimitive to every DispatchProtocolReq
            if (servicePrimitive == static_cast<ServicePrimitive>(-1)) {
                if (packetProtocolTag != nullptr && dispatchProtocolReq->getProtocol() == packetProtocolTag->getProtocol())
                    servicePrimitive = SP_INDICATION;
                else
                    servicePrimitive = SP_REQUEST;
            }
            auto protocol = dispatchProtocolReq->getProtocol();
            auto it = serviceToGateIndex.find(Key(protocol->getId(), servicePrimitive));
            std::cout<<"dispatchProtocolId"<<it->second<<std::endl;
            if (it != serviceToGateIndex.end())
                return gate("out", it->second);
            else
                throw cRuntimeError("handlePacket(): Unknown protocol: id = %d, name = %s", protocol->getId(), protocol->getName());
        }
        auto interfaceReq = packet->findTag<InterfaceReq>();
        if (interfaceReq != nullptr) {
            int interfaceId = interfaceReq->getInterfaceId();

            auto it = interfaceIdToGateIndex.find(interfaceId);
            if (it != interfaceIdToGateIndex.end())
            {
                if (this->selectedWlan < 0) {
                    int randomInterface = (rand()%wlanInterfaceCount) + 2;
                    return gate("out", randomInterface);
                } else {
                    std::cout << "Sending from selected wlan " << selectedWlan << std::endl << std::endl;
                    return gate("out", this->selectedWlan + 2);
                }
            }
            else
                throw cRuntimeError("handlePacket(): Unknown interface: id = %d", interfaceId);
        }
        throw cRuntimeError("handlePacket(): Unknown packet: %s(%s)", packet->getName(), packet->getClassName());
    }

    void RandomisedMessageDispatcher::handleRegisterInterface(const InterfaceEntry &interface, cGate *out, cGate *in)
    {
        Enter_Method("handleRegisterInterface");
        if (interfaceIdToGateIndex.find(interface.getInterfaceId()) != interfaceIdToGateIndex.end())
            throw cRuntimeError("handleRegisterInterface(): Interface is already registered: %s", interface.str().c_str());
        std::string iName = interface.getInterfaceName();
        if(iName.find("wlan")!=std::string::npos && wlanIds.end()==std::find(wlanIds.begin(),wlanIds.end(),out->getIndex()))
        {
            this->wlanIds.push_back(out->getIndex());
            //Ieee80211ScalarRadio radio = interface.getSubmodule("radio", 0);
        }
        interfaceIdToGateIndex[interface.getInterfaceId()] = out->getIndex();
        int size = gateSize("out");
        for (int i = 0; i < size; i++)
            if (i != in->getIndex())
                registerInterface(interface, gate("in", i), gate("out", i));
    }

