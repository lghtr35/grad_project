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

using namespace inet;

class CustomApp : public UdpBasicApp {
    int layer;

    virtual void initialize(int stage) override;
    virtual L3Address chooseDestAddr() override;
};

Define_Module(CustomApp);

void CustomApp::initialize(int stage) {
    UdpBasicApp::initialize(stage);

    layer = par("layer");
}

L3Address CustomApp::chooseDestAddr() {
    int k = layer % destAddresses.size();

    if (destAddresses[k].isUnspecified() || destAddresses[k].isLinkLocal()) {
        L3AddressResolver().tryResolve(destAddressStr[k].c_str(), destAddresses[k]);
    }

    std::cout << "Sending from custom app with layer " << layer << " to address " << destAddresses[k] << std::endl;

    return destAddresses[k];
}
