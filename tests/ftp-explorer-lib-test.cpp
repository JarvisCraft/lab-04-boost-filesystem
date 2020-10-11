// Copyright 2020 Petr Portnov <gh@progrm-jarvis.ru>

#include <gtest/gtest.h>

#include <ftp-explorer-lib.hpp>

namespace ftp_explorer {

    TEST(FileInfo, from_file_name__valid) {
        EXPECT_EQ(
            FileInfo::from_filename("balance_12345678_20200709.txt"),
            (FileInfo{"balance", 12345678u, date::year_month_day{date::year{2020}, date::month{7u}, date::day{9u}}}));
        EXPECT_EQ(
            FileInfo::from_filename("action_14292387_20011231.txt"),
            (FileInfo{"action", 14292387u, date::year_month_day{date::year{2001}, date::month{12u}, date::day{31u}}}));
    }

    TEST(FileInfo, from_file_name__invalid) {
        EXPECT_FALSE(FileInfo::from_filename("random string"));
        EXPECT_FALSE(FileInfo::from_filename("random_file_name.txt"));
        EXPECT_FALSE(FileInfo::from_filename("balance_1234567_20200101.txt"));
        EXPECT_FALSE(FileInfo::from_filename("balance_12345678_2020111.txt"));
        EXPECT_FALSE(FileInfo::from_filename("balance_12345678_202011.txt"));
        EXPECT_FALSE(FileInfo::from_filename("balance_12345678_20201310.txt"));
        EXPECT_FALSE(FileInfo::from_filename("balance_12345678_20200010.txt"));
        EXPECT_FALSE(FileInfo::from_filename("balance_12345678_20201035.txt"));
        EXPECT_FALSE(FileInfo::from_filename("balance_12345678_20201000.txt"));
        EXPECT_FALSE(FileInfo::from_filename("action_14292387_20013112.txt"));
    }
} // namespace ftp_explorer
