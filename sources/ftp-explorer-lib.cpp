// Copyright 2020 Petr Portnov <gh@progrm-jarvis.ru>

#include <ftp-explorer-lib.hpp>

namespace ftp_explorer {

    bool FileInfo::operator!=(const FileInfo& other) const {
        return type != other.type || id != other.id || date != other.date;
    }

    bool FileInfo::operator==(const FileInfo& other) const {
        return type == other.type && id == other.id && date == other.date;
    }

    ::std::optional<FileInfo> FileInfo::from_filename(::std::string const& filename) {
        ::std::smatch filename_match;
        if (!(::std::regex_search(filename, filename_match, FILENAME_REGEX))) return ::std::nullopt;

        auto const& date = filename_match[3].str();

        auto const year = date::year{::std::stoi(date.substr(0, 4))};
        if (!year.ok()) return ::std::nullopt;
        auto const month = date::month{static_cast<unsigned int>(::std::stoi(date.substr(4, 2)))};
        if (!month.ok()) return ::std::nullopt;
        auto const day = date::day{static_cast<unsigned int>(::std::stoi(date.substr(6, 2)))};
        if (!day.ok()) return ::std::nullopt;

        // note: year validation is not required
        return FileInfo{filename_match[1], static_cast<::std::uint32_t>(::std::stoul(filename_match[2].str())),
                        date::year_month_day{year, month, day}};
    }

    ::std::optional<FileInfo> FileInfo::from_path(filesystem::path const& filepath) {
        if (!filesystem::is_regular_file(filepath)) return ::std::nullopt;

        return from_filename(filepath.filename().string());
    }
} // namespace ftp_explorer
