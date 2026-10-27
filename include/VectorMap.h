#ifndef VECTORMAP_H
#define VECTORMAP_H

#include "Map.h"
#include <vector>
#include <utility>
#include <functional>

template <typename K, typename V>
class CVectorMap : public CMap<K, V> {
private:
    std::vector<std::vector<std::pair<K, V>>> buckets{16};
    std::size_t count = 0;
    void Rehash() {
    std::size_t newSize = buckets.size() * 2;

    std::vector<std::vector<std::pair<K, V>>> newBuckets(newSize);

    for (const auto& bucket : buckets) {
        for (const auto& entry : bucket) {
            std::size_t newIndex =
                std::hash<K>{}(entry.first) % newSize;

            newBuckets[newIndex].push_back(entry);
        }
    }

    buckets = std::move(newBuckets);
}

public:
    std::size_t Size() const override {
        return count;
    }

    bool Add(const K& key, V val) override {
        std::size_t index = std::hash<K>{}(key) % buckets.size();

         for (const auto& entry : buckets[index]) {
            if (entry.first == key) {
                return false;
            }
        }
        if ((count + 1.0) / buckets.size() > 0.75) {
        Rehash();
        index = std::hash<K>{}(key) % buckets.size();
}
        buckets[index].push_back({key, val});
        count++;

        return true;

        }
           



    bool Remove(const K& key) override {
        std::size_t index = std::hash<K>{}(key) % buckets.size();
        auto& bucket = buckets[index];

        for (std::size_t i = 0; i < bucket.size(); i++) {
            if (bucket[i].first == key) {
             bucket.erase(bucket.begin() + i);
                count--;
            return true;
        }
        }

        return false;
    }
        
    

    bool Find(const K& key, V& val) const override {
        std::size_t index = std::hash<K>{}(key) % buckets.size();
        for (const auto& entry : buckets[index]) {
            if (entry.first == key) {
                val = entry.second;
                return true;
            }       
        }
        return false;
    }


    void ForEach(typename CMap<K, V>::TEntityFunction fun) override {
        
      for (const auto& bucket : buckets) {
        for (const auto& entry : bucket) {
            fun(entry.first, entry.second);
        }
    }
    }
  
};

#endif