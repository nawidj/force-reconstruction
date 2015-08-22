#include <cstdlib>

#include "forcereconstruction.h"


int main(int argc, char* argv[])
{

    tacman::ForceReconstruction forceReconst("data");

    forceReconst.Train();

    return EXIT_SUCCESS;
}
