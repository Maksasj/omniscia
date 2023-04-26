#ifndef _SAVE_H_
#define _SAVE_H_

namespace omniscia::core {
    struct SecretSaveData {
        std::string _title;
        std::string _description;
        std::string _icon;
        bool _unlocked;
    };

    struct Save {
        std::vector<SecretSaveData> _secrets;
    };
}

#endif