#include <Geode/Geode.hpp>

using namespace geode::prelude;

namespace moveForCommand {
	static constexpr const EditCommand kEditCommandHalfLeft = static_cast<EditCommand>(0x400);
	static constexpr const EditCommand kEditCommandHalfRight = static_cast<EditCommand>(0x401);
	static constexpr const EditCommand kEditCommandHalfUp = static_cast<EditCommand>(0x402);
	static constexpr const EditCommand kEditCommandHalfDown = static_cast<EditCommand>(0x403);

	static constexpr const EditCommand kEditCommandQuarterLeft = static_cast<EditCommand>(0x404);
	static constexpr const EditCommand kEditCommandQuarterRight = static_cast<EditCommand>(0x405);
	static constexpr const EditCommand kEditCommandQuarterUp = static_cast<EditCommand>(0x406);
	static constexpr const EditCommand kEditCommandQuarterDown = static_cast<EditCommand>(0x407);

	static constexpr const EditCommand kEditCommandEightLeft = static_cast<EditCommand>(0x408);
	static constexpr const EditCommand kEditCommandEightRight = static_cast<EditCommand>(0x409);
	static constexpr const EditCommand kEditCommandEightUp = static_cast<EditCommand>(0x40a);
	static constexpr const EditCommand kEditCommandEightDown = static_cast<EditCommand>(0x40b);

	static constexpr const EditCommand kEditCommandSmallerLeft = static_cast<EditCommand>(0x40c);
	static constexpr const EditCommand kEditCommandSmallerRight = static_cast<EditCommand>(0x40d);
	static constexpr const EditCommand kEditCommandSmallerUp = static_cast<EditCommand>(0x40e);
	static constexpr const EditCommand kEditCommandSmallerDown = static_cast<EditCommand>(0x40f);

	static constexpr const EditCommand kEditCommandQUnitLeft = static_cast<EditCommand>(0x410);
	static constexpr const EditCommand kEditCommandQUnitRight = static_cast<EditCommand>(0x411);
	static constexpr const EditCommand kEditCommandQUnitUp = static_cast<EditCommand>(0x412);
	static constexpr const EditCommand kEditCommandQUnitDown = static_cast<EditCommand>(0x413);
}

namespace rotationForCommand {
	static constexpr const EditCommand kEditCommandRotate45CW = static_cast<EditCommand>(0x414);
	static constexpr const EditCommand kEditCommandRotate45CCW = static_cast<EditCommand>(0x415);
	static constexpr const EditCommand kEditCommandRotate265CW = static_cast<EditCommand>(0x416);
	static constexpr const EditCommand kEditCommandRotate265CCW = static_cast<EditCommand>(0x417);
}