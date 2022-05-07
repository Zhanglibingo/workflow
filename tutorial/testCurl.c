#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <cjson/cJSON.h>

int main(void)
{
    // 1.创建一个curl句柄
    CURL *curl = NULL;
    CURLcode res;

    // 2.初始化一个curl句柄
    curl = curl_easy_init();

    // 3.给句柄设置一些参数
    // curl_easy_setopt(curl, CURLOPT_URL, "http://www.pullword.com/baobian/");
    const cJSON *ss = NULL;

    curl_easy_setopt(curl, CURLOPT_URL, "http://baobianapi.pullword.com:9091/get.php");
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "十一月再见,十二月你好,2021年最后一个月总会有不期而遇的温暖,和生生不息的希望"); //这是post的内容
    // curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);                                                                               //这是请求过程的调试log
    // curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
    char *str = ""; //数据请求到以后的回调函数
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &ss);
    str = cJSON_Print(ss); //选择输出到字符串
    printf("str = %s\n", str);
    // 4.将curl句柄向远程服务器提交
    res = curl_easy_perform(curl);
    if (res != CURLE_OK)
    {
        printf("curl easy perform error res = %d", res);
        return 1;
    }
    // 5.初始化服务器的响应结果
    // 6.释放句柄空间
    curl_easy_cleanup(curl);
}
