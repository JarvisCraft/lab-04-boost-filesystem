// Copyright 2020 Petr Portnov <gh@progrm-jarvis.ru>

#include <gtest/gtest.h>

#include <ftp-explorer-lib/FtpFileInfo.hpp>

namespace ftp_explorer {

    TEST(FtpFileInfo, from_file_name__valid) {
        EXPECT_EQ(FtpFileInfo::from_filename("balance_12345678_20200709.txt"),
                  (FtpFileInfo{"balance", 12345678u,
                               date::year_month_day{date::year{2020}, date::month{7u}, date::day{9u}}}));
        EXPECT_EQ(FtpFileInfo::from_filename("action_14292387_20011231.txt"),
                  (FtpFileInfo{"action", 14292387u,
                               date::year_month_day{date::year{2001}, date::month{12u}, date::day{31u}}}));
    }

    TEST(FtpFileInfo, from_file_name__invalid) {
        EXPECT_FALSE(FtpFileInfo::from_filename("random string"));
        EXPECT_FALSE(FtpFileInfo::from_filename("random_file_name.txt"));
        EXPECT_FALSE(FtpFileInfo::from_filename("balance_1234567_20200101.txt"));
        EXPECT_FALSE(FtpFileInfo::from_filename("balance_12345678_2020111.txt"));
        EXPECT_FALSE(FtpFileInfo::from_filename("balance_12345678_202011.txt"));
        EXPECT_FALSE(FtpFileInfo::from_filename("balance_12345678_20201310.txt"));
        EXPECT_FALSE(FtpFileInfo::from_filename("balance_12345678_20200010.txt"));
        EXPECT_FALSE(FtpFileInfo::from_filename("balance_12345678_20201035.txt"));
        EXPECT_FALSE(FtpFileInfo::from_filename("balance_12345678_20201000.txt"));
        EXPECT_FALSE(FtpFileInfo::from_filename("action_14292387_20013112.txt"));
    }

    TEST(FtpFileInfo, as_filename) {
        EXPECT_EQ(
            "balance_88005553_20071103.txt",
            (FtpFileInfo{"balance", 88005553u, date::year_month_day{date::year{2007}, date::month{11u}, date::day{3u}}}
                 .to_filename()));
        EXPECT_EQ(
            "magic_19283746_19961008.txt",
            (FtpFileInfo{"magic", 19283746u, date::year_month_day{date::year{1996}, date::month{10u}, date::day{8u}}}
                 .to_filename()));
    }
} // namespace ftp_explorer
