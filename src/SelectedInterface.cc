#include <omnetpp.h>
#include "inet/common/TagBase_m.h" // import inet.common.TagBase

using namespace inet;

class SelectedInterface: public TagBase {
public:
    SelectedInterface(){
        num = 0;
    }
    int num;
};
