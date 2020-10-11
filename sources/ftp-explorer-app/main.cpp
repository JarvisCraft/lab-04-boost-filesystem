// Copyright 2020 Petr Portnov <gh@progrm-jarvis.ru>

#include <algorithm>
#include <ftp-explorer-lib/FtpData.hpp>
#include <ftp-explorer-lib/FtpFileInfo.hpp>
#include <iostream>

int main(int const argument_count, char* const arguments[]) {
    namespace fs = ::ftp_explorer::filesystem;

    fs::path path_to_ftp = argument_count >= 2 ? arguments[1] : fs::current_path();

    auto const data = ::ftp_explorer::FtpData::from_path(path_to_ftp);
    if (!data) {
        ::std::cerr << "Could not read data from path `" << path_to_ftp << "`" << ::std::endl;

        return 1;
    }

    struct Summary {
        ::std::size_t files;
        ::ftp_explorer::date::year_month_day lastDate;
    };

    ::std::unordered_map<::std::string, ::std::unordered_map<::std::uint32_t, Summary>> summaries;
    for (auto const& broker : data->brokers) {
        ::std::unordered_map<::std::uint32_t, Summary> broker_summaries;

        for (auto const& info : broker.second) {
            {
                auto iter = broker_summaries.find(info.id);
                if (iter == broker_summaries.end()) {
                    broker_summaries.insert(::std::make_pair(info.id, Summary{1, info.date}));
                } else {
                    auto& element = iter->second;
                    ++element.files;
                    if (element.lastDate < info.date) element.lastDate = info.date;
                }
            }

            ::std::cout << broker.first << ' ' << info.to_filename() << "\n";
        }

        summaries.insert(::std::make_pair(broker.first, broker_summaries));
    }
    ::std::cout << '\n';

    //@formatter:off
    for (auto const& broker_summary : summaries) for (auto const& summary : broker_summary.second) ::std::cout
                                                              << "broker:" << broker_summary.first
                                                              << " account:" << summary.first
                                                              << " files:" << summary.second.files
                                                              << " lastdate:" << summary.second.lastDate
                                                              << "\n";
    //@formatter:on
    ::std::cout.flush();
}
