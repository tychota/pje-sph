#pragma once

#include <vtk-6.1/vtkSmartPointer.h>
#include <vtk-6.1/vtkAbstractParticleWriter.h>
#include <string>
#include <vector>

#include "io/Writer.hpp"

class VTK_EXPORT VtkHDF5Writer : vtkAbstractParticleWriter, Writer {
  public:
    static VtkHDF5Writer *New();
    vtkTypeMacro(VtkHDF5Writer,vtkAbstractParticleWriter);
    void PrintSelf(ostream& os, vtkIndent indent);

    // Description:
    // Get the input to this writer.
    vtkPointSet* GetInput();
    vtkPointSet* GetInput(int port);

    // Description:
    // Quesry the file to see if a timestep was written previously
    // this should really be part of vtkHDF5Reader, but when the
    // Writer is used as a cache file, we need a function to check
    // if the timestep is already present
    bool IsTimeStepPresent(int timestep);
    void DeleteTimeStep(int timestep);

    // Description:
    // Make this public so that files can be closed between time steps and
    // the file might survive an application crash.
    void CloseFile();

    // Description:
    // Usually, we want to open the file in WRITE mode, but when being used
    // as a file cache, we want to write and read so use READWRITE mode
    vtkSetMacro(FileMode,int);
    vtkGetMacro(FileMode,int);
    void SetFileModeToWrite();
    void SetFileModeToReadWrite();

    // Description:
    // If VectorsWithStridedWrite is true, performance may be impacted
    // but no copy of {X,Y,Z] out of the triple vector into a single
    // flat array takes place. Test show that using a strided write
    // is terrible in parallel. Hope to fix this one day.
    vtkSetMacro(VectorsWithStridedWrite,int);
    vtkGetMacro(VectorsWithStridedWrite,int);
    vtkBooleanMacro(VectorsWithStridedWrite,int);

    // Description:
    // Set/Get the controller used for coordinating parallel writing
    // (set to the global controller by default)
    // If not using the default, this must be called before any
    // other methods.
    virtual void SetController(vtkMultiProcessController* controller);
    vtkGetObjectMacro(Controller, vtkMultiProcessController);

    // Description:
    // When writing in parallel, all processes must send data to HDF...
    // if one node has no particles, it does nothing - but this causes the
    // others to hang. We therefore gather information and write an
    // empty array of the correct type
    vtkSetMacro(DisableInformationGather,int);
    vtkGetMacro(DisableInformationGather,int);
    vtkBooleanMacro(DisableInformationGather,int);

  protected:
    vtkH5PartWriter();
    ~vtkH5PartWriter();
    //
    int   OpenFile();

    // Override superclass' Write method
    virtual void WriteData();

    void CopyFromVector(int offset, vtkDataArray *source, vtkDataArray *dest);
    void WriteDataArray(int i, vtkDataArray *array);

    // Overide information to only permit PolyData as input
    virtual int FillInputPortInformation(int, vtkInformation *info);
    virtual int FillOutputPortInformation(int, vtkInformation* info);

    // Description:
    virtual int RequestInformation(vtkInformation* request,
                                   vtkInformationVector** inputVector,
                                   vtkInformationVector* outputVector);

    // Description:
    // If a certain process has zero particles, the dataarrays for
    // points and scalars will be effectivle empty, or even NULL
    // in this case, the collective parallel IO write may fail because
    // the zero data process does not know what datatype to 'write'
    // or dataset names to create. We therefore provide a gather call
    // before writing to ensure that all processes 'agree' on what they are writing.
//BTX
    bool GatherDataArrayInfo(vtkDataArray *data, int &datatype,
                             std::string &dataname, int &numComponents);
    bool GatherScalarInfo(vtkPointData *pd, int N, int &numScalar);
//ETX

    //
    // Internal Variables
    //
    int           NumberOfTimeSteps;
    long long     NumberOfParticles;
    int           FileMode;
    int           VectorsWithStridedWrite;
    H5PartFile   *H5FileId;
    //BTX
    std::vector<double>  InputTimeValues;
    //ETX
    int           ActualTimeStep;

    // Used for Parallel write
    int     UpdatePiece;
    int     UpdateNumPieces;
    int     DisableInformationGather;

    vtkMultiProcessController* Controller;

  private:
    vtkH5PartWriter(const vtkH5PartWriter&);  // Not implemented.
    void operator=(const vtkH5PartWriter&);  // Not implemented.
};
