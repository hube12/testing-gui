
list(APPEND MAIN_APP_SOURCES
        main.cpp
        #src/glad/gl.h
		imgui/imgui_impl_opengl3.h
		imgui/imgui_impl_opengl3.cpp
		imgui/imgui_impl_glfw.h
		imgui/imgui_impl_glfw.cpp
        #src/imgui/glad.c
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

#asap_executable(TARGET
#        TARGET
#        asap_app
#        SOURCES
#        ${MAIN_APP_SRC}
#        INCLUDE_DIRS
#        ${MAIN_APP_INCLUDE_DIRS}
#        LIBRARIES
#        ${MAIN_APP_LIBRARIES}
        #)
#set_tidy_target_properties(asap_app)

#set_cppcheck_command()
