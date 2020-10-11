// Copyright 2020 Petr Portnov <gh@progrm-jarvis.ru>

#include <ftp-explorer-lib/FtpFileInfo.hpp>

namespace ftp_explorer {

    bool FtpFileInfo::operator!=(const FtpFileInfo& other) const {
        return type != other.type || id != other.id || date != other.date;
    }

    bool FtpFileInfo::operator==(const FtpFileInfo& other) const {
        return type == other.type && id == other.id && date == other.date;
    }

    ::std::optional<FtpFileInfo> FtpFileInfo::from_filename(::std::string const& filename) {
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
        return FtpFileInfo{filename_match[1], static_cast<::std::uint32_t>(::std::stoul(filename_match[2].str())),
                           date::year_month_day{year, month, day}};
    }

    ::std::optional<FtpFileInfo> FtpFileInfo::from_path(filesystem::path const& filepath) {
        if (!filesystem::is_regular_file(filepath)) return ::std::nullopt;

        return from_filename(filepath.filename().string());
    }

    ::std::string FtpFileInfo::to_filename() const {
        return type + '_' + ::std::to_string(id) + '_' + std::to_string((int)date.year())
               + std::to_string((unsigned int)date.month()) + std::to_string((unsigned int)date.day());
    }
} // namespace ftp_explorer

namespace std {

    size_t hash<::ftp_explorer::FtpFileInfo>::operator()(ftp_explorer::FtpFileInfo const& hashed) const {
        return ::std::hash<::std::string>{}(hashed.type) * 31 * 31 * 31 * 31
               + ::std::hash<::std::uint32_t>{}(hashed.id) * 31 * 31 * 31 + (int)hashed.date.year() * 31 * 31
               + (unsigned int)hashed.date.month() * 31 + (unsigned int)hashed.date.day() * 31;
    }
} // namespace std
