#include <Geode/Geode.hpp>

using namespace geode::prelude;

#define ANDROID32_OFFSET 0x10000

$execute {
    //listenForSettingChanges("editor-extension", [](bool) {
        //if (Mod::get()->getSettingValue<bool>("editor-extension")) { // This is bad?
            #ifdef GEODE_IS_WINDOWS
            Mod::get()->patch(reinterpret_cast<void*>(geode::base::get() + 0x4779c), { 0xeb }); // onCreateObject
            Mod::get()->patch(reinterpret_cast<void*>(geode::base::get() + 0x477d2), { 0xeb });
            Mod::get()->patch(reinterpret_cast<void*>(geode::base::get() + 0x477e8), { 0xeb });
            Mod::get()->patch(reinterpret_cast<void*>(geode::base::get() + 0x477b9), { 0xeb });

            Mod::get()->patch(reinterpret_cast<void*>(geode::base::get() + 0x4b513), { 0xeb }); // getLimitedPosition
            Mod::get()->patch(reinterpret_cast<void*>(geode::base::get() + 0x4b525), { 0xeb });
            Mod::get()->patch(reinterpret_cast<void*>(geode::base::get() + 0x4b53e), { 0xeb });
            Mod::get()->patch(reinterpret_cast<void*>(geode::base::get() + 0x4b562), { 0xeb });

            Mod::get()->patch(reinterpret_cast<void*>(geode::base::get() + 0x4b445), { 0xeb, 0x44 }); // moveObject

            Mod::get()->patch(reinterpret_cast<void*>(geode::base::get() + 0x14a74c), { 0x00, 0x60, 0xea, 0x4a });

            Mod::get()->patch(reinterpret_cast<void*>(geode::base::get() + 0x93861), { 0x24, 0xa3, 0x54, 0x00 });
            Mod::get()->patch(reinterpret_cast<void*>(geode::base::get() + 0x9399b), { 0x24, 0xa3, 0x54, 0x00 });
            Mod::get()->patch(reinterpret_cast<void*>(geode::base::get() + 0x939d3), { 0x24, 0xa3, 0x54, 0x00 });
            Mod::get()->patch(reinterpret_cast<void*>(geode::base::get() + 0x93aed), { 0x24, 0xa3, 0x54, 0x00 });
            Mod::get()->patch(reinterpret_cast<void*>(geode::base::get() + 0x93c72), { 0x24, 0xa3, 0x54, 0x00 });
            Mod::get()->patch(reinterpret_cast<void*>(geode::base::get() + 0x94073), { 0x24, 0xa3, 0x54, 0x00 });
            Mod::get()->patch(reinterpret_cast<void*>(geode::base::get() + 0x94112), { 0x24, 0xa3, 0x54, 0x00 });
            Mod::get()->patch(reinterpret_cast<void*>(geode::base::get() + 0x94667), { 0x24, 0xa3, 0x54, 0x00 });
            Mod::get()->patch(reinterpret_cast<void*>(geode::base::get() + 0x946f3), { 0x24, 0xa3, 0x54, 0x00 });
            #endif

            #ifdef GEODE_IS_ANDROID32
            Mod::get()->patch(reinterpret_cast<void*>(geode::base::get() + 0x1eac20 - ANDROID32_OFFSET), { 0x00, 0x00, 0x00, 0x00 }); // Grid
            Mod::get()->patch(reinterpret_cast<void*>(geode::base::get() + 0x1eb054 - ANDROID32_OFFSET), { 0x00, 0x00, 0x00, 0x00 });
            Mod::get()->patch(reinterpret_cast<void*>(geode::base::get() + 0x1eac24 - ANDROID32_OFFSET), { 0x00, 0x60, 0xea, 0x4a });
            Mod::get()->patch(reinterpret_cast<void*>(geode::base::get() + 0x1eb058 - ANDROID32_OFFSET), { 0x00, 0x60, 0xea, 0x4a });

            Mod::get()->patch(reinterpret_cast<void*>(geode::base::get() + 0x1fb0bc - ANDROID32_OFFSET), { 0x00, 0x00, 0x00, 0x00 }); // onCreateObject
            Mod::get()->patch(reinterpret_cast<void*>(geode::base::get() + 0x1fb0c0 - ANDROID32_OFFSET), { 0x00, 0x00, 0x00, 0x00 });
            #endif
        // }
        // else {
        //     #ifdef GEODE_IS_WINDOWS
        //     Mod::get()->patch(reinterpret_cast<void*>(geode::base::get() + 0x4779c), { 0x77 });
        //     Mod::get()->patch(reinterpret_cast<void*>(geode::base::get() + 0x477d2), { 0x76 });
        //     Mod::get()->patch(reinterpret_cast<void*>(geode::base::get() + 0x477e8), { 0x76 });
        //     Mod::get()->patch(reinterpret_cast<void*>(geode::base::get() + 0x477b9), { 0x77 });

        //     Mod::get()->patch(reinterpret_cast<void*>(geode::base::get() + 0x4b513), { 0x76 });
        //     Mod::get()->patch(reinterpret_cast<void*>(geode::base::get() + 0x4b525), { 0x76 });
        //     Mod::get()->patch(reinterpret_cast<void*>(geode::base::get() + 0x4b53e), { 0x76 });
        //     Mod::get()->patch(reinterpret_cast<void*>(geode::base::get() + 0x4b562), { 0x76 });

        //     Mod::get()->patch(reinterpret_cast<void*>(geode::base::get() + 0x4b445), { 0x76, 0x09 });

        //     Mod::get()->patch(reinterpret_cast<void*>(geode::base::get() + 0x14a74c), { 0x00, 0x60, 0x6a, 0x47 });

        //     Mod::get()->patch(reinterpret_cast<void*>(geode::base::get() + 0x93861), { 0xb8, 0xa6, 0x54, 0x00 });
        //     Mod::get()->patch(reinterpret_cast<void*>(geode::base::get() + 0x9399b), { 0xb8, 0xa6, 0x54, 0x00 });
        //     Mod::get()->patch(reinterpret_cast<void*>(geode::base::get() + 0x939d3), { 0xb8, 0xa6, 0x54, 0x00 });
        //     Mod::get()->patch(reinterpret_cast<void*>(geode::base::get() + 0x93aed), { 0xb8, 0xa6, 0x54, 0x00 });
        //     Mod::get()->patch(reinterpret_cast<void*>(geode::base::get() + 0x93c72), { 0xb8, 0xa6, 0x54, 0x00 });
        //     Mod::get()->patch(reinterpret_cast<void*>(geode::base::get() + 0x94073), { 0xb8, 0xa6, 0x54, 0x00 });
        //     Mod::get()->patch(reinterpret_cast<void*>(geode::base::get() + 0x94112), { 0xb8, 0xa6, 0x54, 0x00 });
        //     Mod::get()->patch(reinterpret_cast<void*>(geode::base::get() + 0x94667), { 0xb8, 0xa6, 0x54, 0x00 });
        //     Mod::get()->patch(reinterpret_cast<void*>(geode::base::get() + 0x946f3), { 0xb8, 0xa6, 0x54, 0x00 });
        //     #endif

        //     #ifdef GEODE_IS_ANDROID32
        //     Mod::get()->patch(reinterpret_cast<void*>(geode::base::get() + 0x1eac20 - ANDROID32_OFFSET), { 0x00, 0x00, 0x96, 0x43 });
        //     Mod::get()->patch(reinterpret_cast<void*>(geode::base::get() + 0x1eb054 - ANDROID32_OFFSET), { 0x00, 0x00, 0x96, 0x43 });
        //     Mod::get()->patch(reinterpret_cast<void*>(geode::base::get() + 0x1eac24 - ANDROID32_OFFSET), { 0x00, 0x60, 0x6a, 0x47 });
        //     Mod::get()->patch(reinterpret_cast<void*>(geode::base::get() + 0x1eb058 - ANDROID32_OFFSET), { 0x00, 0x60, 0x6a, 0x47 });

        //     Mod::get()->patch(reinterpret_cast<void*>(geode::base::get() + 0x1fb0bc - ANDROID32_OFFSET), { 0x00, 0x00, 0xb4, 0x42 });
        //     Mod::get()->patch(reinterpret_cast<void*>(geode::base::get() + 0x1fb0c0 - ANDROID32_OFFSET), { 0x00, 0x00, 0x96, 0x43 });
        //     #endif
        // }
    //});
};