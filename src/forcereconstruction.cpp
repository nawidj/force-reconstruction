

#include "forcereconstruction.h"
#include <iostream>
#include <string>
#include <gurls++/gprwrapper.h>


using namespace gurls;
using std::string;

namespace tacman {



// Create a ForceReconstruction object for bodypart.
// partName:
ForceReconstruction::ForceReconstruction(std::string dataDirectory)
{
    _dataDirectory = dataDirectory;
};

bool ForceReconstruction::Train()
{

    gMat2D<double> Xtr, Xte, ytr, yte;

    string XtrFileName = _dataDirectory + "/Xtr.csv";
    string XteFileName = _dataDirectory + "/Xte.csv";
    string ytrFileName = _dataDirectory + "/ytr.csv";
    string yteFileName = _dataDirectory + "/yte.csv";

    string means_fileName("pred_gp_means.csv");
    string vars_fileName("pred_gp_vars.csv");

    // Load data files
    std::cout << "Loading data files..." << std::endl;
    Xtr.readCSV(XtrFileName);
    Xte.readCSV(XteFileName);
    ytr.readCSV(ytrFileName);
    yte.readCSV(yteFileName);

    // specify the task sequence
    OptTaskSequence *seq = new OptTaskSequence();
    *seq << "split:ho" << "paramsel:siglamhogpregr" << "kernel:rbf"
         << "optimizer:rlsgpregr" << "predkernel:traintest" << "pred:gpregr";

    GurlsOptionsList * process = new GurlsOptionsList("processes", false);

    // defines instructions for training process
    OptProcess* process1 = new OptProcess();
    *process1 << GURLS::computeNsave << GURLS::computeNsave <<  GURLS::computeNsave
              <<  GURLS::computeNsave << GURLS::ignore << GURLS::ignore;
    process->addOpt("one", process1);

    // defines instructions for testing process
    OptProcess* process2 = new OptProcess();
    *process2 << GURLS::load << GURLS::load <<  GURLS::load <<  GURLS::load
              <<GURLS::computeNsave << GURLS::computeNsave;
    process->addOpt("two", process2);

    // build an options' structure
    GurlsOptionsList* opt = new GurlsOptionsList("GURLSgpr", true);
    opt->addOpt("seq", seq);
    opt->addOpt("processes", process);

    GURLS G;

    string jobId0("one");
    string jobId1("two");

    // run gurls for training
    //G.run(Xtr, ytr, *opt, jobId0);

    GurlsOptionsList* opt2 = new GurlsOptionsList("GURLSgpr", false);
    opt2->load("GURLSgpr.bin");
    // run gurls for testing
    G.run(Xte, yte, *opt2, jobId1);



    //        means = opt.pred.means;
            GurlsOptionsList* pred = GurlsOptionsList::dynacast(opt2->getOpt("pred"));
            GurlsOption *means_opt = pred->getOpt("means");

            const gMat2D<double>& means_mat = OptMatrix<gMat2D<double> >::dynacast(means_opt)->getValue();

            means_mat.saveCSV(means_fileName);

    return true;
}

} // namespace tacman


