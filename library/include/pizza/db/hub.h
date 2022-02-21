/**
 * @file pizza/db/hub.h
 * @brief The Database Hub
 * @copyright Copyleft 2022 "unrealinsanity". All rights reversed.
 */

#pragma once

#include <pizza/db/base/database.h>
#include <pizza/db/concepts.h>
#include <pizza/log/logger.h>
#include <pizza/support.h>

namespace pizza::db
{

/**
 * The Database Hub
 *
 * @brief
 * The Database Hub is where all database instances get stored and registered, and each instance is
 * given a name to refer to.
 *
 * @note
 * Since it's very common to have concurrent database access in production code, database instances
 * shall NOT maintain any mutable states, and database connections shall be established per query
 * (aka be kept threads local)
 */
class Hub final
{
    SINGLETON_CLASS(Hub)

   public:
    /** Add database instance to the hub
     *
     * @tparam Database is the database class
     * @returns the name of database added
     */
    template <PizzaDatabase Database>
    [[nodiscard]] std::string_view addDatabase() noexcept
    {
        m_log.info("Registering {} to the database hub", Database::k_Name);

        const auto [_, inserted] = m_self.emplace(Database::k_Name, std::make_unique<Database>());
        RUNTIME_ASSERT(inserted && "Name of database is overlapping with another instance")
        return Database::k_Name;
    }

    /** Get database with given name
     *
     * @param name is the name of database instance
     * @returns reference to the wanted database instance
     */
    [[nodiscard]] base::Database& getDatabase(const std::string_view name) const noexcept
    {
        return *m_self.at(name);
    }

   private:
    /// The Hub itself
    std::unordered_map<std::string_view, std::unique_ptr<base::Database>> m_self;

    /// The Logger
    const pizza::log::Logger m_log{"db:hub"};
};

/** Add database instance to the hub
 *
 * @tparam Database is the database class
 * @returns the name of database added
 */
template <PizzaDatabase Database>
[[nodiscard]] std::string_view addDatabase() noexcept
{
    return Hub::getHub().addDatabase<Database>();
}

/** Get database with given name
 *
 * @param name is the name of database instance
 * @returns reference to the wanted database instance
 */
[[nodiscard]] inline base::Database& getDatabase(const std::string_view name) noexcept
{
    return Hub::getHub().getDatabase(name);
}

}  // namespace pizza::db
