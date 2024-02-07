#include <iostream>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <vector>
#include <list>

template<typename Container1, typename Container2>
bool checkIsEqual(const Container1& cont1, const Container2& cont2)
{
// проверка того, что типы элементов в контейнерах совпадают 
   ::testing::StaticAssertTypeEq<typename Container1::value_type,typename Container2::value_type>();
// проверка размеров контейнеров на равенство
   if(cont1.size() != cont2.size())
       return false;
// поэлементная проверка контейнеров
   return std::equal(cont1.begin(),cont1.end(), cont2.begin());
}

TEST(Ctest, testcase1)
{
   std::vector<int>  v1 = {1,2,3};
   std::list<int> v2 = {1,2,3};

   EXPECT_EQ(checkIsEqual(v1,v2),true);
}

int main(int argc, char *argv[])
{
   ::testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}
