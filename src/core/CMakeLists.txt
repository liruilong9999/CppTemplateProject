add_subdirectory(common)
set_property(TARGET common PROPERTY FOLDER "Core")

add_subdirectory(lbase)
set_property(TARGET lbase PROPERTY FOLDER "Core")

add_subdirectory(pluginmanager)
set_property(TARGET pluginmanager PROPERTY FOLDER "Core")

add_subdirectory(luicommon)
set_property(TARGET luicommon PROPERTY FOLDER "Core")

add_subdirectory(lddsbus)
set_property(TARGET lddsbus PROPERTY FOLDER "Core")



