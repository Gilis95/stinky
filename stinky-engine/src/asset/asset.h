//
// Created by christian on 7/1/21.
//

#ifndef STINKY_ASSET_H
#define STINKY_ASSET_H


namespace stinky {
    struct asset_metadata;
    class asset {
    public:
        asset() = default;

        virtual ~asset() = default;

        virtual bool load(const asset_metadata& assetMetadata) = 0;
    };
}

#endif //STINKY_ASSET_H
