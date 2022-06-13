#include <omnetpp.h>

#include "inet/applications/udpapp/UdpBasicApp.h"
#include "inet/applications/base/ApplicationPacket_m.h"
#include "inet/common/ModuleAccess.h"
#include "inet/common/TagBase_m.h"
#include "inet/common/TimeTag_m.h"
#include "inet/common/lifecycle/ModuleOperations.h"
#include "inet/common/packet/Packet.h"
#include "inet/networklayer/common/FragmentationTag_m.h"
#include "inet/networklayer/common/L3AddressResolver.h"
#include "inet/transportlayer/contract/udp/UdpControlInfo_m.h"
#include "SelectedInterface.cc"

using namespace inet;

class CustomApp : public UdpBasicApp {
    int layer;
    int selectedInterface;

    virtual void initialize(int stage) override;
    virtual L3Address chooseDestAddr(Packet* pk);
    virtual void sendPacket() override;
};


Define_Module(CustomApp);

void CustomApp::initialize(int stage) {
    UdpBasicApp::initialize(stage);

    layer = par("layer");
}

L3Address CustomApp::chooseDestAddr(Packet* pk) {
    int k;
    auto realInterface = pk->findTag<SelectedInterface>();
    if(realInterface != nullptr){
        k = realInterface->num;
    }else{
        k = layer % destAddresses.size();
    }
    selectedInterface = k;

    if (destAddresses[k].isUnspecified() || destAddresses[k].isLinkLocal()) {
        L3AddressResolver().tryResolve(destAddressStr[k].c_str(), destAddresses[k]);
    }

    std::cout << "Sending from custom app with layer " << k << " to address " << destAddresses[k] << std::endl;

    return destAddresses[k];
}

void CustomApp::sendPacket()
{
    std::ostringstream str;
    str << packetName << "-" << numSent;
    Packet *packet = new Packet(str.str().c_str());
    if(dontFragment)
        packet->addTag<FragmentationReq>()->setDontFragment(true);
    const auto& payload = makeShared<ApplicationPacket>();
    payload->setChunkLength(B(par("messageLength")));
    payload->setSequenceNumber(numSent);
    payload->addTag<CreationTimeTag>()->setCreationTime(simTime());
    packet->insertAtBack(payload);
    L3Address destAddr = chooseDestAddr(packet);
    emit(packetSentSignal, packet);
    socket.sendTo(packet, destAddr, destPort);
    numSent++;
}
