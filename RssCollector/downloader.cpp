#include "downloader.hpp"
#include "str_utils.hpp"
#include <sys/stat.h>
#include <utility>
#include <string>
#include <curl/curl.h>
#include <curl/easy.h>
#include <iconv.h>

#include <iostream>
#include <stdlib.h>

namespace downloader {

	CURL *curl;

	size_t write_data_string(char *ptr, size_t size, size_t nmemb, std::string *stream) {
		int result = 0;
		if (stream != NULL) {
			stream->append(ptr, size * nmemb);
			result = size * nmemb;
		}
		return result;
	}

	std::string iconv_recode(std::string from, std::string to, std::string text)
	{
		iconv_t cnv = iconv_open(to.c_str(), from.c_str());
		if (cnv == (iconv_t) - 1)
		{
			iconv_close(cnv);
			std::cerr << "recode failure";
		}
		char *outbuf;
		if ((outbuf = (char *) malloc(text.length()*2 + 1)) == NULL)
		{
			iconv_close(cnv);
			std::cerr << "malloc for recode failure";
		}
		char *ip = (char *) text.c_str(), *op = outbuf;
		size_t icount = text.length(), ocount = text.length()*2;

		std::string ret();
		if (iconv(cnv, &ip, &icount, &op, &ocount) != (size_t) - 1)
		{
			outbuf[text.length()*2 - ocount] = '\0';
			text = outbuf;
		}
		else
		{
			text = "";
		}

		free(outbuf);
		iconv_close(cnv);
		return text;
	}

	std::string recode_charset(std::string text, char* content_type)
	{
		//TODO: check charset attribute in xml
		std::string tmp(content_type);
		std::string::size_type pos = tmp.find("charset");
		if (pos != std::string::npos)
		{
			pos = tmp.find("=", pos);
			if (pos != std::string::npos)
			{
				std::string charset = tmp.substr(pos+1);
				if (charset.compare("utf-8") != 0)
				{
					return iconv_recode(charset, std::string("utf-8"), text);
				}
			}
		}
		return text;
	}

	std::string download(const std::string &url) {
		if (!curl) {
				curl = curl_easy_init();
		}

		std::string mi;
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &mi);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data_string);
		curl_easy_perform(curl);

		long http_code;
		curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
		if (http_code != 200)
		{
			std::cout << "http code:" << http_code << std::endl;
			throw "Failed to download feed";
		}

		char* content_type;
		curl_easy_getinfo(curl, CURLINFO_CONTENT_TYPE, &content_type);

		mi = recode_charset(mi, content_type);
		return mi;
	}
}
