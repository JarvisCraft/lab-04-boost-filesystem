// Copyright 2020 Petr Portnov <gh@progrm-jarvis.ru>

#include "ftp-explorer-lib/FtpData.hpp"

namespace ftp_explorer {

    bool FtpData::operator==(FtpData const& other) const {
        return brokers == other.brokers;
    }

    bool FtpData::operator!=(FtpData const& other) const {
        return brokers != other.brokers;
    }

    static ::std::unordered_set<FtpFileInfo> parse_directory_(filesystem::path const& broker_path) {
        // the check should actually be done by caller
        assert(filesystem::is_directory(broker_path) && "`broker_path` should be a directory");

        ::std::unordered_set<FtpFileInfo> broker_entries(32);
        {
            filesystem::path entry_path; // reused
            for (auto const& entry : filesystem::directory_iterator(broker_path)) {
                if (filesystem::is_regular_file(entry))
                    entry_path = entry.path();
                else if (filesystem::is_symlink(entry))
                    entry_path = filesystem::read_symlink(entry.path());

                auto const ftp_file_info = FtpFileInfo::from_path(entry_path);
                if (ftp_file_info) broker_entries.insert(*ftp_file_info);
            }
        }

        return broker_entries;
    }

    ::std::optional<FtpData> FtpData::from_path(filesystem::path const& directory) {
        if (!filesystem::is_directory(directory)) return ::std::nullopt;

        BrokersMap brokers;
        for (auto const& entry : filesystem::directory_iterator(directory)) {
            if (!filesystem::is_directory(entry)) continue;

            auto const broker_path = entry.path();
            auto const broker_name = broker_path.filename().string();
            if (PERMITTED_BROKERS.find(broker_name) == PERMITTED_BROKERS.end()) continue;

            brokers.insert(::std::make_pair<>(broker_name, parse_directory_(broker_path)));
        }

        return FtpData{brokers};
    }
}
