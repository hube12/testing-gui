
list(APPEND MAIN_APP_SOURCES
        main.cpp
        implementation/imgui_impl_opengl3.h
        implementation/imgui_impl_opengl3.cpp
        implementation/imgui_impl_glfw.h
        implementation/imgui_impl_glfw.cpp
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
add_executable(${NAME} ${MAIN_APP_SOURCES})
target_include_directories(${NAME} PUBLIC ${MAIN_APP_INCLUDE_DIRS})
target_link_libraries(${NAME} ${MAIN_APP_LIBRARIES})

list(APPEND GUI_APP_SOURCES
        gui.cc
        implementation/imgui_impl_opengl3.h
        implementation/imgui_impl_opengl3.cpp
        implementation/imgui_impl_glfw.h
        implementation/imgui_impl_glfw.cpp
        glad/glad.h
        glad/glad.c
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
add_executable(${NAME} ${GUI_APP_SOURCES})
target_include_directories(${NAME} PUBLIC ${GUI_APP_INCLUDE_DIRS})
target_link_libraries(${NAME} ${GUI_APP_LIBRARIES})
