#include "mhui_func.h"
#include "imgui.h"
//#include "../misc/offsets/offsets.h"
#include <stdio.h>
#include <d3d11.h>
#include <tchar.h>
#include "instruction.h"

#include "../misc/offsets/offsets.h"


void mhmain_base_address_table_row(uint32_t process_id, uint32_t address, std::string title)
{
  ImGui::TableNextRow();
  ImGui::TableSetColumnIndex(0);
  ImGui::Text(u8"%s", title);
  ImGui::TableSetColumnIndex(1);
  ImGui::Text(u8"%X", address);
  if (address == NULL)
  {
    for (size_t i = 2; i < 8; i++)
    {
      ImGui::TableSetColumnIndex(i);
      ImGui::Text("NULL");
    }
  }
  else
  {
    uint32_t pos_x = Read<uint32_t>(process_id, address + ui_pos_offset_x);
    uint32_t pos_y = Read<uint32_t>(process_id, address + ui_pos_offset_y);
    uint32_t size_x = Read<uint32_t>(process_id, address + ui_size_offset_x);
    uint32_t size_y = Read<uint32_t>(process_id, address + ui_size_offset_y);
    uint32_t active = Read<uint32_t>(process_id, address + ui_is_active_offset);
    uint32_t dynamic = Read<uint32_t>(process_id, address + ui_dynamic_length_offset);
    ImGui::TableSetColumnIndex(2);
    ImGui::Text(u8"%d", pos_x);
    ImGui::TableSetColumnIndex(3);
    ImGui::Text(u8"%d", pos_y);
    ImGui::TableSetColumnIndex(4);
    ImGui::Text(u8"%d", size_x);
    ImGui::TableSetColumnIndex(5);
    ImGui::Text(u8"%d", size_y);
    ImGui::TableSetColumnIndex(6);
    ImGui::Text(u8"%d", active);
    ImGui::TableSetColumnIndex(7);
    ImGui::Text(u8"%d", dynamic);
  }
}

void mhmain_base_address_table(uint32_t process_id, PMH_BASE_ADDRESS base_address)
{
  static ImGuiTableFlags table_flags = ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_RowBg | ImGuiTableFlags_Borders | ImGuiTableFlags_Resizable | ImGuiTableFlags_Reorderable;

  if (ImGui::BeginTable("table1", 8, table_flags))
  {
    ImGui::TableSetupColumn(u8"名称", ImGuiTableColumnFlags_WidthFixed);
    ImGui::TableSetupColumn(u8"地址", ImGuiTableColumnFlags_WidthFixed);
    ImGui::TableSetupColumn(u8"X位置", ImGuiTableColumnFlags_WidthFixed);
    ImGui::TableSetupColumn(u8"Y位置", ImGuiTableColumnFlags_WidthFixed);
    ImGui::TableSetupColumn(u8"X长度", ImGuiTableColumnFlags_WidthFixed);
    ImGui::TableSetupColumn(u8"Y长度", ImGuiTableColumnFlags_WidthFixed);
    ImGui::TableSetupColumn(u8"激活状态", ImGuiTableColumnFlags_WidthFixed);
    ImGui::TableSetupColumn(u8"动态长度", ImGuiTableColumnFlags_WidthFixed);
    ImGui::TableHeadersRow();

    mhmain_base_address_table_row(process_id, base_address->player_IP_address, u8"人伤条");
    mhmain_base_address_table_row(process_id, base_address->player_HP_address, u8"人血条");
    mhmain_base_address_table_row(process_id, base_address->player_MP_address, u8"人蓝条");
    mhmain_base_address_table_row(process_id, base_address->player_AP_address, u8"人愤怒");
    mhmain_base_address_table_row(process_id, base_address->player_EXP_address, u8"人经验");

    mhmain_base_address_table_row(process_id, base_address->pet_HP_address, u8"宠物血条");
    mhmain_base_address_table_row(process_id, base_address->pet_MP_address, u8"宠物蓝条");
    mhmain_base_address_table_row(process_id, base_address->pet_EXP_address, u8"宠物经验");

    mhmain_base_address_table_row(process_id, base_address->tab_address, u8"地图");

    mhmain_base_address_table_row(process_id, base_address->alt_e_address, u8"物品栏");
    mhmain_base_address_table_row(process_id, base_address->alt_w_address, u8"人物栏");
    mhmain_base_address_table_row(process_id, base_address->alt_q_new_address, u8"任务栏(新)");

    mhmain_base_address_table_row(process_id, base_address->quick_mission_address, u8"任务追踪");

    mhmain_base_address_table_row(process_id, base_address->dialog_box_address, u8"对话框");

    mhmain_base_address_table_row(process_id, base_address->alt_q_ori_address, u8"任务栏(旧)");
    mhmain_base_address_table_row(process_id, base_address->alt_f_address, u8"好友栏");

    

    ImGui::EndTable();
  }
}
