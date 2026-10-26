#include <gtest/gtest.h>
#include "UnionFind.h"
#include "UnionFindFactory.h"
#include <iostream>

template <typename T>
class UnionFindTest : public ::testing::Test {
    protected:
        std::unique_ptr<CUnionFind> DUnionFind = SUnionFindFactory<T>::Create();
};


using GDequeImplementations = ::testing::Types<CWeightedQuickUnion>;


TYPED_TEST_SUITE(UnionFindTest, GDequeImplementations);

TYPED_TEST(UnionFindTest, EmptyTest){
    EXPECT_EQ(this->DUnionFind->Size(),0);
}

TYPED_TEST(UnionFindTest, SimpleAddFind){
    EXPECT_EQ(this->DUnionFind->Size(),0);
    EXPECT_EQ(this->DUnionFind->AddElement(),0);
    EXPECT_EQ(this->DUnionFind->Size(),1);
    EXPECT_EQ(this->DUnionFind->Find(0),0);
}

TYPED_TEST(UnionFindTest, AddMultipleElements){
    EXPECT_EQ(this->DUnionFind->Size(), 0);
    EXPECT_EQ(this->DUnionFind->GroupCount(), 0);

    EXPECT_EQ(this->DUnionFind->AddElement(), 0);
    EXPECT_EQ(this->DUnionFind->AddElement(), 1);
    EXPECT_EQ(this->DUnionFind->AddElement(), 2);
    EXPECT_EQ(this->DUnionFind->AddElement(), 3);

    EXPECT_EQ(this->DUnionFind->Size(), 4);
    EXPECT_EQ(this->DUnionFind->GroupCount(), 4);
}

TYPED_TEST(UnionFindTest, EachElementInitiallyOwnGroup){
    for (std::size_t I = 0; I < 5; ++I){
        EXPECT_EQ(this->DUnionFind->AddElement(), I);
    }

    EXPECT_EQ(this->DUnionFind->Size(), 5);
    EXPECT_EQ(this->DUnionFind->GroupCount(), 5);

    for (std::size_t I = 0; I < 5; ++I){
        EXPECT_EQ(this->DUnionFind->Find(I), I);
        EXPECT_TRUE(this->DUnionFind->Connected(I, I));
    }
}

TYPED_TEST(UnionFindTest, SimpleUnion){
    this->DUnionFind->AddElement();
    this->DUnionFind->AddElement();

    EXPECT_EQ(this->DUnionFind->GroupCount(), 2);
    EXPECT_FALSE(this->DUnionFind->Connected(0, 1));

    EXPECT_TRUE(this->DUnionFind->Union(0, 1));

    EXPECT_EQ(this->DUnionFind->GroupCount(), 1);
    EXPECT_TRUE(this->DUnionFind->Connected(0, 1));
    EXPECT_TRUE(this->DUnionFind->Connected(1, 0));
}

TYPED_TEST(UnionFindTest, UnionReturnsFalseWhenAlreadyConnected){
    this->DUnionFind->AddElement();
    this->DUnionFind->AddElement();

    EXPECT_TRUE(this->DUnionFind->Union(0, 1));
    EXPECT_FALSE(this->DUnionFind->Union(0, 1));

    EXPECT_EQ(this->DUnionFind->GroupCount(), 1);
}

TYPED_TEST(UnionFindTest, UnionElementWithItself){
    this->DUnionFind->AddElement();

    EXPECT_FALSE(this->DUnionFind->Union(0, 0));

    EXPECT_EQ(this->DUnionFind->Size(), 1);
    EXPECT_EQ(this->DUnionFind->GroupCount(), 1);
    EXPECT_EQ(this->DUnionFind->Find(0), 0);
}

TYPED_TEST(UnionFindTest, TransitiveUnion){
    this->DUnionFind->AddElement();
    this->DUnionFind->AddElement();
    this->DUnionFind->AddElement();

    EXPECT_TRUE(this->DUnionFind->Union(0, 1));
    EXPECT_TRUE(this->DUnionFind->Union(1, 2));

    EXPECT_TRUE(this->DUnionFind->Connected(0, 1));
    EXPECT_TRUE(this->DUnionFind->Connected(1, 2));
    EXPECT_TRUE(this->DUnionFind->Connected(0, 2));

    EXPECT_EQ(this->DUnionFind->GroupCount(), 1);
}

TYPED_TEST(UnionFindTest, FindReturnsSameGroup){
    for (std::size_t I = 0; I < 4; ++I){
        this->DUnionFind->AddElement();
    }

    this->DUnionFind->Union(0, 1);
    this->DUnionFind->Union(2, 3);

    EXPECT_EQ(this->DUnionFind->Find(0), this->DUnionFind->Find(1));
    EXPECT_EQ(this->DUnionFind->Find(2), this->DUnionFind->Find(3));

    EXPECT_NE(this->DUnionFind->Find(0), this->DUnionFind->Find(2));
}

TYPED_TEST(UnionFindTest, MultipleGroups){
    for (std::size_t I = 0; I < 6; ++I){
        this->DUnionFind->AddElement();
    }

    EXPECT_EQ(this->DUnionFind->GroupCount(), 6);

    this->DUnionFind->Union(0, 1);
    this->DUnionFind->Union(2, 3);

    EXPECT_EQ(this->DUnionFind->GroupCount(), 4);

    this->DUnionFind->Union(4, 5);

    EXPECT_EQ(this->DUnionFind->GroupCount(), 3);

    EXPECT_TRUE(this->DUnionFind->Connected(0, 1));
    EXPECT_TRUE(this->DUnionFind->Connected(2, 3));
    EXPECT_TRUE(this->DUnionFind->Connected(4, 5));

    EXPECT_FALSE(this->DUnionFind->Connected(0, 2));
    EXPECT_FALSE(this->DUnionFind->Connected(0, 4));
    EXPECT_FALSE(this->DUnionFind->Connected(2, 4));
}

TYPED_TEST(UnionFindTest, MergeExistingGroups){
    for (std::size_t I = 0; I < 4; ++I){
        this->DUnionFind->AddElement();
    }

    this->DUnionFind->Union(0, 1);
    this->DUnionFind->Union(2, 3);

    EXPECT_EQ(this->DUnionFind->GroupCount(), 2);

    EXPECT_TRUE(this->DUnionFind->Union(1, 2));

    EXPECT_EQ(this->DUnionFind->GroupCount(), 1);

    EXPECT_TRUE(this->DUnionFind->Connected(0, 3));
    EXPECT_EQ(this->DUnionFind->Find(0), this->DUnionFind->Find(3));
}

TYPED_TEST(UnionFindTest, GroupCountAfterRepeatedUnions){
    for (std::size_t I = 0; I < 5; ++I){
        this->DUnionFind->AddElement();
    }

    EXPECT_EQ(this->DUnionFind->GroupCount(), 5);

    EXPECT_TRUE(this->DUnionFind->Union(0, 1));
    EXPECT_EQ(this->DUnionFind->GroupCount(), 4);

    EXPECT_TRUE(this->DUnionFind->Union(1, 2));
    EXPECT_EQ(this->DUnionFind->GroupCount(), 3);

    EXPECT_FALSE(this->DUnionFind->Union(0, 2));
    EXPECT_EQ(this->DUnionFind->GroupCount(), 3);

    EXPECT_TRUE(this->DUnionFind->Union(3, 4));
    EXPECT_EQ(this->DUnionFind->GroupCount(), 2);

    EXPECT_FALSE(this->DUnionFind->Union(4, 3));
    EXPECT_EQ(this->DUnionFind->GroupCount(), 2);

    EXPECT_TRUE(this->DUnionFind->Union(2, 4));
    EXPECT_EQ(this->DUnionFind->GroupCount(), 1);
}

TYPED_TEST(UnionFindTest, FindIsStable){
    for (std::size_t I = 0; I < 5; ++I){
        this->DUnionFind->AddElement();
    }

    auto Group0 = this->DUnionFind->Find(0);
    EXPECT_EQ(Group0,0);

    this->DUnionFind->Union(0, 1);
    this->DUnionFind->Union(1, 2);
    this->DUnionFind->Union(2, 3);
    this->DUnionFind->Union(3, 4);

    EXPECT_EQ(this->DUnionFind->Find(0),
              this->DUnionFind->Find(1));

    EXPECT_EQ(this->DUnionFind->Find(1),
              this->DUnionFind->Find(2));

    EXPECT_EQ(this->DUnionFind->Find(2),
              this->DUnionFind->Find(3));

    EXPECT_EQ(this->DUnionFind->Find(3),
              this->DUnionFind->Find(4));

    EXPECT_EQ(this->DUnionFind->GroupCount(), 1);
}

TYPED_TEST(UnionFindTest, SizeDoesNotChangeWhenUnioning){
    for (std::size_t I = 0; I < 5; ++I){
        this->DUnionFind->AddElement();
    }

    EXPECT_EQ(this->DUnionFind->Size(), 5);

    this->DUnionFind->Union(0, 1);
    this->DUnionFind->Union(1, 2);
    this->DUnionFind->Union(3, 4);
    this->DUnionFind->Union(2, 3);

    EXPECT_EQ(this->DUnionFind->Size(), 5);
}

TYPED_TEST(UnionFindTest, ASmallerRankUnion){
    for (std::size_t I = 0; I < 5; ++I){
        this->DUnionFind->AddElement();
    }

    EXPECT_EQ(this->DUnionFind->Size(), 5);

    this->DUnionFind->Union(1, 2);
    this->DUnionFind->Union(1, 3);
    this->DUnionFind->Union(1, 4);
    this->DUnionFind->Union(0, 1);
    EXPECT_EQ(this->DUnionFind->GroupCount(),1);
}

TYPED_TEST(UnionFindTest, InvalidFind){
    EXPECT_EQ(this->DUnionFind->Find(0), CUnionFind::InvalidGroupID);
}

TYPED_TEST(UnionFindTest, InvalidConnected){
    EXPECT_FALSE(this->DUnionFind->Connected(0,1));
}

TYPED_TEST(UnionFindTest, InvalidUnion){
    EXPECT_FALSE(this->DUnionFind->Union(0,1));
}