#include "Cone.h"

Cone::Cone() {
  this->coneSource = vtkSmartPointer<vtkConeSource>::New();
}

Cone::Initialize(vtkSmartPointer<vtkRenderer> renderWindow) {
  this->renderWindow = renderWindow;
  vtkSmartPointer<vtkRenderer> renderer = renderWindow->GetRenderers()->GetFirstRenderer();
  vtkNew<vtkPolyDataMapper> mapper = vtkPolyDataMapper();
  vtkNew<vtkActor> actor = vtkActor();

  mapper->SetInputConnection(coneSource->GetOutputPort());
  actor->SetMapper(mapper);

  renderer->AddActor(actor);
  renderer->ResetCamera();
  // this->renderWindow->Render(); // Done on Python side
}

Cone::ResetCamera() {
  this->renderWindow->GetRenderers()->GetFirstRenderer()->ResetCamera();
  // this->renderWindow->Render(); // Done on Python side
}

Cone::SetResolution(int resolution) {
  this->coneSource->SetResolution(resolution);
  // this->renderWindow->Render(); // Done on Python side
}