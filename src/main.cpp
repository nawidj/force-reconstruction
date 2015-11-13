#include <cstdlib>

#include "forcereconstruction.h"
#include <yarp/os/ResourceFinder.h>
#include <yarp/os/Network.h>
#include <yarp/os/Bottle.h>

int main(int argc, char* argv[])
{

    yarp::os::Network yarp;
    yarp::os::ResourceFinder rf;
    rf.setVerbose(true);
    rf.setDefaultConfigFile("forceReconstruction.ini");
    rf.setContext("force-reconstruction");
    rf.configure(argc, argv);


    tacman::ForceReconstruction forceReconst(rf);
    //forceReconst.Train("left_index");
    forceReconst.useCallback();
    forceReconst.open("/urgh");

   // yarp::os::Bottle& outBot = forceReconst.prepare();
   // outBot.clear();
   // outBot.addDouble(0);
   // outBot.addDouble(0);
   // forceReconst.waitForWrite();

    yarp::os::Network::connect("/icub/skin/left_hand_comp", "/urgh");



    while(true)
    ;

    return EXIT_SUCCESS;
}
