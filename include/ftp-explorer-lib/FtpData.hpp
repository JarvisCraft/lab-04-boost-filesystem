// Copyright 2020 Petr Portnov <gh@progrm-jarvis.ru>

#ifndef INCLUDE_FTP_EXPLORER_LIB_FTPDATA_HPP_
#define INCLUDE_FTP_EXPLORER_LIB_FTPDATA_HPP_

#include <string>
#include <unordered_map>
#include <unordered_set>

#include "FtpFileInfo.hpp"

namespace ftp_explorer {

    struct FtpData {
        typedef ::std::unordered_map<::std::string, ::std::unordered_set<FtpFileInfo>> BrokersMap;

        static inline const ::std::unordered_set<::std::string> PERMITTED_BROKERS{"ib", "bcs", "otkritie"};

        BrokersMap brokers;

        [[nodiscard]] bool operator==(FtpData const& other) const;

        [[nodiscard]] bool operator!=(FtpData const& other) const;

        [[nodiscard]] static ::std::optional<FtpData> from_path(filesystem::path const& directory);
    };
} // namespace ftp_explorer

#endif // INCLUDE_FTP_EXPLORER_LIB_FTPDATA_HPP_
