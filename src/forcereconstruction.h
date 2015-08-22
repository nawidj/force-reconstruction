#ifndef FORCERECONSTRUCTION_H
#define FORCERECONSTRUCTION_H

#include <string>
#include <gurls++/gprwrapper.h>

namespace tacman {
class ForceReconstruction
{
public:

    ForceReconstruction(std::string dataDirectory);
    bool Train();

private:
    std::string _dataDirectory;

    //gurls::GPWrapper <double> _gaussianProcess;

};

} // namespace tacman

#endif // FORCERECONSTRUCTION_H
