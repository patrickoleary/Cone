#include "Cone.h"

#include <vtkRendererCollection.h>

Cone::Cone() {
  this->coneSource = vtkSmartPointer<vtkConeSource>::New();
}

void Cone::Initialize(vtkSmartPointer<vtkRenderWindow> renderWindow) {
  this->renderWindow = renderWindow;
  vtkSmartPointer<vtkRenderer> renderer = renderWindow->GetRenderers()->GetFirstRenderer();
  vtkNew<vtkPolyDataMapper> mapper;
  vtkNew<vtkActor> actor;

  mapper->SetInputConnection(coneSource->GetOutputPort());
  actor->SetMapper(mapper);

  renderer->AddActor(actor);
  renderer->ResetCamera();
  // this->renderWindow->Render(); // Done on Python side
}

void Cone::ResetCamera() {
  this->renderWindow->GetRenderers()->GetFirstRenderer()->ResetCamera();
  // this->renderWindow->Render(); // Done on Python side
}

void Cone::SetResolution(int resolution) {
  this->coneSource->SetResolution(resolution);
  // this->renderWindow->Render(); // Done on Python side
}