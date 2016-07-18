#include "DicomBinaryInformationExtractor.hpp"
#include "CommonTypes.h"
#include <iostream>
#include <memory>

#include "dcmtk/config/osconfig.h"
#include "dcmtk/dcmdata/dctk.h"
#include "dcmtk/dcmimgle/dcmimage.h"
#include "dcmtk/dcmimage/dipipng.h"

DicomBinaryInformationExtractor::DicomBinaryInformationExtractor()
{
}

bool DicomBinaryInformationExtractor::extract(const char* p_dicomFileName, std::string p_binaryFileName) const
{
    FILE* l_binaryOutputFile = fopen(p_binaryFileName.c_str(), "wb");
    if (l_binaryOutputFile != NULL)
    {
        bool l_status = processFile(l_binaryOutputFile, p_dicomFileName);
        fclose(l_binaryOutputFile);
        return l_status;
    }
    else
    {
        logFileOpenProblem(p_binaryFileName);
        return false;
    }
}

bool DicomBinaryInformationExtractor::processFile(FILE*& p_binaryFile, std::string p_fileName) const
{
    if (not dcmDataDict.isDictionaryLoaded())
    {
        logLackOfLoadedDictionary();
        return false;
    }

    DcmFileFormat* l_dicomFile = new DcmFileFormat();
    if (not loadDicomFile(l_dicomFile, p_fileName))
    {
        return false;
    }

    DicomImage *l_image = NULL;
    if(not loadDicomImage(l_image, l_dicomFile))
    {
        return false;
    }

    saveImageAsPngFile(p_binaryFile, l_image);
    delete l_image;
    return true;
}

bool DicomBinaryInformationExtractor::loadDicomFile(DcmFileFormat*& p_dicomFile, std::string p_fileName) const
{
    OFCondition l_result = p_dicomFile->loadFile(p_fileName.c_str(),
                                                 EXS_Unknown,
                                                 EGL_withoutGL,
                                                 DCM_MaxReadLength,
                                                 ERM_autoDetect);
    if (l_result.bad())
    {
        std::cout << __FILE__ << ":" << __LINE__ << l_result.text() << ": reading file: " << p_fileName << std::endl;
        return false;
    }
    return true;
}

bool DicomBinaryInformationExtractor::loadDicomImage(DicomImage*& p_image, DcmFileFormat*& p_dfile) const
{
    unsigned long l_optCompatibilityMode = CIF_MayDetachPixelData | CIF_TakeOverExternalDataset;
    l_optCompatibilityMode |= CIF_IgnoreModalityTransformation;

    DcmDataset* l_dataSet = p_dfile->getDataset();
    E_TransferSyntax l_xfer = l_dataSet->getOriginalXfer();

    OFCmdUnsignedInt l_optFrameCount = 1;
    OFCmdUnsignedInt l_optFrame = 1;

    p_image = new DicomImage(p_dfile, l_xfer, l_optCompatibilityMode, l_optFrame - 1, l_optFrameCount);
    if (p_image == NULL)
    {
        std::cout << __FILE__ << ":" << __LINE__ << "Loaded DICOM image is empty!" << std::endl;
        return false;
    }

    if (p_image->getStatus() != EIS_Normal)
    {
        logProblemWithLoadingDicomFile(p_image);
        return false;
    }
    return true;
}

void DicomBinaryInformationExtractor::saveImageAsPngFile(FILE*& p_binaryFile, DicomImage*& p_image) const
{
    unsigned int l_frame = 0;

    DiPNGPlugin l_pngPlugin;
    l_pngPlugin.setInterlaceType(E_pngInterlaceAdam7);
    l_pngPlugin.setMetainfoType(E_pngFileMetainfo);
    p_image->writePluginFormat(&l_pngPlugin, p_binaryFile, l_frame);
}

void DicomBinaryInformationExtractor::logFileOpenProblem(std::string p_binaryFileName) const
{
    std::cout << __FILE__ << ":" << __LINE__
              << "Couldn't open file: "
              << p_binaryFileName
              << std::endl;
}

void DicomBinaryInformationExtractor::logLackOfLoadedDictionary() const
{
    std::cout << __FILE__ << ":" << __LINE__
              << "No data dictionary loaded, check environment variable: "
              << DCM_DICT_ENVIRONMENT_VARIABLE
              << std::endl;
}

void DicomBinaryInformationExtractor::logProblemWithLoadingDicomFile(DicomImage* p_image) const
{
    std::cout << __FILE__ << ":" << __LINE__
              << "Error: cannot load DICOM image ("
              << DicomImage::getString(p_image->getStatus()) << ")"
              << std::endl;
}

