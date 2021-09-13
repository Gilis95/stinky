//
// Created by christian on 7/5/21.
//

#ifndef STINKY_ASSET_STORAGE_FACTORY_H
#define STINKY_ASSET_STORAGE_FACTORY_H

#include "asset/asset_storage.h"

namespace stinky {
    template<class _T_asset>
    struct asset_storage_factory {
        static asset_storage<_T_asset> storage;
    };
}

#endif //STINKY_ASSET_STORAGE_FACTORY_H
