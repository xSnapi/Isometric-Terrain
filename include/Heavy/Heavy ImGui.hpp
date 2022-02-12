#pragma once

/*
	"Heavy" way to implement ImGui
*/

#include "Core.hpp"

#if ENABLE_IMGUI
#include <ImGui/imgui.h>
#include <ImGui/imgui-SFML.h>
namespace hv {
	class ImGuiWindow {
	public:
		ImGuiWindow(const char* name) {
			ImGui::Begin(name);
		}

		~ImGuiWindow() {
			ImGui::End();
		}
	};
}
#else
namespace hv {
	class ImGui {
	public:
		ImGui() {

		}

		~ImGui() {

		}
	};
}
#endif