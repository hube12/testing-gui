
# Set some Win32 Specific Settings
IF(WIN32)
SET(GUI_TYPE WIN32)
ENDIF(WIN32)
# Set some Apple MacOS Specific settings
IF (APPLE)
SET(GUI_TYPE MACOSX_BUNDLE)
ENDIF (APPLE)

#TODO remove next line for release and change bool to 1
UNSET(GUI_TYPE)
SET(COMPRESS 0)


list(APPEND MAIN_APP_SOURCES
        main.cpp
        implementation/imgui_impl_opengl3.h
        implementation/imgui_impl_opengl3.cpp
        implementation/imgui_impl_glfw.h
        implementation/imgui_impl_glfw.cpp
        implementation/stb_image.h
        glad/glad.h
        glad/glad.c
        KHR/khrplatform.h
        )

set(MAIN_APP_LIBRARIES
        imgui
        glfw
        )

list(APPEND MAIN_APP_INCLUDE_DIRS
        ${CMAKE_CURRENT_SOURCE_DIR}
        "${CMAKE_CURRENT_SOURCE_DIR}/imgui"
        )

set(NAME imgui-glfw)
add_executable(${NAME} ${GUI_TYPE} ${MAIN_APP_SOURCES})
target_include_directories(${NAME} PUBLIC ${MAIN_APP_INCLUDE_DIRS})
target_link_libraries(${NAME} ${MAIN_APP_LIBRARIES})
IF(COMPRESS)
add_custom_command(TARGET ${NAME} POST_BUILD COMMAND upx.exe --brute ${NAME}.exe USES_TERMINAL)
ENDIF(COMPRESS)

list(APPEND GUI_APP_SOURCES
        gui.cpp
        implementation/imgui_impl_opengl3.h
        implementation/imgui_impl_opengl3.cpp
        implementation/imgui_impl_glfw.h
        implementation/imgui_impl_glfw.cpp
        implementation/stb_image.h
        glad/glad.h
        glad/glad.c
        ressources/pillars.c
        ressources/pillars.h
        KHR/khrplatform.h
        )

set(GUI_APP_LIBRARIES
        imgui
        glfw
        )

list(APPEND GUI_APP_INCLUDE_DIRS
        ${CMAKE_CURRENT_SOURCE_DIR}
        "${CMAKE_CURRENT_SOURCE_DIR}/imgui"
        )

set(NAME gui-test)
add_executable(${NAME} ${GUI_TYPE} ${GUI_APP_SOURCES})
target_include_directories(${NAME} PUBLIC ${GUI_APP_INCLUDE_DIRS})
target_link_libraries(${NAME} ${GUI_APP_LIBRARIES})

IF(COMPRESS)
add_custom_command(TARGET ${NAME} POST_BUILD COMMAND upx.exe --brute ${NAME}.exe USES_TERMINAL)
ENDIF(COMPRESS)