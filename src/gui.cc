#include "imgui.h"
#include "implementation/imgui_impl_glfw.h"
#include "implementation/imgui_impl_opengl3.h"
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>

#define IM_MAX(_A,_B)       (((_A) >= (_B)) ? (_A) : (_B))

static int font_current = 0;
static void glfw_error_callback(int error, const char *description) {
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}


static void ShowDebugMenu()
{
    ImGui::MenuItem("Debug Menu", nullptr, false, false);
    if (ImGui::MenuItem("Open", "Ctrl+O")) {}
    if (ImGui::BeginMenu("Open Recent"))
    {
        if (ImGui::BeginMenu("More.."))
        {
            if (ImGui::BeginMenu("Recurse.."))
            {
                ShowDebugMenu();
                ImGui::EndMenu();
            }
            ImGui::EndMenu();
        }
        ImGui::EndMenu();
    }
    ImGui::Separator();

    if (ImGui::BeginMenu("Themes"))
    {
        ImGui::ShowStyleSelector("Choose");
        ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("Font"))
    {
        const char* fonts[] = { "Default", "Cousine", "Karla", "Lato", "lato light"};
        ImGui::Combo("font-combo", &font_current, fonts, IM_ARRAYSIZE(fonts));
        ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("Disabled", false)) // Disabled
    {
        IM_ASSERT(0);
    }
    if (ImGui::MenuItem("Quit", "Alt+F4")) {}
}

static void ShowMainWindow(bool show){
    struct CustomConstraints // Helper functions to demonstrate programmatic constraints
    {
        static void Square(ImGuiSizeCallbackData* data) { data->DesiredSize = ImVec2(IM_MAX(data->DesiredSize.x, data->DesiredSize.y), IM_MAX(data->DesiredSize.x, data->DesiredSize.y)); }
        static void Step(ImGuiSizeCallbackData* data)   { auto step = (float)(int)(intptr_t)data->UserData; data->DesiredSize = ImVec2(roundf(data->DesiredSize.x / step + 0.5f) * step, roundf(data->DesiredSize.y / step + 0.5f) * step); }
    };
    ImGui::SetNextWindowSizeConstraints(ImVec2(0, 0), ImVec2(FLT_MAX, FLT_MAX), CustomConstraints::Square);
    ImGuiWindowFlags window_flags = (unsigned int)0;
    window_flags = (unsigned int)window_flags|ImGuiWindowFlags_NoTitleBar;
    window_flags = (unsigned int)window_flags|ImGuiWindowFlags_NoScrollbar;
    window_flags = (unsigned int)window_flags|ImGuiWindowFlags_NoMove;
    window_flags = (unsigned int)window_flags|ImGuiWindowFlags_NoCollapse;
    window_flags = (unsigned int)window_flags|ImGuiWindowFlags_NoNav;
    window_flags = (unsigned int)window_flags|ImGuiWindowFlags_NoResize;
    ImGui::Begin("Main", &show, window_flags);

    ImGui::SetWindowSize(ImVec2(ImGui::GetIO().DisplaySize.y,ImGui::GetIO().DisplaySize.y));

    ImGui::End();
}
static void ShowMainMenuBar()
{
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("Debug"))
        {
            ShowDebugMenu();
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}

int main(int argc, char **argv) {
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return 1;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#if __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    //get monitor and set up the main windows
    GLFWmonitor *monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode *mode = glfwGetVideoMode(monitor);
    glfwWindowHint(GLFW_RED_BITS, mode->redBits);
    glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
    glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
    glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
    GLFWwindow *window = glfwCreateWindow(mode->width / 2, mode->height / 2, "NeilSeedCrackerV2.0", nullptr, nullptr);

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    gladLoadGL((GLADloadfunc) glfwGetProcAddress);

    // Setup Dear ImGui binding
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void) io;

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();

    // Setup style
    ImGui::StyleColorsDark();
    //load fonts
    auto font_default = io.Fonts->AddFontDefault();
    auto font_cousine = io.Fonts->AddFontFromFileTTF(CPP_SRC_DIR "modules/imgui/misc/fonts/Cousine-Regular.ttf", 15.0f);
    auto font_karla = io.Fonts->AddFontFromFileTTF(CPP_SRC_DIR "modules/imgui/misc/fonts/Karla-Regular.ttf", 18.0f);
    auto font_lato = io.Fonts->AddFontFromFileTTF(CPP_SRC_DIR "fonts/Lato-Regular.ttf", 18.0f);
    auto font_lato_light = io.Fonts->AddFontFromFileTTF(CPP_SRC_DIR "fonts/Lato-Light.ttf", 18.0f);

    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f); //backgound color
    while (!glfwWindowShouldClose(window)) {
        glfwWaitEvents();

        // Start the ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        switch (font_current)
        {
            case 0:
                ImGui::PushFont(font_default);
                break;
            case 1:
                ImGui::PushFont(font_cousine);
                break;
            case 2:
                ImGui::PushFont(font_karla);
                break;
            case 3:
                ImGui::PushFont(font_lato);
                break;
            case 4:
                ImGui::PushFont(font_lato_light);
                break;
            default:
                ImGui::PushFont(font_default);
                break;
        }
        ShowMainMenuBar();


        bool showMain=true;
        ShowMainWindow(showMain);
        ImGui::PopFont();
        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwMakeContextCurrent(window);
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwMakeContextCurrent(window);
        glfwSwapBuffers(window);
    }

// Cleanup
    ImGui_ImplOpenGL3_Shutdown();

    ImGui_ImplGlfw_Shutdown();

    ImGui::DestroyContext();

    glfwDestroyWindow(window);

    glfwTerminate();

}

