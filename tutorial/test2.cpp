#include <iostream>
#include <stdio.h>
#include <curl/curl.h>
#include <cjson/cJSON.h>
#include <memory.h>
using namespace std;

size_t receive_data(void *buffer, size_t size, size_t nmemb, FILE *file);

size_t writeCallback(void *ptr, size_t size, size_t nmemb, void *userdata)
{
    std::string *str = dynamic_cast<std::string *>((std::string *)userdata);
    str->append((char *)ptr, size * nmemb);
    return size * nmemb;
}

int main()
{
    char url[] = "http://www.sina.com.cn";
    cJSON *cjson_test = NULL;

    FILE *file = fopen("href_title.txt", "r");
    char buf[2048];
    FILE *file2 = fopen("score.txt", "w");
    int index = 0;
    while (fgets(buf, sizeof(buf), file))
    {
        index++;
        if (index % 2 == 1)
            continue;
        cout << buf << endl;

        curl_global_init(CURL_GLOBAL_ALL);
        CURL *handle = curl_easy_init();
        string str;
        curl_easy_setopt(handle, CURLOPT_URL, "http://baobianapi.pullword.com:9091/get.php");
        curl_easy_setopt(handle, CURLOPT_POSTFIELDS, buf);
        // curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, receive_data);
        // curl_easy_setopt(handle, CURLOPT_WRITEDATA, file);
        curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, writeCallback);
        curl_easy_setopt(handle, CURLOPT_WRITEDATA, &str);
        curl_easy_perform(handle);
        // cout << "str = " << str << endl;
        int index = str.find(':');
        string scores = str.substr(index + 1, str.length() - index - 2);
        cout << "score = " << scores << endl;
        curl_easy_cleanup(handle);
        curl_global_cleanup();
        fputs(scores.c_str(), file2);
        fputs("\n", file2);
    }
    fclose(file);
    fclose(file2);
    return 0;
}

size_t receive_data(void *buffer, size_t size, size_t nmemb, FILE *file)
{
    size_t r_size = fwrite(buffer, size, nmemb, file);
    return r_size;
}