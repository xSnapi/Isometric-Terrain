#pragma once

namespace hv {
	class Runtime;

	struct Times {
		static float DT;
		static float FDT;
	};

	extern const float& dt;
	extern const float& fdt;
}