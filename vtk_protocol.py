import time

sys.path.append("build/")

import Cone

from vtk.web import protocols as vtk_protocols

from wslink import register as exportRpc

# import vtk - Moved to Cpp

# -------------------------------------------------------------------------
# ViewManager
# -------------------------------------------------------------------------

class VtkCone(vtk_protocols.vtkWebProtocol):
    def __init__(self):
        self.cone = Cone()

    @exportRpc("vtk.initialize")
    def createVisualization(self):
        renderWindow = self.getView('-1')

        self.cone.Initialize(renderWindow)

        return self.resetCamera()


    @exportRpc("vtk.camera.reset")
    def resetCamera(self):

        self.cone.ResetCamera()

    #    renderWindow = self.getView('-1')
    #    self.getApplication().InvalidateCache(renderWindow)
        self.getApplication().InvokeEvent('UpdateEvent')

        return -1


    @exportRpc("vtk.cone.resolution.update")
    def updateResolution(self, resolution):

        self.cone.SetResolution(resolution)

        self.getApplication().InvokeEvent('UpdateEvent')


    @exportRpc("viewport.mouse.zoom.wheel")
    def updateZoomFromWheel(self, event):
      if 'Start' in event["type"]:
        self.getApplication().InvokeEvent('StartInteractionEvent')

      renderWindow = self.getView(event['view'])
      if renderWindow and 'spinY' in event:
        zoomFactor = 1.0 - event['spinY'] / 10.0

        camera = renderWindow.GetRenderers().GetFirstRenderer().GetActiveCamera()
        fp = camera.GetFocalPoint()
        pos = camera.GetPosition()
        delta = [fp[i] - pos[i] for i in range(3)]
        camera.Zoom(zoomFactor)

        pos2 = camera.GetPosition()
        camera.SetFocalPoint([pos2[i] + delta[i] for i in range(3)])
        renderWindow.Modified()

      if 'End' in event["type"]:
        self.getApplication().InvokeEvent('EndInteractionEvent')