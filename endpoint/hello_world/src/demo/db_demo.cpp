/**
 * @file demo/db_demo.cpp
 * @brief Demo of Pizza's database utility
 * @copyright Copyleft 2021-2022 "unrealinsanity". All rights reversed.
 */

#include <pizza/db/hub.h>
#include <pizza/db/sqlite/database.h>
#include <pizza/log/logger.h>

namespace
{
struct Db1
{
    static constexpr std::string_view k_Name{"db1"};
    static constexpr std::string_view k_FileName{"/tmp/db1.sqlite3"};
};

const auto databaseName = pizza::db::addDatabase<pizza::db::sqlite::Database<Db1>>();
}  // namespace

/** Before you execute this demo:
 *
 * $ sqlite3 /tmp/db1.sqlite3
 * > CREATE TABLE test_table (name, desc);
 */
int main() noexcept
{
    const pizza::log::Logger logger{"db_test"};
    auto& db1 = pizza::db::getDatabase("db1");

    constexpr std::string_view k_unrealInsanity{"UnrealInsanity"};
    constexpr std::string_view k_is_a_dev{"is a dev"};
    db1.execute({.insertInto = pizza::db::Table{"test_table"},
                 .columns = pizza::db::Columns{"name", "desc"},
                 .values = pizza::db::Values{k_unrealInsanity, k_is_a_dev}});

    const auto result = db1.execute({.select = pizza::db::Columns{"name", "desc"},
                                     .from = pizza::db::Table{"test_table"},
                                     .where = pizza::db::Condition{"name='{}'", k_unrealInsanity}});

    const pizza::db::Columns columns{"name", "desc"};
    logger.info("{}", fmt::join(*columns, ", "));
    for (const auto& values : result)
    {
        logger.info("{}", values.dump());
    }
}
