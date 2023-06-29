#ifndef _OMNISCIA_EDITOR_TILE_GROUP_SORTER_SYSTEM_H_
#define _OMNISCIA_EDITOR_TILE_GROUP_SORTER_SYSTEM_H_

#include <iostream>
#include <string>
#include <algorithm>

#include "tilegroup_data_ref.h"

#include "../gfx.h"
#include "../types.h"

namespace omniscia_editor::windows {
    using namespace omniscia::core;

    struct TileGroupSorter {
        virtual void sort(std::vector<TileGroupData>& tileGroups, const bool& reverseSort) {}
    };

    struct AlphabeticalTileGroupSorter : public TileGroupSorter {
        void sort(std::vector<TileGroupData>& tileGroups, const bool& reverseSort) override {
            std::sort(tileGroups.begin(), tileGroups.end(), [&](const TileGroupData& a, const TileGroupData& b) {
                if(reverseSort)
                    return a._name > b._name;

                return a._name < b._name;
            });
        }

        static AlphabeticalTileGroupSorter& get_instance() {
            static AlphabeticalTileGroupSorter sorter;
            return sorter;
        }
    };

    struct TileCountTileGroupSorter : public TileGroupSorter {
        void sort(std::vector<TileGroupData>& tileGroups, const bool& reverseSort) override {
            std::sort(tileGroups.begin(), tileGroups.end(), [&](const TileGroupData& a, const TileGroupData& b) {
                if(reverseSort)
                    return a._tiles.size() > b._tiles.size();

                return a._tiles.size() < b._tiles.size();
            });
        } 

        static TileCountTileGroupSorter& get_instance() {
            static TileCountTileGroupSorter sorter;
            return sorter;
        }
    };

    struct CollisionBoxCountTileGroupSorter : public TileGroupSorter {
        void sort(std::vector<TileGroupData>& tileGroups, const bool& reverseSort) override {
            std::sort(tileGroups.begin(), tileGroups.end(), [&](const TileGroupData& a, const TileGroupData& b) {
                if(reverseSort)
                    return a._collisionBoxes.size() > b._collisionBoxes.size();

                return a._collisionBoxes.size() < b._collisionBoxes.size();
            });
        } 

        static CollisionBoxCountTileGroupSorter& get_instance() {
            static CollisionBoxCountTileGroupSorter sorter;
            return sorter;
        }
    };

    struct TileGroupSorterInstance {
        std::string _label;
        TileGroupSorter* _sorter;
    };
}

#endif
