/**
 * @file own/db/sqlite/database.h
 * @brief The Database class for SQLite
 * @copyright Copyleft 2022 "unrealinsanity". All rights reversed.
 */

#pragma once

#include <external/sqlitecpp/all.h>
#include <own/db/base/database.h>
#include <own/db/sqlite/details.h>

namespace own::db::sqlite
{

/**
 * The Database class for SQLite
 *
 * @tparam Desc is the description of database connection
 * @note Database connections shall not be shared by multiple threads; keep them threads local
 *
 * @details
 * In Desc, two fields are mandatory: k_Name, k_FileName.
 * Desc::k_Name is the name of database to be registered to the database hub.
 * Desc::k_FileName is the filename of the database file.
 */
template <typename Desc>
requires(std::is_same_v<decltype(Desc::k_Name), const std::string_view>&& std::is_same_v<
         decltype(Desc::k_FileName), const std::string_view>) class Database final
    : public base::Database
{
   public:
    /// Constructor
    explicit Database() noexcept : base::Database{Desc::k_Name} {}

    /// The Name
    static constexpr std::string_view k_Name{Desc::k_Name};

   private:
    /** Do statement execution
     *
     * @param statement is the statement to execute
     */
    void doStatementExecution(const std::string_view statement) const noexcept final
    {
        SQLite::Database database{Desc::k_FileName.data(), SQLite::OPEN_READWRITE};
        SQLite::Statement statement_{database, statement.data()};
        statement_.exec();
    }

    /** Do statement execution
     *
     * @param result is passed in to store the query result
     * @param statement is the statement to execute
     */
    void doStatementExecution(std::vector<Values>& result,
                              const std::string_view statement) const noexcept final
    {
        SQLite::Database database{Desc::k_FileName.data(), SQLite::OPEN_READWRITE};
        SQLite::Statement statement_{database, statement.data()};
        while (statement_.executeStep())
        {
            auto resultStep = nlohmann::json::array();
            for (int index = 0; index < statement_.getColumnCount(); ++index)
            {
                auto value = details::getColumn(statement_, index);
                RUNTIME_ASSERT(std::as_const(value).is_primitive() && "Value is not primitive")
                resultStep.emplace_back(std::move(value));
            }
            result.emplace_back(std::move(resultStep));
        }
    }
};

}  // namespace own::db::sqlite
