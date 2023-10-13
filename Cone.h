#include <vtkConeSource.h>
#include <vtkNew.h>
#include <vtkSmartPointer.h>

#include <vtkActor.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>

class Cone {

    vtkSmartPointer<vtkConeSource> coneSource;
    vtkSmartPointer<vtkRenderWindow> renderWindow;
    
    int resolution = 10;

public:
    Cone();

    void Initialize(vtkSmartPointer<vtkRenderWindow> renderWindow);
    void ResetCamera();
    void SetResolution(int resolution);
};