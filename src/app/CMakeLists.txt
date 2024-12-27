add_subdirectory(main)
set_property(TARGET main PROPERTY FOLDER "App")

add_subdirectory(test)
set_property(TARGET test PROPERTY FOLDER "App")

add_subdirectory(test2)
set_property(TARGET test2 PROPERTY FOLDER "App")
