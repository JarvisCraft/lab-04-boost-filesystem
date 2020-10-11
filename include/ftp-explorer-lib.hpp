// Copyright 2020 Petr Portnov <gh@progrm-jarvis.ru>

#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_

#include <date/date.h>

#include <boost/filesystem.hpp>
#include <cstddef>
#include <optional>
#include <regex>
#include <string>

namespace ftp_explorer {

    namespace filesystem = ::boost::filesystem;
    namespace date = ::date;

    static const ::std::regex FILENAME_REGEX("^([a-z\\d]+)_(\\d{8})_(\\d{8})\\.txt$");

    struct FileInfo {
        ::std::string type;
        ::std::uint32_t id;
        date::year_month_day date;

        bool operator==(FileInfo const& other) const;

        bool operator!=(FileInfo const& other) const;

        [[nodiscard]] ::std::string to_filename() const;

        static ::std::optional<FileInfo> from_filename(::std::string const& filename);

        static ::std::optional<FileInfo> from_path(filesystem::path const& filepath);
    };
} // namespace ftp_explorer

#endif // INCLUDE_HEADER_HPP_
