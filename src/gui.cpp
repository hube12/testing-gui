#include "imgui.h"
#include "implementation/imgui_impl_glfw.h"
#include "implementation/imgui_impl_opengl3.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <cstdio>
#include <iostream>
#include "ressources/pillars.h"

#define STB_IMAGE_IMPLEMENTATION

#include "implementation/stb_image.h"


#define IM_MAX(_A, _B)       (((_A) >= (_B)) ? (_A) : (_B))
#define IM_MIN(_A, _B)       (((_A) <= (_B)) ? (_A) : (_B))
#define IMVEC_PRINT(_A) (printf("%f %f \n",_A.x,_A.y))

static inline ImVec2 operator*(ImVec2 a, ImVec2 b) { return {a.x * b.x, a.y * b.y}; }

static inline ImVec2 operator*(ImVec2 a, float b) { return {a.x * b, a.y * b}; }

static inline ImVec2 operator-(ImVec2 a, ImVec2 b) { return {a.x - b.x, a.y - b.y}; }

static inline ImVec2 operator+(ImVec2 a, ImVec2 b) { return {a.x +b.x, a.y + b.y}; }

static inline ImVec2 operator/(ImVec2 a, float b) { return {a.x / b, a.y / b}; }


static bool log_bool = false;
static int style_current = 1;
static int font_current = 0;
static float heigh_main_menu_bar = 0;
static bool showMain = true;
static bool showLeft = false;
static bool showRight = false;
static ImGuiWindowFlags windowFlags = (unsigned int) ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse |
                                      ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBringToFrontOnFocus;
GLuint pillars_texture;


struct CustomConstraints // Helper functions to demonstrate programmatic constraints
{
    static void Square(ImGuiSizeCallbackData *data) {
        data->DesiredSize = ImVec2(IM_MIN(data->DesiredSize.x, data->DesiredSize.y), IM_MIN(data->DesiredSize.x, data->DesiredSize.y));
    }

    static void Step(ImGuiSizeCallbackData *data) {
        auto step = (float) (int) (intptr_t) data->UserData;
        data->DesiredSize = ImVec2(roundf(data->DesiredSize.x / step + 0.5f) * step, roundf(data->DesiredSize.y / step + 0.5f) * step);
    }
};

static GLuint loadpng(GLuint my_opengl_texture) {
    int my_image_width, my_image_height;
    unsigned char *my_image_data = stbi_load_from_memory(pillars_png_start, pillars_png_size, &my_image_width, &my_image_height, nullptr, 4);
    // Turn the RGBA pixel data into an OpenGL texture:
    glGenTextures(1, &my_opengl_texture);
    glBindTexture(GL_TEXTURE_2D, my_opengl_texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, my_image_width, my_image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, my_image_data);
    stbi_image_free(my_image_data);
    return my_opengl_texture;
}


static void glfw_error_callback(int error, const char *description) {
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}


static void ShowDebugMenu() {
    ImGui::MenuItem("Debug Menu", nullptr, false, false);
    if (ImGui::MenuItem("Open", "Ctrl+O")) {}
    if (ImGui::BeginMenu("Open Recent")) {
        if (ImGui::BeginMenu("More..")) {
            if (ImGui::BeginMenu("Recurse..")) {
                ShowDebugMenu();
                ImGui::EndMenu();
            }
            ImGui::EndMenu();
        }
        ImGui::EndMenu();
    }
    ImGui::Separator();

    if (ImGui::BeginMenu("Themes")) {
        const char *styles[] = {"Classic", "Dark", "Light"};
        ImGui::Combo("##theme", &style_current, styles, IM_ARRAYSIZE(styles));
        ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("Font")) {
        const char *fonts[] = {"Default", "Cousine", "Karla", "Lato", "lato light"};
        ImGui::Combo("##font", &font_current, fonts, IM_ARRAYSIZE(fonts));
        ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("By Neil#4879", false)) {
        IM_ASSERT(0);
    }
    if (ImGui::MenuItem("Log")) { log_bool = true; }
    if (ImGui::MenuItem("Quit the application", "Alt+F4")) {
        exit(0);
    }
}

static void ShowBackgroundWindow() {
    ImGui::SetNextWindowBgAlpha(0.0f);
    ImGui::SetNextWindowSizeConstraints(ImVec2(0, 0), ImVec2(FLT_MAX, FLT_MAX), nullptr);
    ImGui::SetNextWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x, ImGui::GetFrameHeight() * 3));
    ImGui::SetNextWindowPos(ImVec2(0, heigh_main_menu_bar), ImGuiCond_Always);

    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 10.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding,
                        ImVec2(ImGui::GetFrameHeight() / 2, ImGui::GetFrameHeight() / 2));

    if (!ImGui::Begin("Background", nullptr, windowFlags)) {
        ImGui::End();
        return;
    }
    ImGui::SetCursorPos(ImVec2(0, 0));
    ImGui::PushItemWidth(100);
    if (ImGui::ArrowButton("##leftHide", showLeft ? ImGuiDir_Left : ImGuiDir_Right)) {
        showLeft = !showLeft;
    }
    ImGui::SetCursorPos(ImVec2(ImGui::GetIO().DisplaySize.x - ImGui::GetFrameHeight(), 0));
    if (ImGui::ArrowButton("##rightHide", showRight ? ImGuiDir_Right : ImGuiDir_Left)) {
        showRight = !showRight;
    }

    ImGui::End();
    ImGui::PopStyleVar(5);
}


static void ShowMainWindow() {
    ImGui::SetNextWindowSizeConstraints(ImVec2(0, 0), ImVec2(FLT_MAX, FLT_MAX), CustomConstraints::Square);
    ImVec2 mainFactorSize = ImVec2(0.5, 1);
    ImVec2 mainFactorPos = ImVec2(0.10, 1);
    ImGui::SetNextWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x, ImGui::GetIO().DisplaySize.y - heigh_main_menu_bar) * mainFactorSize);
    float x = ImGui::GetIO().DisplaySize.x * mainFactorSize.x, y = ImGui::GetIO().DisplaySize.y - heigh_main_menu_bar;
    ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x + ((x > y) ? ((x - y) / 2 / mainFactorPos.x) : 0), heigh_main_menu_bar + ((y > x) ? (y - x) / 2 : 0)) * mainFactorPos,
                            ImGuiCond_Always);
    if (!ImGui::Begin("Main", nullptr, windowFlags)) {
        ImGui::End();
        return;
    }
    //push the image as a background
    ImGui::Image((void *) (intptr_t) pillars_texture, ImVec2(ImGui::GetWindowSize().x, ImGui::GetWindowSize().y));\

    //push 10 circles on the pillars
    static float posx[10]{0.5, 0.34, 0.24, 0.24, 0.34, 0.5, 0.66, 0.76, 0.76, 0.66};
    static float posy[10]{0.78, 0.72, 0.58, 0.42, 0.28, 0.22, 0.28, 0.42, 0.58, 0.72};

    for (int i = 0; i < 10; i++) {
        ImGui::PushID(i);
        float scaleFactor = ImGui::GetWindowSize().x / 1000.0;
        ImVec2 higherCorner = ImVec2(posx[i], posy[i]) * ImGui::GetWindowSize() + ImGui::GetWindowPos()+ ImVec2(10, 10) * scaleFactor +ImVec2(1, 1) / scaleFactor;
        //ImVec2 lowerCorner = higherCorner + ImVec2(50, 50) * scaleFactor;
        //ImGui::GetWindowDrawList()->AddRectFilled(higherCorner, lowerCorner, ImGui::GetColorU32(ImVec4(1, 1, 1, 1)),5,ImDrawCornerFlags_All);
        ImGui::GetWindowDrawList()->AddCircleFilled(higherCorner,40*scaleFactor,ImGui::GetColorU32(ImVec4(1, 1, 0, 1)),30);
        ImGui::GetWindowDrawList()->AddCircleFilled(higherCorner,38*scaleFactor,ImGui::GetColorU32(ImVec4(1, 1, 1, 1)),30);
        ImGui::PopID();
    }
    ImGui::End();
}

static void ShowLeftWindows() {

    ImGui::SetNextWindowSizeConstraints(ImVec2(0, 0), ImVec2(FLT_MAX, FLT_MAX), nullptr);
    ImVec2 leftFactorSize = ImVec2(0.10, 1);
    ImVec2 leftFactorPos = ImVec2(0.0, 1);
    ImGui::SetNextWindowSize(
            ImVec2(ImGui::GetIO().DisplaySize.x, ImGui::GetIO().DisplaySize.y - heigh_main_menu_bar) *
            leftFactorSize);
    ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x, heigh_main_menu_bar) * leftFactorPos,
                            ImGuiCond_Always);
    if (!ImGui::Begin("Left", nullptr, windowFlags) || !showLeft) {
        ImGui::End();
        return;
    }

    ImGui::End();
}

static void ShowRightWindows() {

    ImGui::SetNextWindowSizeConstraints(ImVec2(0, 0), ImVec2(FLT_MAX, FLT_MAX), nullptr);
    ImVec2 rightFactorSize = ImVec2(0.4, 1);
    ImVec2 rightFactorPos = ImVec2(0.6, 1);
    ImGui::SetNextWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x, ImGui::GetIO().DisplaySize.y - heigh_main_menu_bar) * rightFactorSize);
    ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x, heigh_main_menu_bar) * rightFactorPos, ImGuiCond_Always);
    if (!ImGui::Begin("Right", nullptr, windowFlags) || !showRight) {
        ImGui::End();
        return;
    }

    ImGui::End();
}

static void ShowMainMenuBar() {
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("Debug")) {
            ShowDebugMenu();
            ImGui::EndMenu();
        }
        heigh_main_menu_bar = ImGui::GetWindowSize().y;
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
    glfwWindowHint(GLFW_AUTO_ICONIFY, GLFW_TRUE);
    glfwWindowHint(GLFW_FLOATING, GLFW_TRUE);
    glfwWindowHint(GLFW_FOCUS_ON_SHOW, GLFW_TRUE);

    GLFWwindow *window = glfwCreateWindow(mode->width / 2, mode->height / 2, "NeilSeedCrackerV2.0", nullptr, nullptr);
    glfwSetWindowSizeLimits(window,480,270,GLFW_DONT_CARE,GL_DONT_CARE);
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


    //load fonts
    auto font_default = io.Fonts->AddFontDefault();
    auto font_cousine = io.Fonts->AddFontFromFileTTF(CPP_SRC_DIR "modules/imgui/misc/fonts/Cousine-Regular.ttf", 15.0f);
    auto font_karla = io.Fonts->AddFontFromFileTTF(CPP_SRC_DIR "modules/imgui/misc/fonts/Karla-Regular.ttf", 18.0f);
    auto font_lato = io.Fonts->AddFontFromFileTTF(CPP_SRC_DIR "fonts/Lato-Regular.ttf", 18.0f);
    auto font_lato_light = io.Fonts->AddFontFromFileTTF(CPP_SRC_DIR "fonts/Lato-Light.ttf", 18.0f);

    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f); //backgound color

    pillars_texture = loadpng(pillars_texture);
    while (!glfwWindowShouldClose(window)) {

        glfwWaitEvents();

        // Start the ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        if (log_bool) {
            ImGui::LogToFile(10, "log_gui.txt");
            log_bool = false;
        }
        // Setup style
        switch (style_current) {
            case 0:
                ImGui::StyleColorsClassic();
                break;
            case 1:
                ImGui::StyleColorsDark();
                break;
            case 2:
                ImGui::StyleColorsLight();
                break;
            default:
                ImGui::StyleColorsDark();
                break;
        }

        switch (font_current) {
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

        if (showMain) {
            ShowBackgroundWindow();
            ShowMainWindow();
        }
        if (showLeft) { ShowLeftWindows(); }
        if (showRight) { ShowRightWindows(); }
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

    ImGui::LogFinish();

}

