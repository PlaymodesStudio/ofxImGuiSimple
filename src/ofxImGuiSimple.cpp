//
//  ofxImGuiSimple.cpp
//  example-basic
//
//  Created by Eduard Frigola Bagué on 06/04/2020.
//

#include "ofxImGuiSimple.h"

#include "ofAppBaseWindow.h"
#include "ofAppRunner.h"
#include "ofGLUtils.h"

void ofxImGuiSimple::setup(ofAppBaseWindow* win){
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
    //io.ConfigViewportsNoAutoMerge = true;
    //io.ConfigViewportsNoTaskBarIcon = true;
    
    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();
    
    // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }
    
    if(win == nullptr){
        ImGui_ImplGlfw_InitForOpenGL((GLFWwindow*)ofGetWindowPtr()->getWindowContext(), true);
    }else{
        ImGui_ImplGlfw_InitForOpenGL((GLFWwindow*)win->getWindowContext(), true);
    }
    
    isProgramableRenderer = ofIsGLProgrammableRenderer();
    
    if(isProgramableRenderer){
        const char* glsl_version = "#version 150";
        ImGui_ImplOpenGL3_Init(glsl_version);
    }else{
        ImGui_ImplOpenGL2_Init();
    }
}

void ofxImGuiSimple::begin(){
    if(isProgramableRenderer)
        ImGui_ImplOpenGL3_NewFrame();
    else
        ImGui_ImplOpenGL2_NewFrame();
    
    ImGui_ImplGlfw_NewFrame();
//    ImGuiIO& io = ImGui::GetIO();
    // io.DeltaTime = ???; // Not yet supported
//    io.DisplaySize = ImVec2((float) ofGetWidth(), (float) ofGetHeight());
    // io.DisplayFramebufferScale = ???; // Not yet supported
    
    ImGui::NewFrame();
}

void ofxImGuiSimple::end(){
    ImGuiIO& io = ImGui::GetIO();
    ImGui::Render();
    if(isProgramableRenderer){
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }else{
        ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
    }
    
    // Update and Render additional Platform Windows
    // (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
    //  For this specific demo app we could also call glfwMakeContextCurrent(window) directly)
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        //           GLFWwindow* backup_current_context = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        //           glfwMakeContextCurrent(backup_current_context);
    }
}
