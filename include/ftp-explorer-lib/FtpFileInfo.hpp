// Copyright 2020 Petr Portnov <gh@progrm-jarvis.ru>

#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_

#include <date/date.h>

#include <boost/filesystem.hpp>
#include <cstddef>
#include <optional>
#include <regex>
#include <string>
#include <unordered_map>
#include <unordered_set>

namespace ftp_explorer {

    namespace filesystem = ::boost::filesystem;
    namespace date = ::date;

    static const ::std::regex FILENAME_REGEX("^([a-z\\d]+)_(\\d{8})_(\\d{8})\\.txt$");

    struct FtpFileInfo {
        ::std::string type;
        ::std::uint32_t id;
        date::year_month_day date;

        [[nodiscard]] bool operator==(FtpFileInfo const& other) const;

        [[nodiscard]] bool operator!=(FtpFileInfo const& other) const;

        [[nodiscard]] ::std::string to_filename() const;

        [[nodiscard]] static ::std::optional<FtpFileInfo> from_filename(::std::string const& filename);

        [[nodiscard]] static ::std::optional<FtpFileInfo> from_path(filesystem::path const& filepath);
    };
} // namespace ftp_explorer

namespace std {
    template <>
    struct hash<::ftp_explorer::FtpFileInfo> {
        size_t operator()(::ftp_explorer::FtpFileInfo const& hashed) const;
    };
} // namespace std

#endif // INCLUDE_HEADER_HPP_
