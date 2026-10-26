#include <gtest/gtest.h>
#include "Map.h"
#include "MapFactory.h"

#include <algorithm>
template <typename T>
class MapTest : public ::testing::Test {
    protected:
        std::unique_ptr<CMap<int,int>> DMap = SMapFactory<T>::Create();
};


using GMapImplementations = ::testing::Types<YOUR_IMPLEMENTATION<int,int>>;


TYPED_TEST_SUITE(MapTest, GMapImplementations);

TYPED_TEST(MapTest, EmptyTest) {
    EXPECT_EQ(this->DMap->Size(),0);
}

TYPED_TEST(MapTest, SimpleAddFind){
    int Value;
    EXPECT_EQ(this->DMap->Size(),0);
    EXPECT_FALSE(this->DMap->Find(7,Value));
    EXPECT_TRUE(this->DMap->Add(7,11));
    EXPECT_EQ(this->DMap->Size(),1);
    EXPECT_TRUE(this->DMap->Find(7,Value));
    EXPECT_EQ(Value,11);
}

TYPED_TEST(MapTest, AddMultipleFind){
    int Value;

    EXPECT_TRUE(this->DMap->Add(5,50));
    EXPECT_TRUE(this->DMap->Add(2,20));
    EXPECT_TRUE(this->DMap->Add(8,80));
    EXPECT_TRUE(this->DMap->Add(1,10));
    EXPECT_TRUE(this->DMap->Add(3,30));

    EXPECT_EQ(this->DMap->Size(),5);

    EXPECT_TRUE(this->DMap->Find(1,Value));
    EXPECT_EQ(Value,10);

    EXPECT_TRUE(this->DMap->Find(2,Value));
    EXPECT_EQ(Value,20);

    EXPECT_TRUE(this->DMap->Find(3,Value));
    EXPECT_EQ(Value,30);

    EXPECT_TRUE(this->DMap->Find(5,Value));
    EXPECT_EQ(Value,50);

    EXPECT_TRUE(this->DMap->Find(8,Value));
    EXPECT_EQ(Value,80);
}

TYPED_TEST(MapTest, DuplicateAdd){
    int Value;
    EXPECT_TRUE(this->DMap->Add(1,11));
    EXPECT_TRUE(this->DMap->Add(2,11));
    EXPECT_TRUE(this->DMap->Add(9,11));
    EXPECT_TRUE(this->DMap->Add(12,11));
    EXPECT_TRUE(this->DMap->Add(8,11));
    EXPECT_TRUE(this->DMap->Add(7,11));
    EXPECT_FALSE(this->DMap->Add(7,22));

    EXPECT_EQ(this->DMap->Size(),6);

    EXPECT_TRUE(this->DMap->Find(7,Value));
    EXPECT_EQ(Value,11);
}

TYPED_TEST(MapTest, FindMissing){
    int Value;

    EXPECT_TRUE(this->DMap->Add(10,100));
    EXPECT_TRUE(this->DMap->Add(5,50));
    EXPECT_TRUE(this->DMap->Add(15,150));

    EXPECT_FALSE(this->DMap->Find(1,Value));
    EXPECT_FALSE(this->DMap->Find(7,Value));
    EXPECT_FALSE(this->DMap->Find(12,Value));
    EXPECT_FALSE(this->DMap->Find(20,Value));

    EXPECT_EQ(this->DMap->Size(),3);
}

TYPED_TEST(MapTest, NegativeKeys){
    int Value;

    EXPECT_TRUE(this->DMap->Add(-10,100));
    EXPECT_TRUE(this->DMap->Add(-20,200));
    EXPECT_TRUE(this->DMap->Add(-5,50));
    EXPECT_TRUE(this->DMap->Add(0,0));
    EXPECT_TRUE(this->DMap->Add(10,-100));

    EXPECT_EQ(this->DMap->Size(),5);

    EXPECT_TRUE(this->DMap->Find(-20,Value));
    EXPECT_EQ(Value,200);

    EXPECT_TRUE(this->DMap->Find(-10,Value));
    EXPECT_EQ(Value,100);

    EXPECT_TRUE(this->DMap->Find(-5,Value));
    EXPECT_EQ(Value,50);

    EXPECT_TRUE(this->DMap->Find(0,Value));
    EXPECT_EQ(Value,0);

    EXPECT_TRUE(this->DMap->Find(10,Value));
    EXPECT_EQ(Value,-100);
}

TYPED_TEST(MapTest, IncreasingKeys){
    int Value;

    for(int I = 0; I < 100; I++){
        EXPECT_TRUE(this->DMap->Add(I,I * 10));
    }

    EXPECT_EQ(this->DMap->Size(),100);

    for(int I = 0; I < 100; I++){
        EXPECT_TRUE(this->DMap->Find(I,Value));
        EXPECT_EQ(Value,I * 10);
    }
}

TYPED_TEST(MapTest, DecreasingKeys){
    int Value;

    for(int I = 99; I >= 0; I--){
        EXPECT_TRUE(this->DMap->Add(I,I * 10));
    }

    EXPECT_EQ(this->DMap->Size(),100);

    for(int I = 0; I < 100; I++){
        EXPECT_TRUE(this->DMap->Find(I,Value));
        EXPECT_EQ(Value,I * 10);
    }
}

TYPED_TEST(MapTest, MixedInsertion){
    int Value;

    int Keys[] = {
        50, 25, 75, 10, 30, 60, 90,
        5, 15, 27, 35, 55, 65, 85, 95
    };

    for(int Key : Keys){
        EXPECT_TRUE(this->DMap->Add(Key,Key * 2));
    }

    EXPECT_EQ(this->DMap->Size(),15);

    for(int Key : Keys){
        EXPECT_TRUE(this->DMap->Find(Key,Value));
        EXPECT_EQ(Value,Key * 2);
    }
}

TYPED_TEST(MapTest, SizeAfterEachAdd){
    for(int I = 0; I < 50; I++){
        EXPECT_TRUE(this->DMap->Add(I,I));
        EXPECT_EQ(this->DMap->Size(),
                  static_cast<std::size_t>(I + 1));
    }
}

TYPED_TEST(MapTest, FindDoesNotChangeSize){
    int Value;

    EXPECT_TRUE(this->DMap->Add(10,100));
    EXPECT_TRUE(this->DMap->Add(20,200));
    EXPECT_TRUE(this->DMap->Add(30,300));

    EXPECT_EQ(this->DMap->Size(),3);

    EXPECT_TRUE(this->DMap->Find(20,Value));
    EXPECT_EQ(this->DMap->Size(),3);

    EXPECT_FALSE(this->DMap->Find(99,Value));
    EXPECT_EQ(this->DMap->Size(),3);
}

TYPED_TEST(MapTest, RemoveEmpty){
    EXPECT_FALSE(this->DMap->Remove(7));
    EXPECT_EQ(this->DMap->Size(),0);
}

TYPED_TEST(MapTest, RemoveMissing){
    int Value;

    EXPECT_TRUE(this->DMap->Add(10,100));
    EXPECT_TRUE(this->DMap->Add(20,200));
    EXPECT_TRUE(this->DMap->Add(30,300));

    EXPECT_FALSE(this->DMap->Remove(15));

    EXPECT_EQ(this->DMap->Size(),3);

    EXPECT_TRUE(this->DMap->Find(10,Value));
    EXPECT_TRUE(this->DMap->Find(20,Value));
    EXPECT_TRUE(this->DMap->Find(30,Value));
}

TYPED_TEST(MapTest, RemoveOnlyNode){
    int Value;

    EXPECT_TRUE(this->DMap->Add(10,100));
    EXPECT_EQ(this->DMap->Size(),1);

    EXPECT_TRUE(this->DMap->Remove(10));

    EXPECT_EQ(this->DMap->Size(),0);
    EXPECT_FALSE(this->DMap->Find(10,Value));
}

TYPED_TEST(MapTest, RemoveLeaf){
    int Value;

    EXPECT_TRUE(this->DMap->Add(10,100));
    EXPECT_TRUE(this->DMap->Add(5,50));
    EXPECT_TRUE(this->DMap->Add(15,150));

    EXPECT_TRUE(this->DMap->Remove(5));

    EXPECT_EQ(this->DMap->Size(),2);
    EXPECT_FALSE(this->DMap->Find(5,Value));

    EXPECT_TRUE(this->DMap->Find(10,Value));
    EXPECT_EQ(Value,100);

    EXPECT_TRUE(this->DMap->Find(15,Value));
    EXPECT_EQ(Value,150);
    EXPECT_TRUE(this->DMap->Remove(10));
    EXPECT_TRUE(this->DMap->Remove(15));
    EXPECT_EQ(this->DMap->Size(),0);

    EXPECT_TRUE(this->DMap->Add(10, 10));
    EXPECT_TRUE(this->DMap->Add(5, 5));
    EXPECT_TRUE(this->DMap->Add(15, 15));
    EXPECT_TRUE(this->DMap->Add(2, 2));
    EXPECT_TRUE(this->DMap->Add(7, 7));
    EXPECT_TRUE(this->DMap->Add(12, 12));
    EXPECT_TRUE(this->DMap->Add(20, 20));
    EXPECT_TRUE(this->DMap->Add(1, 1));
    EXPECT_TRUE(this->DMap->Add(3, 3));

    EXPECT_TRUE(this->DMap->Remove(20));

    EXPECT_EQ(this->DMap->Size(), 8);
}

TYPED_TEST(MapTest, RemoveRoot){
    int Value;

    EXPECT_TRUE(this->DMap->Add(10,100));
    EXPECT_TRUE(this->DMap->Add(5,50));
    EXPECT_TRUE(this->DMap->Add(15,150));

    EXPECT_TRUE(this->DMap->Remove(10));

    EXPECT_EQ(this->DMap->Size(),2);
    EXPECT_FALSE(this->DMap->Find(10,Value));

    EXPECT_TRUE(this->DMap->Find(5,Value));
    EXPECT_EQ(Value,50);

    EXPECT_TRUE(this->DMap->Find(15,Value));
    EXPECT_EQ(Value,150);
}

TYPED_TEST(MapTest, RemoveTwoChildren){
    int Value;

    EXPECT_TRUE(this->DMap->Add(20,20));
    EXPECT_TRUE(this->DMap->Add(10,10));
    EXPECT_TRUE(this->DMap->Add(30,30));
    EXPECT_TRUE(this->DMap->Add(5,5));
    EXPECT_TRUE(this->DMap->Add(15,15));
    EXPECT_TRUE(this->DMap->Add(25,25));
    EXPECT_TRUE(this->DMap->Add(35,35));
    EXPECT_TRUE(this->DMap->Add(22,22));
    EXPECT_TRUE(this->DMap->Add(27,27));
    EXPECT_TRUE(this->DMap->Remove(20));

    EXPECT_EQ(this->DMap->Size(),8);

    EXPECT_FALSE(this->DMap->Find(20, Value));
    EXPECT_TRUE(this->DMap->Find(10, Value));
    EXPECT_TRUE(this->DMap->Find(30, Value));
    EXPECT_TRUE(this->DMap->Find(5, Value));
    EXPECT_TRUE(this->DMap->Find(15, Value));
    EXPECT_TRUE(this->DMap->Find(25, Value));
    EXPECT_TRUE(this->DMap->Find(35, Value));
    EXPECT_TRUE(this->DMap->Find(22, Value));
    EXPECT_TRUE(this->DMap->Find(27, Value));
}

TYPED_TEST(MapTest, RemoveEverything){
    int Value;

    for(int I = 0; I < 100; I++){
        EXPECT_TRUE(this->DMap->Add(I,I * 10));
    }

    EXPECT_EQ(this->DMap->Size(),100);

    for(int I = 0; I < 100; I++){
        EXPECT_TRUE(this->DMap->Remove(I));
        EXPECT_EQ(this->DMap->Size(),
                  static_cast<std::size_t>(99 - I));
        EXPECT_FALSE(this->DMap->Find(I,Value));
    }

    EXPECT_EQ(this->DMap->Size(),0);
}

TYPED_TEST(MapTest, RemoveEverythingReverse){
    int Value;

    for(int I = 0; I < 100; I++){
        EXPECT_TRUE(this->DMap->Add(I,I));
    }

    for(int I = 99; I >= 0; I--){
        EXPECT_TRUE(this->DMap->Remove(I));
        EXPECT_FALSE(this->DMap->Find(I,Value));
        EXPECT_EQ(this->DMap->Size(),
                  static_cast<std::size_t>(I));
    }

    EXPECT_EQ(this->DMap->Size(),0);
}

TYPED_TEST(MapTest, ForEachTest){
    for(int I = 0; I < 100; I++){
        EXPECT_TRUE(this->DMap->Add(I,I * 3));
    }
    EXPECT_EQ(this->DMap->Size(),100);
    std::vector<int> Keys;
    std::vector<int> Values;
    this->DMap->ForEach([&Keys,&Values](int k, int v){
        Keys.push_back(k);
        Values.push_back(v);
    });
    std::sort(Keys.begin(), Keys.end());
    std::sort(Values.begin(), Values.end());
    for(int I = 0; I < 100; I++){
        EXPECT_EQ(Keys[I],I);
        EXPECT_EQ(Values[I],I*3);
    }
}