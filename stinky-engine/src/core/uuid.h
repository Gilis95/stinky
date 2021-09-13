//
// Created by christian on 6/30/21.
//

#ifndef STINKY_UUID_H
#define STINKY_UUID_H


namespace stinky {

    // "UUID" (universally unique identifier) or GUID is (usually) a 128-bit integer
    // used to "uniquely" identify information. In Hazel, even though we use the term
    // GUID and UUID, at the moment we're simply using a randomly generated 64-bit
    // integer, as the possibility of a clash is low enough for now.
    // This may change in the future.
    class uuid
    {
    public:
        uuid();
        explicit uuid(uint64_t uuid);
        uuid(const uuid& other);

        operator uint64_t () { return m_UUID; }
        operator uint64_t () const { return m_UUID; }
    private:
        uint64_t m_UUID;
    };

}

namespace std {

    template <>
    struct hash<stinky::uuid>
    {
        std::size_t operator()(const stinky::uuid& uuid) const
        {
            return hash<uint64_t>()((uint64_t)uuid);
        }
    };
}
#endif //STINKY_UUID_H
