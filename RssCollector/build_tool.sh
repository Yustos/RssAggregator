#!/bin/sh
g++ -O2 -c -g -I./libs/librss/include -DUSE_LIB_RSS -MMD -MP -MF "md5.o.d" -o md5.o md5.cpp
g++ -O2 -c -g -I./libs/librss/include -DUSE_LIB_RSS -MMD -MP -MF "str_utils.o.d" -o str_utils.o str_utils.cpp
g++ -O2 -c -g -I./libs/librss/include -DUSE_LIB_RSS -MMD -MP -MF "record.o.d" -o record.o record.cpp
g++ -O2 -c -g -I./libs/librss/include -DUSE_LIB_RSS -MMD -MP -MF "downloader.o.d" -o downloader.o downloader.cpp
g++ -O2 -c -g -I./libs/librss/include -I./libs/pg/include -DUSE_LIB_RSS -MMD -MP -MF "storage.o.d" -o storage.o storage.cpp
g++ -O2 -c -g -I./libs/librss/include -I./libs/pg/include -DUSE_LIB_RSS -MMD -MP -MF "main.o.d" -o main.o main.cpp
g++ -O2 -c -g -I./libs/librss/include -I./libs/pg/include -DUSE_LIB_RSS -MMD -MP -MF "collector.o.d" -o collector.o collector.cpp
g++ -O2 -c -g -I./libs/librss/include -DUSE_LIB_RSS -MMD -MP -MF "rss_parser.o.d" -o rss_parser.o rss_parser.cpp
g++ -O2 -c -g -I./libs/librss/include -DUSE_LIB_RSS -MMD -MP -MF "feed.o.d" -o feed.o feed.cpp
g++ -O2 -c -g -I./libs/librss/include -I./libs/json -DUSE_LIB_RSS -MMD -MP -MF "configuration.o.d" -o configuration.o configuration.cpp
g++ -O2 -o rsscollector collector.o feed.o main.o md5.o record.o downloader.o rss_parser.o storage.o str_utils.o configuration.o -L./libs/libiconv/libiconv-1.14/lib/.libs/ -L./libs/librss/bin -lpq -lcurl -liconv -lrss -ljson-c
