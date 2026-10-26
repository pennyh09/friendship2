#ifndef UNION_FIND_H
#define UNION_FIND_H

#include <cstddef>
#include <limits>

class CUnionFind{
    public:
        using TElementID = std::size_t;
        using TGroupID = std::size_t;
        static constexpr const TGroupID InvalidGroupID = std::numeric_limits<TGroupID>::max();

        virtual ~CUnionFind() = default;
        virtual std::size_t Size() const = 0;
        virtual std::size_t GroupCount() const = 0;
        virtual TElementID AddElement() = 0;
        virtual bool Union(TElementID a, TElementID b) = 0;
        virtual TGroupID Find(TElementID a) const = 0;
        virtual bool Connected(TElementID a, TElementID b) = 0;
};

#endif