/**
 * @file own/database/postgresql/details.h
 * @brief PostgreSQL details.
 * @copyright Copyleft 2022 "unrealinsanity". All rights reversed.
 */

#ifndef DATABASE_POSTGRESQL_DETAILS_INCLUDED
#define DATABASE_POSTGRESQL_DETAILS_INCLUDED

#include <external/libpqxx/all.h>
#include <own/database/base/db.h>
#include <own/generic/types.h>
#include <own/logging/logging.h>

#include "oid.h"

/**
 * @namespace PostgreSQL details
 */
namespace own::database::postgresql::details
{

    /**
     * @name Using base `Database`
     */
    using own::database::base::Database;

    /** Connect to a PostgreSQL database
     *
     * @param connString is the postgres connection string (postgresql://)
     * @param logger is the logger
     */
    inline auto connectToDatabase(const std::string_view connString,
                                  const own::logging::Logger& logger)
    {
        logger.info(fmt::format("{} is connecting to {}", logger.getWhere(), connString));
        return std::make_unique<pqxx::connection>(connString.data());
    }

    /** Cast field to any
     *
     * @param field is the object
     * @ref https://github.com/olt/libpq/blob/master/oid/types.go
     */
    inline std::any castFieldToAny(const pqxx::field& field)
    {
        const auto oid = static_cast<OidEnum>(field.type());

        // only a subset of types are supported..
        // this is ugly.. this is too fucking ugly.. :(
        switch (oid)
        {
        case OidEnum::T_bool:
        case OidEnum::T_int2:
        case OidEnum::T_int4:
        case OidEnum::T_int8:
        case OidEnum::T__bool:
        case OidEnum::T__int2:
        case OidEnum::T__int4:
        case OidEnum::T__int8:
            // treat as generic integer
            return field.as<size_t>();
        case OidEnum::T_float4:
        case OidEnum::T_float8:
        case OidEnum::T__float4:
        case OidEnum::T__float8:
            // treat as generic float
            return field.as<double>();
        default:
            // type guess failed, treat everything as string
            return pqxx::to_string(field);
        }
    }

    /** Execute a PostgreSQL database query
     *
     * @param work contains the database connection object
     * @param query is the SQL statement to be executed
     */
    inline auto executePostgresQuery(pqxx::work& work, const std::string_view query)
        -> Database::Values
    {
        pqxx::result result { work.exec(query) };
        if (result.size() == 0)
        {
            return {};
        }

        Database::Values values;
        for (const auto row : result)
        {
            Database::Value value;
            std::transform(row.begin(), row.end(), std::back_inserter(value),
                           [&](const pqxx::field& field) { return castFieldToAny(field); });

            values.emplace_back(value);
        }

        return values;
    }

} // namespace own::database::postgresql::details

#endif
