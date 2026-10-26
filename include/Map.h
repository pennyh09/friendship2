#ifndef MAP_H
#define MAP_H
#include <cstddef>

#include <functional>

template <class K, class V>    
class CMap{
    public:
        using TEntityFunction = std::function<void(const K &, const V &)>;
        virtual std::size_t Size() const = 0;
        virtual bool Add(const K &key, V val) = 0;
        virtual bool Remove(const K &key) = 0;
        virtual bool Find(const K &key, V &val) const = 0;
        virtual void ForEach(TEntityFunction fun) = 0;
};

#endif