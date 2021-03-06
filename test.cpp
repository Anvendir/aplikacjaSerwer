/* testowy jeden
#include "dcmtk/config/osconfig.h"
#include "dcmtk/dcmdata/dctk.h"
#include "dcmtk/dcmimgle/dcmimage.h"
#include "iostream"

int main(int argc, char *argv[])
{

    DicomImage *image = new DicomImage("CT0001.dcm");
    if (image != NULL)
    {
        std::cout << "hell yeah!";
    }

    return 0;
}*/

//komenda do budowy tego gowna
// g++ -pthread -lz -I ./projekt/dcmtk/config/include/ -I ./projekt/dcmtk/dcmdata/include/ -I ./projekt/dcmtk/oflog/include -I ./projekt/dcmtk/ofstd/include/ -I ./projekt/dcmtk/dcmimgle/include  test.cpp -L./projekt/dcmtk/dcmimgle/libsrc/ -ldcmimgle -L./projekt/dcmtk/dcmdata/libsrc/ -ldcmdata -L./projekt/dcmtk/oflog/libsrc/ -loflog -L./projekt/dcmtk/ofstd/libsrc/ -lofstd  -o raz

#include "dcmtk/config/osconfig.h"
#include "dcmtk/dcmdata/dctk.h"
#include "dcmtk/dcmimgle/dcmimage.h"
#include <iostream>

int main()
{
    std::cout << "Helo world" << std::endl;
    DcmFileFormat fileformat;
    OFCondition status = fileformat.loadFile("CT0001.dcm");
    if (status.good())
    {
        OFString patientName;
        if (fileformat.getDataset()->findAndGetOFString(DCM_PatientName, patientName).good())
        {
            std::cout << "Patient's Name: " << patientName << std::endl;
        }
        else
            std::cerr << "Error: cannot access Patient's Name!" << std::endl;
    }
    else
        std::cerr << "Error: cannot read DICOM file (" << status.text() << ")" << std::endl;
}
