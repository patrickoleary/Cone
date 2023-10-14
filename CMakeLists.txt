
cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

project(Cone)

find_package(VTK COMPONENTS 
  CommonCore
  CommonDataModel
  FiltersSources
  InteractionStyle
  RenderingContextOpenGL2
  RenderingCore
  RenderingFreeType
  RenderingGL2PSOpenGL2
  RenderingOpenGL2
)
find_package(pybind11 REQUIRED)

if (NOT VTK_FOUND)
  message(FATAL_ERROR "Cone: Unable to find the VTK build folder.")
endif()

set(CONE_PYBIND11_FLAGS "-Wno-shadow")

set(library_name "Cone")
pybind11_add_module(${library_name} PyWrap.cxx)
target_include_directories(${library_name} PUBLIC
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
)
target_link_libraries(${library_name} LINK_PUBLIC ${VTK_LIBRARIES})
set_target_properties(${library_name}
  PROPERTIES
    CXX_VISIBILITY_PRESET hidden
    COMPILE_FLAGS ${CONE_PYBIND11_FLAGS}
  )
# vtk_module_autoinit is needed
vtk_module_autoinit(
  TARGETS ${library_name}
  MODULES ${VTK_LIBRARIES}
)