#include "frontend.hpp"

void GUI_Text::show()
{
    ImGui::Columns(2);
    ImGui::Separator();
    //sprintf_s(buffer, text2.c_str());
    ImGui::TextWrapped(text.text.c_str());                              ImGui::NextColumn();
    ImGui::InputText(text.text_ID.c_str(), bfr, IM_ARRAYSIZE(bfr));     ImGui::NextColumn();

    if (!text.comment.empty()) {
        ImGui::Columns(1);
        ImGui::Bullet();
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.33f, 0.51f, 0.07f, 1.0f));
        ImGui::TextWrapped(text.comment.c_str());
        ImGui::PopStyleColor(1);
    }
}

Text_data GUI_Text::save()
{
    return Text_data();
}

void GUI_Category::show()
{
    //ImGui::Columns(3, "mycolumns"); // 3-ways, with border

    if (ImGui::TreeNode(_name.c_str())) {
        for (auto& td : _tradline) {
            td.show();
        }
        
        ImGui::Separator();

        /*ImGui::InputTextMultiline("##source", buffer, IM_ARRAYSIZE(buffer), ImVec2(-FLT_MIN, ImGui::GetTextLineHeight() * 1.3));*/
        ImGui::TreePop();

    }
}