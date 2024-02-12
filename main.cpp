#include <string>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

class IDBConection
{
public:
   IDBConection() = default;
   virtual ~IDBConection() = default;
   virtual bool open() = 0;
   virtual bool close() = 0;
   virtual const char* execQuery(std::string& query) = 0;
};

class DBConnection : public IDBConection
{
public:
   DBConnection() = default;
   ~DBConnection() = default;
   bool open() override
   {
      return true;
   }
   bool close() override
   {
      return true;
   }
   const char* execQuery(std::string& query) override
   {
      if(query.empty())
      {
         query = "Error: empty query!";
      }
      else
      {
         query += '_' + std::to_string(++counter_);
      }
      return query.c_str();
   }
private:
   size_t counter_{0}; 
};

class MockDBConnection : public IDBConection
{
public:
   MOCK_METHOD(bool, open, (), (override));
   MOCK_METHOD(bool, close, (), (override));
   MOCK_METHOD(const char*, execQuery, (std::string&), (override));
};

class ClassThatUseDb
{
public:
   ClassThatUseDb(std::shared_ptr<IDBConection>&& connection) : connection_ { connection } {}
   ~ClassThatUseDb() = default;
   bool openConnection()
   {
      return connection_->open();
   }
   const char* useConnection(std::string& query)
   {
      return connection_->execQuery(query);
   }
   bool closeConnection()
   {
      return connection_->close();
   }
private:
   std::shared_ptr<IDBConection> connection_;
};

TEST(ConnectionTest, open_close)
{
   auto connection = std::make_shared<MockDBConnection>();
   EXPECT_CALL(*connection, open).WillOnce(::testing::Return(true));
   EXPECT_CALL(*connection, close).WillOnce(::testing::Return(true));
   ClassThatUseDb dbUser(connection);
   dbUser.openConnection();
   dbUser.closeConnection();
}

TEST(ConnectionTest, query)
{
   auto connection = std::make_shared<DBConnection>();
   ClassThatUseDb dbUser(connection);
   std::string q1{"query"};
   std::string q2;
   ASSERT_STREQ(dbUser.useConnection(q1), "query_1");
   ASSERT_STREQ(dbUser.useConnection(q2), "Error: empty query!");
}

int main(int argc, char* argv[])
{
   ::testing::InitGoogleTest(&argc, argv);
   ::testing::InitGoogleMock(&argc, argv);
   return RUN_ALL_TESTS();
}
