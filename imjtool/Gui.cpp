#include "gui.h"

#include "Game.h"
#include <imgui-SFML.h>

#include "Object.h"
#include "InGame.h"

#include "imgui_stdlib.h"
#include <filesystem>
#include "FileDialog.h"

#include "random.hpp"

using Random = effolkronium::random_static;

Gui::Gui()
{
	groupIndex = {
		{
			GetIndex(PlayerStart),
			GetIndex(Save),
			GetIndex(Warp),
		},
		{
			GetIndex(SpikeUp),
			GetIndex(SpikeDown),
			GetIndex(SpikeLeft),
			GetIndex(SpikeRight),
		},
		{
			GetIndex(MiniSpikeUp),
			GetIndex(MiniSpikeDown),
			GetIndex(MiniSpikeLeft),
			GetIndex(MiniSpikeRight),
		},
		{
			GetIndex(Apple),
			GetIndex(KillerBlock),
		},
		{
			GetIndex(Block),
			GetIndex(MiniBlock),
			GetIndex(Platform),
			GetIndex(BulletBlocker),
		},
		{
			GetIndex(WalljumpR),
			GetIndex(WalljumpL),
		},
		{
			GetIndex(Water),
			GetIndex(Water2),
			GetIndex(Water3),
		},
		{
			GetIndex(GravityArrowUp),
			GetIndex(GravityArrowDown),
		}
	};
}


void Gui::setGuiTheme(ThemeName name)
{
	curTheme = name;

	ImVec4* colors = ImGui::GetStyle().Colors;
	switch (name)
	{
	case ThemeName::Default:
		Gm.windowBgColor = sf::Color::Black;
		colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
		colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
		colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.06f, 0.06f, 0.94f);
		colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
		colors[ImGuiCol_Border] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
		colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		colors[ImGuiCol_FrameBg] = ImVec4(0.16f, 0.29f, 0.48f, 0.54f);
		colors[ImGuiCol_FrameBgHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
		colors[ImGuiCol_FrameBgActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
		colors[ImGuiCol_TitleBg] = ImVec4(0.04f, 0.04f, 0.04f, 1.00f);
		colors[ImGuiCol_TitleBgActive] = ImVec4(0.16f, 0.29f, 0.48f, 1.00f);
		colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
		colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
		colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
		colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
		colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
		colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
		colors[ImGuiCol_CheckMark] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
		colors[ImGuiCol_SliderGrab] = ImVec4(0.24f, 0.52f, 0.88f, 1.00f);
		colors[ImGuiCol_SliderGrabActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
		colors[ImGuiCol_Button] = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
		colors[ImGuiCol_ButtonHovered] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
		colors[ImGuiCol_ButtonActive] = ImVec4(0.06f, 0.53f, 0.98f, 1.00f);
		colors[ImGuiCol_Header] = ImVec4(0.26f, 0.59f, 0.98f, 0.31f);
		colors[ImGuiCol_HeaderHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
		colors[ImGuiCol_HeaderActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
		colors[ImGuiCol_Separator] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
		colors[ImGuiCol_SeparatorHovered] = ImVec4(0.10f, 0.40f, 0.75f, 0.78f);
		colors[ImGuiCol_SeparatorActive] = ImVec4(0.10f, 0.40f, 0.75f, 1.00f);
		colors[ImGuiCol_ResizeGrip] = ImVec4(0.26f, 0.59f, 0.98f, 0.20f);
		colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
		colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
		colors[ImGuiCol_Tab] = ImVec4(0.18f, 0.35f, 0.58f, 0.86f);
		colors[ImGuiCol_TabHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
		colors[ImGuiCol_TabActive] = ImVec4(0.20f, 0.41f, 0.68f, 1.00f);
		colors[ImGuiCol_TabUnfocused] = ImVec4(0.07f, 0.10f, 0.15f, 0.97f);
		colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.14f, 0.26f, 0.42f, 1.00f);
		colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
		colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
		colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
		colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
		colors[ImGuiCol_TableHeaderBg] = ImVec4(0.19f, 0.19f, 0.20f, 1.00f);
		colors[ImGuiCol_TableBorderStrong] = ImVec4(0.31f, 0.31f, 0.35f, 1.00f);
		colors[ImGuiCol_TableBorderLight] = ImVec4(0.23f, 0.23f, 0.25f, 1.00f);
		colors[ImGuiCol_TableRowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
		colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
		colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
		colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
		colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
		colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
		colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
		break;
	case ThemeName::Dark:
		Gm.windowBgColor = sf::Color(30, 30, 30);
		colors[ImGuiCol_Text] = ImVec4(0.82f, 0.82f, 0.82f, 1.00f);
		colors[ImGuiCol_TextDisabled] = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
		colors[ImGuiCol_WindowBg] = ImVec4(0.13f, 0.14f, 0.16f, 1.00f);
		colors[ImGuiCol_ChildBg] = ImVec4(0.17f, 0.18f, 0.20f, 1.00f);
		colors[ImGuiCol_PopupBg] = ImVec4(0.22f, 0.24f, 0.25f, 1.00f);
		colors[ImGuiCol_Border] = ImVec4(0.16f, 0.17f, 0.18f, 1.00f);
		colors[ImGuiCol_BorderShadow] = ImVec4(0.16f, 0.17f, 0.18f, 1.00f);
		colors[ImGuiCol_FrameBg] = ImVec4(0.14f, 0.15f, 0.16f, 1.00f);
		colors[ImGuiCol_FrameBgHovered] = ImVec4(0.84f, 0.34f, 0.17f, 1.00f);
		colors[ImGuiCol_FrameBgActive] = ImVec4(0.59f, 0.24f, 0.12f, 1.00f);
		colors[ImGuiCol_TitleBg] = ImVec4(0.13f, 0.14f, 0.16f, 1.00f);
		colors[ImGuiCol_TitleBgActive] = ImVec4(0.13f, 0.14f, 0.16f, 1.00f);
		colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.13f, 0.14f, 0.16f, 1.00f);
		colors[ImGuiCol_MenuBarBg] = ImVec4(0.13f, 0.14f, 0.16f, 1.00f);
		colors[ImGuiCol_ScrollbarBg] = ImVec4(0.13f, 0.14f, 0.16f, 1.00f);
		colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
		colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.75f, 0.30f, 0.15f, 1.00f);
		colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
		colors[ImGuiCol_CheckMark] = ImVec4(0.90f, 0.90f, 0.90f, 0.50f);
		colors[ImGuiCol_SliderGrab] = ImVec4(1.00f, 1.00f, 1.00f, 0.30f);
		colors[ImGuiCol_SliderGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
		colors[ImGuiCol_Button] = ImVec4(0.19f, 0.20f, 0.22f, 1.00f);
		colors[ImGuiCol_ButtonHovered] = ImVec4(0.84f, 0.34f, 0.17f, 1.00f);
		colors[ImGuiCol_ButtonActive] = ImVec4(0.59f, 0.24f, 0.12f, 1.00f);
		colors[ImGuiCol_Header] = ImVec4(0.22f, 0.23f, 0.25f, 1.00f);
		colors[ImGuiCol_HeaderHovered] = ImVec4(0.84f, 0.34f, 0.17f, 1.00f);
		colors[ImGuiCol_HeaderActive] = ImVec4(0.59f, 0.24f, 0.12f, 1.00f);
		colors[ImGuiCol_Separator] = ImVec4(0.17f, 0.18f, 0.20f, 1.00f);
		colors[ImGuiCol_SeparatorHovered] = ImVec4(0.75f, 0.30f, 0.15f, 1.00f);
		colors[ImGuiCol_SeparatorActive] = ImVec4(0.59f, 0.24f, 0.12f, 1.00f);
		colors[ImGuiCol_ResizeGrip] = ImVec4(0.84f, 0.34f, 0.17f, 0.14f);
		colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.84f, 0.34f, 0.17f, 1.00f);
		colors[ImGuiCol_ResizeGripActive] = ImVec4(0.59f, 0.24f, 0.12f, 1.00f);
		colors[ImGuiCol_Tab] = ImVec4(0.16f, 0.16f, 0.16f, 1.00f);
		colors[ImGuiCol_TabHovered] = ImVec4(0.84f, 0.34f, 0.17f, 1.00f);
		colors[ImGuiCol_TabActive] = ImVec4(0.68f, 0.28f, 0.14f, 1.00f);
		colors[ImGuiCol_TabUnfocused] = ImVec4(0.13f, 0.14f, 0.16f, 1.00f);
		colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.17f, 0.18f, 0.20f, 1.00f);
		//colors[ImGuiCol_DockingPreview] = ImVec4(0.19f, 0.20f, 0.22f, 1.00f);
		//colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
		colors[ImGuiCol_PlotLines] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
		colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
		colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
		colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
		colors[ImGuiCol_TextSelectedBg] = ImVec4(0.75f, 0.30f, 0.15f, 1.00f);
		colors[ImGuiCol_DragDropTarget] = ImVec4(0.75f, 0.30f, 0.15f, 1.00f);
		colors[ImGuiCol_NavHighlight] = ImVec4(0.75f, 0.30f, 0.15f, 1.00f);
		colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
		colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
		colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.20f, 0.20f, 0.20f, 0.35f);
		break;
	case ThemeName::Light:
		Gm.windowBgColor = sf::Color(192, 192, 192);
		colors[ImGuiCol_Text] = ImVec4(0.15f, 0.15f, 0.15f, 1.00f);
		colors[ImGuiCol_TextDisabled] = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
		colors[ImGuiCol_WindowBg] = ImVec4(0.87f, 0.87f, 0.87f, 1.00f);
		colors[ImGuiCol_ChildBg] = ImVec4(0.87f, 0.87f, 0.87f, 1.00f);
		colors[ImGuiCol_PopupBg] = ImVec4(0.87f, 0.87f, 0.87f, 1.00f);
		colors[ImGuiCol_Border] = ImVec4(0.89f, 0.89f, 0.89f, 1.00f);
		colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		colors[ImGuiCol_FrameBg] = ImVec4(0.93f, 0.93f, 0.93f, 1.00f);
		colors[ImGuiCol_FrameBgHovered] = ImVec4(1.00f, 0.69f, 0.07f, 0.69f);
		colors[ImGuiCol_FrameBgActive] = ImVec4(1.00f, 0.82f, 0.46f, 0.69f);
		colors[ImGuiCol_TitleBg] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
		colors[ImGuiCol_TitleBgActive] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
		colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
		colors[ImGuiCol_MenuBarBg] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
		colors[ImGuiCol_ScrollbarBg] = ImVec4(0.87f, 0.87f, 0.87f, 1.00f);
		colors[ImGuiCol_ScrollbarGrab] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
		colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(1.00f, 0.69f, 0.07f, 0.69f);
		colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(1.00f, 0.82f, 0.46f, 0.69f);
		colors[ImGuiCol_CheckMark] = ImVec4(0.01f, 0.01f, 0.01f, 0.63f);
		colors[ImGuiCol_SliderGrab] = ImVec4(1.00f, 0.69f, 0.07f, 0.69f);
		colors[ImGuiCol_SliderGrabActive] = ImVec4(1.00f, 0.82f, 0.46f, 0.69f);
		colors[ImGuiCol_Button] = ImVec4(0.83f, 0.83f, 0.83f, 1.00f);
		colors[ImGuiCol_ButtonHovered] = ImVec4(1.00f, 0.69f, 0.07f, 0.69f);
		colors[ImGuiCol_ButtonActive] = ImVec4(1.00f, 0.82f, 0.46f, 0.69f);
		colors[ImGuiCol_Header] = ImVec4(0.67f, 0.67f, 0.67f, 1.00f);
		colors[ImGuiCol_HeaderHovered] = ImVec4(1.00f, 0.69f, 0.07f, 1.00f);
		colors[ImGuiCol_HeaderActive] = ImVec4(1.00f, 0.82f, 0.46f, 0.69f);
		colors[ImGuiCol_Separator] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
		colors[ImGuiCol_SeparatorHovered] = ImVec4(1.00f, 0.69f, 0.07f, 1.00f);
		colors[ImGuiCol_SeparatorActive] = ImVec4(1.00f, 0.82f, 0.46f, 0.69f);
		colors[ImGuiCol_ResizeGrip] = ImVec4(1.00f, 1.00f, 1.00f, 0.18f);
		colors[ImGuiCol_ResizeGripHovered] = ImVec4(1.00f, 0.69f, 0.07f, 1.00f);
		colors[ImGuiCol_ResizeGripActive] = ImVec4(1.00f, 0.82f, 0.46f, 0.69f);
		colors[ImGuiCol_Tab] = ImVec4(0.16f, 0.16f, 0.16f, 0.00f);
		colors[ImGuiCol_TabHovered] = ImVec4(1.00f, 0.69f, 0.07f, 1.00f);
		colors[ImGuiCol_TabActive] = ImVec4(1.00f, 0.69f, 0.07f, 1.00f);
		colors[ImGuiCol_TabUnfocused] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
		colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.87f, 0.87f, 0.87f, 1.00f);
		//colors[ImGuiCol_DockingPreview] = ImVec4(1.00f, 0.82f, 0.46f, 0.69f);
		//colors[ImGuiCol_DockingEmptyBg] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
		colors[ImGuiCol_PlotLines] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
		colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
		colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
		colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
		colors[ImGuiCol_TextSelectedBg] = ImVec4(1.00f, 0.69f, 0.07f, 1.00f);
		colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 0.69f, 0.07f, 1.00f);
		colors[ImGuiCol_NavHighlight] = ImVec4(1.00f, 0.69f, 0.07f, 1.00f);
		colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
		colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.87f, 0.87f, 0.87f, 1.00f);
		colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.20f, 0.20f, 0.20f, 0.35f);
		break;
	case ThemeName::Diana:
		Gm.windowBgColor = sf::Color(255, 247, 236);
		colors[ImGuiCol_Text] = ImVec4(1.00f, 0.97f, 0.93f, 1.00f);
		colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.41f, 0.37f, 1.00f);
		colors[ImGuiCol_WindowBg] = ImVec4(0.82f, 0.67f, 0.61f, 0.62f);
		colors[ImGuiCol_ChildBg] = ImVec4(0.80f, 0.68f, 0.60f, 1.00f);
		colors[ImGuiCol_PopupBg] = ImVec4(0.80f, 0.67f, 0.59f, 1.00f);
		colors[ImGuiCol_Border] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
		colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		colors[ImGuiCol_FrameBg] = ImVec4(0.77f, 0.60f, 0.50f, 1.00f);
		colors[ImGuiCol_FrameBgHovered] = ImVec4(0.80f, 0.67f, 0.60f, 1.00f);
		colors[ImGuiCol_FrameBgActive] = ImVec4(0.80f, 0.67f, 0.60f, 1.00f);
		colors[ImGuiCol_TitleBg] = ImVec4(0.80f, 0.68f, 0.60f, 1.00f);
		colors[ImGuiCol_TitleBgActive] = ImVec4(0.91f, 0.56f, 0.55f, 1.00f);
		colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.80f, 0.67f, 0.59f, 1.00f);
		colors[ImGuiCol_MenuBarBg] = ImVec4(0.80f, 0.67f, 0.59f, 1.00f);
		colors[ImGuiCol_ScrollbarBg] = ImVec4(0.72f, 0.60f, 0.53f, 1.00f);
		colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.96f, 0.59f, 0.58f, 0.55f);
		colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
		colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
		colors[ImGuiCol_CheckMark] = ImVec4(0.80f, 0.67f, 0.60f, 1.00f);
		colors[ImGuiCol_SliderGrab] = ImVec4(0.80f, 0.67f, 0.60f, 1.00f);
		colors[ImGuiCol_SliderGrabActive] = ImVec4(0.78f, 0.60f, 0.50f, 1.00f);
		colors[ImGuiCol_Button] = ImVec4(0.80f, 0.67f, 0.60f, 1.00f);
		colors[ImGuiCol_ButtonHovered] = ImVec4(0.77f, 0.57f, 0.46f, 1.00f);
		colors[ImGuiCol_ButtonActive] = ImVec4(0.80f, 0.67f, 0.60f, 0.48f);
		colors[ImGuiCol_Header] = ImVec4(0.83f, 0.62f, 0.50f, 0.48f);
		colors[ImGuiCol_HeaderHovered] = ImVec4(0.88f, 0.72f, 0.64f, 1.00f);
		colors[ImGuiCol_HeaderActive] = ImVec4(0.80f, 0.67f, 0.60f, 1.00f);
		colors[ImGuiCol_Separator] = ImVec4(0.54f, 0.43f, 0.37f, 0.52f);
		colors[ImGuiCol_SeparatorHovered] = ImVec4(0.80f, 0.67f, 0.60f, 1.00f);
		colors[ImGuiCol_SeparatorActive] = ImVec4(0.80f, 0.67f, 0.60f, 1.00f);
		colors[ImGuiCol_ResizeGrip] = ImVec4(0.80f, 0.67f, 0.60f, 1.00f);
		colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.80f, 0.67f, 0.60f, 1.00f);
		colors[ImGuiCol_ResizeGripActive] = ImVec4(0.80f, 0.67f, 0.60f, 1.00f);
		colors[ImGuiCol_Tab] = ImVec4(0.80f, 0.67f, 0.59f, 1.00f);
		colors[ImGuiCol_TabHovered] = ImVec4(0.78f, 0.63f, 0.55f, 1.00f);
		colors[ImGuiCol_TabActive] = ImVec4(0.91f, 0.56f, 0.55f, 1.00f);
		colors[ImGuiCol_TabUnfocused] = ImVec4(0.07f, 0.10f, 0.15f, 0.97f);
		colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.14f, 0.26f, 0.42f, 1.00f);
		colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
		colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
		colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
		colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
		colors[ImGuiCol_TableHeaderBg] = ImVec4(0.80f, 0.67f, 0.59f, 1.00f);
		colors[ImGuiCol_TableBorderStrong] = ImVec4(0.75f, 0.59f, 0.49f, 1.00f);
		colors[ImGuiCol_TableBorderLight] = ImVec4(0.88f, 0.74f, 0.65f, 1.00f);
		colors[ImGuiCol_TableRowBg] = ImVec4(0.83f, 0.68f, 0.58f, 1.00f);
		colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
		colors[ImGuiCol_TextSelectedBg] = ImVec4(0.80f, 0.68f, 0.60f, 1.00f);
		colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
		colors[ImGuiCol_NavHighlight] = ImVec4(0.83f, 0.58f, 0.43f, 1.00f);
		colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
		colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
		colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
		break;
	}
}

void Gui::update()
{
	// functions
	auto newMap = [&]()
	{
		for (auto o : ObjMgr.objects)
		{
			if (inPalette(o->index) || o->index == GetIndex(Blood) || o->index == GetIndex(Player))
				DestroyInst(o);
		}
		showGameWindow = true;
	};
	auto openMap = [&]()
	{
		auto f = GetOpenFile(
			"All Map Files (*.jmap;*.map)\0*.jmap;*.map\0"
			"Jtool Map File (*.jmap)\0*.jmap\0"
			"RMJ Map File (*.map)\0*.map\0"
			, "Open Map");
		if (f != "")
		{
			filesystem::path filename(f);
			auto ext = filename.extension();
			if (ext == ".jmap")
				MapMgr.loadJmap(filename.string());
			else if (ext == ".map")
				MapMgr.loadRMJ(filename.string());
		}
		showGameWindow = true;
	};
	auto saveMap = [&]()
	{
		auto f = GetSaveFile(
			"Jtool Map File (*.jmap)\0*.jmap\0"
			"RMJ Map File (*.map)\0*.map\0"
			, "Open Map");
		if (f.filename != "")
		{
			filesystem::path filename(f.filename);
			auto ext = filename.extension();
			string ename;
			switch (f.index)
			{
			case 1:
				ename = ".jmap";
				if (ext != ename)
					filename += ename;
				MapMgr.saveJmap(filename.string());
				break;
			case 2:
				ename = ".map";
				if (ext != ename)
					filename += ename;
				MapMgr.saveRMJ(filename.string());
				break;
			}
		}
	};

	// shortcut keys
	if (InputMgr.isKeyPress(sf::Keyboard::F2))
		newMap();
	if (InputMgr.isKeyHold(sf::Keyboard::LControl) && InputMgr.isKeyPress(sf::Keyboard::O))
		openMap();
	if (InputMgr.isKeyHold(sf::Keyboard::LControl) && InputMgr.isKeyPress(sf::Keyboard::S))
		saveMap();
	if (InputMgr.isKeyHold(sf::Keyboard::LControl) && InputMgr.isKeyPress(sf::Keyboard::Z) && !RecMgr.tasPause)
		Gm.editor.undo();
	if (InputMgr.isKeyHold(sf::Keyboard::LControl) && InputMgr.isKeyPress(sf::Keyboard::Y) && !RecMgr.tasPause)
		Gm.editor.redo();
	if (InputMgr.isKeyHold(sf::Keyboard::F8))
		showSkin = true;
	if (InputMgr.isKeyHold(sf::Keyboard::G))
		showSnap = true;

	// main menu
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("New Map", "F2"))
			{
				newMap();
			}
			ImGui::Separator();
			if (ImGui::MenuItem("Open Map", "CTRL+O"))
			{
				openMap();
			}
			if (ImGui::MenuItem("Save Map", "CTRL+S"))
			{
				saveMap();
			}
			ImGui::Separator();
			if (ImGui::MenuItem("Exit", "ALT+F4"))
			{
				Gm.window->close();
			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Edit", showGameWindow))
		{
			if (ImGui::MenuItem("Undo", "CTRL+Z", false, Gm.editor.undoPos > 0 && !RecMgr.tasPause))
			{
				Gm.editor.undo();
			}
			if (ImGui::MenuItem("Redo", "CTRL+Y", false, Gm.editor.undoPos < Gm.editor.undoEvents.size() && !RecMgr.tasPause))
			{
				Gm.editor.redo();
			}
			ImGui::Separator();
			if (ImGui::MenuItem("Snap", "G"))
			{
				showSnap = true;
			}
			if (ImGui::MenuItem("Shift"))
			{
				showShift = true;
			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("View", showGameWindow))
		{
			if (ImGui::BeginMenu("Grid"))
			{
				if (ImGui::MenuItem("Show Grid", nullptr, showGrid))
				{
					showGrid = !showGrid;
					if (showGrid)
					{
						updateGrid();
					}
				}
				ImGui::Separator();
				if (ImGui::MenuItem("Set Size"))
				{
					showGridWindow = !showGridWindow;
				}
				ImGui::EndMenu();
			}
			ImGui::Separator();
			if (ImGui::MenuItem("Show Mouse Coord", nullptr, showMouseCoord))
			{
				showMouseCoord = !showMouseCoord;
			}
			ImGui::Separator();
			if (ImGui::BeginMenu("Skin"))
			{
				if (ImGui::MenuItem("Next"))
				{
					auto index = find(SkinMgr.skinNames.begin(), SkinMgr.skinNames.end(), SkinMgr.curSkin->skinName) -
						SkinMgr.skinNames.begin();
					if (++index == SkinMgr.skinNames.size())
					{
						index = 0;
					}
					SkinMgr.apply(SkinMgr.skinNames[index]);
				}
				if (ImGui::MenuItem("Previous"))
				{
					auto index = find(SkinMgr.skinNames.begin(), SkinMgr.skinNames.end(), SkinMgr.curSkin->skinName) -
						SkinMgr.skinNames.begin();

					if (--index == -1)
					{
						index = SkinMgr.skinNames.size() - 1;
					}
					SkinMgr.apply(SkinMgr.skinNames[index]);
				}
				if (ImGui::MenuItem("Random"))
				{
					auto index = find(SkinMgr.skinNames.begin(), SkinMgr.skinNames.end(), SkinMgr.curSkin->skinName) -
						SkinMgr.skinNames.begin();

					int newIndex = Random::get(0, static_cast<int>(SkinMgr.skinNames.size()) - 1);
					while (index == newIndex)
					{
						newIndex = Random::get(0, static_cast<int>(SkinMgr.skinNames.size()) - 1);
					}
					SkinMgr.apply(SkinMgr.skinNames[newIndex]);
				}
				ImGui::Separator();
				if (ImGui::MenuItem("Choose", "F8"))
				{
					showSkin = true;
				}
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("GUI Theme"))
			{
				if (ImGui::MenuItem("Default"))
				{
					setGuiTheme(ThemeName::Default);
				}
				if (ImGui::MenuItem("Dark"))
				{
					setGuiTheme(ThemeName::Dark);
				}
				if (ImGui::MenuItem("Light"))
				{
					setGuiTheme(ThemeName::Light);
				}
				if (ImGui::MenuItem("Diana"))
				{
					setGuiTheme(ThemeName::Diana);
				}
				ImGui::EndMenu();
			}

			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Player", showGameWindow))
		{
			if (ImGui::MenuItem("Dot Kid", nullptr, PlayerMgr.dotkid))
			{
				PlayerMgr.dotkid = !PlayerMgr.dotkid;
			}
			if (ImGui::MenuItem("Outline", nullptr, PlayerMgr.dotkidOutline, PlayerMgr.dotkid))
			{
				PlayerMgr.dotkidOutline = !PlayerMgr.dotkidOutline;
			}
			ImGui::Separator();
			if (ImGui::MenuItem("Enable Death", nullptr, PlayerMgr.deathEnable))
			{
				PlayerMgr.deathEnable = !PlayerMgr.deathEnable;
			}
			if (ImGui::MenuItem("Inf Jump", nullptr, PlayerMgr.infjump))
			{
				PlayerMgr.infjump = !PlayerMgr.infjump;
			}
			ImGui::Separator();
			if (ImGui::BeginMenu("Save Type"))
			{
				if (ImGui::MenuItem("Only Shoot", nullptr, PlayerMgr.saveType == SaveType::OnlyShoot))
				{
					PlayerMgr.saveType = SaveType::OnlyShoot;
				}
				if (ImGui::MenuItem("Shoot Or Bullet", nullptr, PlayerMgr.saveType == SaveType::ShootOrBullet))
				{
					PlayerMgr.saveType = SaveType::ShootOrBullet;
				}
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Map Border Type"))
			{
				if (ImGui::MenuItem("Killer", nullptr, PlayerMgr.deathBorder == DeathBorder::Killer))
				{
					PlayerMgr.deathBorder = DeathBorder::Killer;
				}
				if (ImGui::MenuItem("Solid", nullptr, PlayerMgr.deathBorder == DeathBorder::Solid))
				{
					PlayerMgr.deathBorder = DeathBorder::Solid;
				}
				ImGui::EndMenu();
			}
			ImGui::Separator();
			if (ImGui::BeginMenu("Mask (Hitbox)", !PlayerMgr.dotkid))
			{
				if (ImGui::MenuItem("Only Player", nullptr, PlayerMgr.showMask == ShowMask::OnlyPlayer))
				{
					PlayerMgr.showMask = ShowMask::OnlyPlayer;
				}
				if (ImGui::MenuItem("Only Mask", nullptr, PlayerMgr.showMask == ShowMask::OnlyMask))
				{
					PlayerMgr.showMask = ShowMask::OnlyMask;
				}
				if (ImGui::MenuItem("Player And Mask", nullptr, PlayerMgr.showMask == ShowMask::PlayerAndMask))
				{
					PlayerMgr.showMask = ShowMask::PlayerAndMask;
				}
				ImGui::EndMenu();
			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Window"))
		{
			if (ImGui::MenuItem("Game Window", nullptr, showGameWindow))
			{
				showGameWindow = !showGameWindow;
			}
			if (ImGui::MenuItem("Palette", nullptr, showPalette))
			{
				showPalette = !showPalette;
			}
			if (ImGui::MenuItem("Debug Window", nullptr, showDebug))
			{
				showDebug = !showDebug;
			}
			if (ImGui::MenuItem("Shift", nullptr, showShift))
			{
				showShift = !showShift;
			}
			if (ImGui::MenuItem("Player Analysis", nullptr, showAnalysis))
			{
				showAnalysis = !showAnalysis;
			}
			if (ImGui::MenuItem("TAS", nullptr, showTAS))
			{
				showTAS = !showTAS;
			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Help"))
		{
			if (ImGui::MenuItem("Github"))
			{
				ShellExecuteA(nullptr, "open", "https://github.com/cubeww/imjtool", nullptr, nullptr, 10);
			}
			ImGui::Separator();
			if (ImGui::MenuItem("About"))
			{
				showAbout = true;
			}
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}

	// game window
	if (showGameWindow)
	{
		ImGui::SetNextWindowSize(ImVec2(816, 650), ImGuiCond_Once);
		int flag = ImGuiWindowFlags_NoResize;
		if (!Gm.editor.mouseInTitle)
			flag |= ImGuiWindowFlags_NoMove;
		if (ImGui::Begin("Game Window", &showGameWindow, flag))
		{
			auto cursorStartPos = ImGui::GetCursorStartPos();
			auto windowPos = ImGui::GetWindowPos();
			ImGui::Image(*Gm.gameTexture);

			if (!RecMgr.tasPause)
				Gm.editor.update();

			if (showMouseCoord)
			{
				auto pos = ImVec2(ImGui::GetMousePos().x - windowPos.x - cursorStartPos.x,
					ImGui::GetMousePos().y - windowPos.y - cursorStartPos.y);
				if (pos.x >= 0 && pos.x <= 800 && pos.y >= 0 && pos.y <= 608)
				{
					ImGui::BeginTooltip();
					auto coord = "(" + to_string(FloorToInt(pos.x)) + ", " + to_string(FloorToInt(pos.y)) + ")";
					ImGui::Text(coord.data());
					ImGui::EndTooltip();
				}
			}
		}
		ImGui::End();
	}

	// palette
	if (showPalette)
	{
		ImGui::SetNextWindowSize(ImVec2(200, 300), ImGuiCond_Once);
		ImGui::Begin("Palette", &showPalette);
		auto addObject = [&](int index, int group, string hint = "")
		{
			auto name = spriteOf(index);
			if (paletteIcons[index] == nullptr)
			{
				shared_ptr<sf::Sprite> spr = SkinMgr.getCurrentSprite(name)->items[0]->sprite;
				spr->setPosition(16, 16);
				spr->setOrigin(spr->getLocalBounds().width / 2, spr->getLocalBounds().height / 2);
				auto tex = make_shared<sf::RenderTexture>();
				tex->create(32, 32);
				tex->clear(sf::Color::Transparent);
				tex->draw(*spr);
				paletteIcons[index] = tex;
			}

			if (ImGui::ImageButton(*paletteIcons[index]))
			{
				Gm.editor.selectIndex = index;
				curGroup = group;
			}
			if (hint != "" && ImGui::IsItemHovered())
			{
				ImGui::BeginTooltip();
				ImGui::Text(hint.data());
				ImGui::EndTooltip();
			}
		};
		if (ImGui::CollapsingHeader("Player"))
		{
			addObject(GetIndex(PlayerStart), 0);
			ImGui::SameLine();
			addObject(GetIndex(Save), 0);
			ImGui::SameLine();
			addObject(GetIndex(Warp), 0);
		}
		if (ImGui::CollapsingHeader("Killer"))
		{
			addObject(GetIndex(SpikeUp), 1);
			ImGui::SameLine();
			addObject(GetIndex(SpikeDown), 1);
			ImGui::SameLine();
			addObject(GetIndex(SpikeLeft), 1);
			ImGui::SameLine();
			addObject(GetIndex(SpikeRight), 1);

			addObject(GetIndex(MiniSpikeUp), 2);
			ImGui::SameLine();
			addObject(GetIndex(MiniSpikeDown), 2);
			ImGui::SameLine();
			addObject(GetIndex(MiniSpikeLeft), 2);
			ImGui::SameLine();
			addObject(GetIndex(MiniSpikeRight), 2);

			addObject(GetIndex(Apple), 3);
			ImGui::SameLine();
			addObject(GetIndex(KillerBlock), 3);
		}
		if (ImGui::CollapsingHeader("Block & Platform"))
		{
			addObject(GetIndex(Block), 4);
			ImGui::SameLine();
			addObject(GetIndex(MiniBlock), 4);
			ImGui::SameLine();
			addObject(GetIndex(Platform), 4);
			ImGui::SameLine();
			addObject(GetIndex(BulletBlocker), 4);
		}
		if (ImGui::CollapsingHeader("Vine & Water"))
		{
			addObject(GetIndex(WalljumpR), 5);
			ImGui::SameLine();
			addObject(GetIndex(WalljumpL), 5);

			addObject(GetIndex(Water), 6, "Water 1 (Refresh Jump, High)");
			ImGui::SameLine();
			addObject(GetIndex(Water2), 6, "Water 2 (No Refresh Jump)");
			ImGui::SameLine();
			addObject(GetIndex(Water3), 6, "Water 3 (Refresh Jump)");
		}
		if (ImGui::CollapsingHeader("Misc"))
		{
			addObject(GetIndex(GravityArrowUp), 7);
			ImGui::SameLine();
			addObject(GetIndex(GravityArrowDown), 7);
		}
		ImGui::End();
	}

	// palette shortcuts
	if (InputMgr.mouseWheelDown)
	{
		auto index = find(groupIndex[curGroup].begin(), groupIndex[curGroup].end(), Gm.editor.selectIndex) - groupIndex[
			curGroup].begin();
			auto size = groupIndex[curGroup].size();
			if (++index == size)
				index = 0;
			Gm.editor.selectIndex = groupIndex[curGroup][index];
	}
	if (InputMgr.mouseWheelUp)
	{
		auto index = find(groupIndex[curGroup].begin(), groupIndex[curGroup].end(), Gm.editor.selectIndex) - groupIndex[
			curGroup].begin();
			auto size = groupIndex[curGroup].size();
			if (--index == -1)
				index = size - 1;
			Gm.editor.selectIndex = groupIndex[curGroup][index];
	}
	for (int i = sf::Keyboard::Num1; i <= sf::Keyboard::Num1 + groupIndex.size() - 1; i++)
	{
		if (InputMgr.isKeyPress(i))
		{
			curGroup = i - sf::Keyboard::Num1;
			Gm.editor.selectIndex = groupIndex[curGroup][0];
		}
	}

	auto textDouble = [&](string name, double value)
	{
		name += ": ";
		string s = to_string(value);
		s.erase(s.find_last_not_of('0') + 1, std::string::npos);
		s.erase(s.find_last_not_of('.') + 1, std::string::npos);
		ImGui::Text((name + s).data());
	};

	// debug window
	if (showDebug)
	{
		ImGui::SetNextWindowSize(ImVec2(250, 250), ImGuiCond_Once);
		ImGui::Begin("Debug Window", &showDebug);
		textDouble("FPS", Gm.fps);
		textDouble("Inst", ObjMgr.objects.size());
		textDouble("Sprite Count", debugSpriteCount);
		textDouble("Undo Stack Size", Gm.editor.undoEvents.size());
		textDouble("Undo Pos", Gm.editor.undoPos);
		ImGui::End();
	}

	// about window
	if (showAbout)
	{
		ImGui::OpenPopup("About");
	}
	ImGui::SetNextWindowSize(ImVec2(420, 420), ImGuiCond_Once);
	if (ImGui::BeginPopupModal("About", &showAbout))
	{
		ImGui::Text("Immediate Mode Jump Tool");
		ImGui::Text("By Cube");
		ImGui::Text("Powered By:");
		ImGui::Image(*ResMgr.textures["sfml"]);
		ImGui::Text("Simple and Fast Multimedia Library");
		ImGui::Image(*ResMgr.textures["imgui"]);
		ImGui::Text("Dear ImGui");
		if (ImGui::Button("Close"))
		{
			showAbout = false;
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}

	// shift window
	if (showShift)
	{
		ImGui::Begin("Shift Objects", &showShift);
		ImGui::InputInt("Shift X", &shiftX);
		ImGui::InputInt("Shift Y", &shiftY);

		ImGui::SetCursorPos(ImVec2(48, ImGui::GetCursorPos().y));

		if (ImGui::Button("U", ImVec2(32, 32)))
		{
			for (const auto& i : ObjMgr.objects)
			{
				if (i->index == GetIndex(Player))
					continue;
				Gm.editor.addMoveEvent(i, i->x, i->y, i->x, i->y - shiftY);
				i->y -= shiftY;
			}
			Gm.editor.finishEvent();
		}
		if (ImGui::Button("L", ImVec2(32, 32)))
		{
			for (const auto& i : ObjMgr.objects)
			{
				if (i->index == GetIndex(Player))
					continue;
				Gm.editor.addMoveEvent(i, i->x, i->y, i->x - shiftX, i->y);
				i->x -= shiftX;
			}
			Gm.editor.finishEvent();
		}
		ImGui::SameLine();
		if (ImGui::Button("D", ImVec2(32, 32)))
		{
			for (const auto& i : ObjMgr.objects)
			{
				if (i->index == GetIndex(Player))
					continue;
				Gm.editor.addMoveEvent(i, i->x, i->y, i->x, i->y + shiftY);
				i->y += shiftY;
			}
			Gm.editor.finishEvent();
		}
		ImGui::SameLine();
		if (ImGui::Button("R", ImVec2(32, 32)))
		{
			for (const auto& i : ObjMgr.objects)
			{
				if (i->index == GetIndex(Player))
					continue;
				Gm.editor.addMoveEvent(i, i->x, i->y, i->x + shiftX, i->y);
				i->x += shiftX;
			}
			Gm.editor.finishEvent();
		}

		ImGui::End();
	}

	// grid window
	if (showGridWindow)
	{
		ImGui::OpenPopup("Set Grid");
	}
	ImGui::SetNextWindowSize(ImVec2(200, 130), ImGuiCond_Once);
	if (ImGui::BeginPopupModal("Set Grid", &showGridWindow))
	{
		if (ImGui::Button("32"))
		{
			gridW = 32;
			gridH = 32;
		}
		ImGui::SameLine();
		if (ImGui::Button("16"))
		{
			gridW = 16;
			gridH = 16;
		}
		ImGui::SameLine();
		if (ImGui::Button("8"))
		{
			gridW = 8;
			gridH = 8;
		}
		ImGui::SameLine();
		if (ImGui::Button("1"))
		{
			gridW = 1;
			gridH = 1;
		}

		ImGui::InputInt("Grid W", &gridW);
		ImGui::InputInt("Grid H", &gridH);

		gridW = clamp(gridW, 1, 800);
		gridH = clamp(gridH, 1, 608);

		if (ImGui::Button("OK"))
		{
			updateGrid();
			showGridWindow = false;
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}

	// snap window
	if (showSnap)
	{
		ImGui::OpenPopup("Set Snap");
	}
	ImGui::SetNextWindowSize(ImVec2(200, 130), ImGuiCond_Once);
	if (ImGui::BeginPopupModal("Set Snap", &showSnap))
	{
		if (ImGui::Button("32"))
		{
			snapW = 32;
			snapH = 32;
		}
		ImGui::SameLine();
		if (ImGui::Button("16"))
		{
			snapW = 16;
			snapH = 16;
		}
		ImGui::SameLine();
		if (ImGui::Button("8"))
		{
			snapW = 8;
			snapH = 8;
		}
		ImGui::SameLine();
		if (ImGui::Button("1"))
		{
			snapW = 1;
			snapH = 1;
		}

		ImGui::InputInt("Snap W", &snapW);
		ImGui::InputInt("Snap H", &snapH);

		snapW = clamp(snapW, 1, 800);
		snapH = clamp(snapH, 1, 608);

		if (ImGui::Button("OK"))
		{
			Gm.editor.snap = ImVec2(snapW, snapH);
			showSnap = false;
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}

	// skin window
	if (showSkin)
	{
		ImGui::OpenPopup("Skin");
	}
	ImGui::SetNextWindowSize(ImVec2(430, 330), ImGuiCond_Once);
	if (ImGui::BeginPopupModal("Skin", &showSkin))
	{
		ImGui::Columns(2);
		ImGui::Text("Search");
		ImGui::SameLine();
		if (ImGui::InputText("##SearchSkin", &skinSearchStr))
		{
			skinSearchVec.clear();
			int index = 0;
			for (auto name : SkinMgr.skinNames)
			{
				if (name.find(skinSearchStr))
				{
					skinSearchVec.push_back(index);
				}
				index++;
			}
		}
		if (ImGui::BeginListBox("##Skins", ImVec2(200, 250)))
		{
			int index = 0;
			for (const auto& name : SkinMgr.skinNames)
			{
				if (find(skinSearchVec.begin(), skinSearchVec.end(), index) != skinSearchVec.end())
				{
					index++;
					continue;
				}
				if (ImGui::Selectable(name.data(), skinSelect == index) || SkinMgr.previewSkin == nullptr)
				{
					skinSelect = index;
					SkinMgr.previewSkin = make_shared<SkinPackage>(name);
				}

				index++;
			}
			ImGui::EndListBox();
		}
		ImGui::NextColumn();
		ImGui::Text("Preview:");

		auto startPos = ImGui::GetCursorPos();
		auto drawPreview = [&](int index, int xx, int yy)
		{
			auto name = spriteOf(index);
			ImGui::SetCursorPos(ImVec2(startPos.x + xx, startPos.y + yy));

			auto obj = SkinMgr.getPreview(name);
			if (obj != nullptr)
			{
				ImGui::Image(*obj->sprite->items[0]->sprite);
			}
			else
			{
				ImGui::Image(*ResMgr.sprites[name]->items[0]->sprite);
			}
		};
		auto d = 32;
		drawPreview(GetIndex(Warp), 0, 0);
		drawPreview(GetIndex(SpikeUp), d, 0);
		drawPreview(GetIndex(JumpRefresher), d * 2, 0);
		drawPreview(GetIndex(Block), d * 3, 0);
		drawPreview(GetIndex(WalljumpR), d * 3, 0);
		drawPreview(GetIndex(Block), d * 4, 0);
		drawPreview(GetIndex(WalljumpL), d * 4, 0);

		drawPreview(GetIndex(SpikeLeft), 0, d);
		drawPreview(GetIndex(Block), d, d);
		drawPreview(GetIndex(SpikeRight), d * 2, d);
		drawPreview(GetIndex(Platform), d * 3, d);
		drawPreview(GetIndex(Apple), d * 4, d);

		drawPreview(GetIndex(PlayerStart), 0, d * 2);
		drawPreview(GetIndex(SpikeDown), d, d * 2);
		drawPreview(GetIndex(MiniSpikeUp), d * 2, d * 2);
		drawPreview(GetIndex(MiniSpikeRight), d * 2 + 16, d * 2);
		drawPreview(GetIndex(MiniSpikeLeft), d * 2, d * 2 + 16);
		drawPreview(GetIndex(MiniSpikeDown), d * 2 + 16, d * 2 + 16);
		drawPreview(GetIndex(Water2), d * 3, d * 2);
		drawPreview(GetIndex(Save), d * 4, d * 2);

		ImGui::Columns();
		if (ImGui::Button("Apply"))
		{
			SkinMgr.apply(SkinMgr.previewSkin);
			showSkin = false;
		}
		ImGui::SameLine();
		if (ImGui::Button("Cancel"))
		{
			showSkin = false;
		}
		ImGui::EndPopup();
	}

	// analysis window
	auto textFrames = [&](string name, int count)
	{
		name += ": ";
		string s = to_string(count) + " frame";
		if (count != 1)
		{
			s += "s";
		}
		ImGui::Text((name + s).data());
	};
	auto textDuration = [&](string name, int dt)
	{
		name += ": ";
		string s;
		if (dt == 0)
		{
			s = "Good";
		}
		else
		{
			s = to_string(abs(dt)) + " frame";
			if (dt != 1)
				s += "s";
			if (dt > 0)
				s += " late";
			else
				s += " early";
		}

		ImGui::Text((name + s).data());
	};
	if (showAnalysis)
	{
		ImGui::SetNextWindowSize(ImVec2(250, 300), ImGuiCond_Once);
		ImGui::Begin("Player Analysis", &showAnalysis);
		textDouble("Align", FloorToInt(PlayerMgr.x) % 3);
		textDouble("X", PlayerMgr.x);
		textDouble("Y", PlayerMgr.y);
		ImGui::Separator();
		textFrames("Jump", PlayerMgr.frameCountJump1);
		textFrames("Pause", PlayerMgr.frameCountPause);
		textFrames("Djump", PlayerMgr.frameCountJump2);
		textFrames("Pause", PlayerMgr.frameCountPause2);
		ImGui::Separator();
		if (PlayerMgr.jcShow)
			textDuration("JC", PlayerMgr.jcDuration);
		else
			ImGui::Text("JC: Not");
		ImGui::Separator();
		if (PlayerMgr.bhopShow)
			textDuration("BH", PlayerMgr.bhopOffset);
		else
			ImGui::Text("BH: Not");

		ImGui::End();
	}

	// TAS window
	if (showTAS)
	{
		ImGui::SetNextWindowSize(ImVec2(350, 300), ImGuiCond_Once);
		ImGui::Begin("TAS", &showAnalysis);
		static int e = 0;
		int eLast = e;
		ImGui::RadioButton("1.0x", &e, 0);
		ImGui::RadioButton("0.5x", &e, 1);
		ImGui::RadioButton("0.2x", &e, 2);
		ImGui::RadioButton("Pause (Editor will be disabled)", &e, 3);
		if (eLast != e)
		{
			switch (e)
			{
			case 0: Gm.window->setFramerateLimit(50); break;
			case 1: Gm.window->setFramerateLimit(25); break;
			case 2: Gm.window->setFramerateLimit(10); break;
			case 3: Gm.window->setFramerateLimit(50); break;
			}
			RecMgr.tasPause = e == 3;
		}
		ImGui::Separator();
		static int stateIndex = 0;
		if (ImGui::Button("Save State"))
		{
			RecMgr.saveState();
			stateIndex = clamp(stateIndex + 1, 0, max(static_cast<int>(RecMgr.states.size()) - 1, 0));
		}
		ImGui::SameLine();
		if (ImGui::Button("delete State"))
		{
			if (!RecMgr.states.empty())
			{
				RecMgr.deleteState(stateIndex);
				stateIndex = clamp(stateIndex - 1, 0, max(static_cast<int>(RecMgr.states.size()) - 1, 0));
			}
		}
		if (ImGui::BeginListBox("##Player States"))
		{
			for (int i = RecMgr.states.size() - 1; i >= 0; i--)
			{
				if (ImGui::Selectable(to_string(i).c_str(), i == stateIndex))
				{
					stateIndex = i;
				}
			}
			ImGui::EndListBox();
		}
		if (ImGui::Button("Load State"))
		{
			if (!RecMgr.states.empty())
			{
				RecMgr.loadState(stateIndex);
			}
		}
		auto tasKey = [&](string name, sf::Keyboard::Key key)
		{
			ImGui::Checkbox((name + " Press").c_str(), &InputMgr.tasPress[key]);
			ImGui::SameLine();
			ImGui::Checkbox((name + " Hold").c_str(), &InputMgr.tasHold[key]);
			ImGui::SameLine();
			ImGui::Checkbox((name + " Release").c_str(), &InputMgr.tasRelease[key]);
		};
		if (RecMgr.tasPause)
		{
			ImGui::Separator();
			ImGui::Checkbox("Auto Clear Press", &RecMgr.autoClearPress);
			ImGui::Checkbox("Auto Clear Hold", &RecMgr.autoClearHold);
			ImGui::Checkbox("Auto Clear Release", &RecMgr.autoClearRelease);
			ImGui::Separator();
			tasKey("Left", sf::Keyboard::Left);
			tasKey("Right", sf::Keyboard::Right);
			tasKey("Jump", sf::Keyboard::LShift);
			ImGui::Separator();
			if (ImGui::Button("Next Frame (Space)") || InputMgr.isKeyPress(sf::Keyboard::Space))
			{
				RecMgr.nextFrame();
			}
		}
		ImGui::End();
	}
}

void Gui::updateGrid()
{
	if (gridTexture == nullptr)
	{
		gridTexture = make_shared<sf::RenderTexture>();
		gridTexture->create(800, 608);
	}
	gridTexture->clear(sf::Color::Transparent);
	for (auto yy = 0; yy <= 608; yy += gridH)
	{
		sf::RectangleShape rect;
		rect.setFillColor(sf::Color::Black);
		rect.setPosition(0, static_cast<float>(yy));
		rect.setSize(sf::Vector2f(800, 1));
		gridTexture->draw(rect);
	}
	for (auto xx = 0; xx <= 800; xx += gridW)
	{
		sf::RectangleShape rect;
		rect.setFillColor(sf::Color::Black);
		rect.setPosition(static_cast<float>(xx), 0);
		rect.setSize(sf::Vector2f(1, 608));
		gridTexture->draw(rect);
	}
}
