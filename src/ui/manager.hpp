#ifndef UI_MANAGER_HPP
#define UI_MANAGER_HPP

#define IMGUI_DEFINE_MATH_OPERATORS

#include <tabby.hpp>
#include <imgui.h>

#include "state.hpp"
#include "theme.hpp"

class UIManager {
   public:
    UIState m_state;

    tabby::Font m_font;
    tabby::Font m_medium;
    tabby::Font m_bold;
    Theme* m_theme;
    tabby::AutocompleteState m_replayAutocomplete;

    geode::async::TaskHolder<geode::utils::web::WebResponse> m_webListener;
    double m_ffmpegDownloadProgress = -1.0;

    GLuint m_texture = 0;

    UIManager();

    void setup();
    void draw();
    void toggle();

    void drawKeybindContextMenu();

    void keybindRightClick(const std::string& tag) {
        ImVec2 size = ImGui::GetItemRectSize();
        ImVec2 pos  = ImGui::GetItemRectMin();
        ImGui::SetCursorScreenPos(pos);
        ImGui::InvisibleButton(("##rcz" + tag).c_str(), size,
                               ImGuiButtonFlags_MouseButtonRight);
        if (ImGui::IsItemClicked(ImGuiMouseButton_Right)) {
            auto& ctx               = m_state.m_keybindCtx;
            ctx.tag                 = tag;
            ctx.open                = true;
            ctx.capturing           = false;
            ctx.capturedKey         = 0;
            ctx.capturedMod         = 0;
            ctx.pendingValue        = "1";
            ctx.pendingType         = KeybindType::Toggle;
            ctx.typeState.selectedIndex = 0;
        }
    }
};

#endif  
