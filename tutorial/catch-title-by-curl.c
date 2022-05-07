#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

void get_key_from_str(char *origin, char *str1, char *str2, char *key);

//提取href and news title
void get_href_title_from_str(char *origin)
{
    char *str1 = "热点要闻";
    char key[4096] = {0};
    char *str2, *str3, *str4;
    //定位到热点要闻
    origin = strstr(origin, str1);
    str1 = "<a href=\"";
    str2 = "\"";
    str3 = ">";
    str4 = "</a>";
    int count = 0;
    char *filename = "href_title.txt";
    FILE *fptr = fopen(filename, "w");
    while (count != 90)
    {
        count++;
        char *p = strstr(origin, str1);
        char *q = strstr(p + strlen(str1), str2);
        int len = q - p - strlen(str1);
        snprintf(key, len + 1, "%s", p + strlen(str1));
        key[len + 1] = '\0';
        printf("key %d = %s\n", count, key);

        fputs(key, fptr);
        fputs("\n", fptr);
        p = strstr(q + strlen(str2), str3);
        q = strstr(p + strlen(str3), str4);
        len = q - p - strlen(str3);
        snprintf(key, len + 1, "%s", p + strlen(str3));
        key[len + 1] = '\0';
        printf("key %d = %s\n", count, key);
        fputs(key, fptr);
        fputs("\n", fptr);
        origin = q;
    }
    fclose(fptr);
}

int main(int argc, char **argv)
{
    CURL *curl;
    FILE *fp = NULL, *fp_read = NULL;
    int file_size = 0;
    char *tmp = NULL;
    int flag = 0;
    char key[2048] = {0};
    char str1[2048] = {0};
    char str2[2048] = {0};

    if ((fp = fopen("test.txt", "w")) == NULL)
    {
        return 1;
    }
    curl = curl_easy_init();
    if (curl)
    {
        flag = 1;
        curl_easy_setopt(curl, CURLOPT_URL, "http://news.baidu.com/"); // curl设置网址
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);                 //将网页源码存在文件中，好像只能存文件，不能存字�?�串
        curl_easy_perform(curl);                                       //开始抓�?
        curl_easy_cleanup(curl);
        fclose(fp);
        fp_read = fopen("test.txt", "rb");
        fseek(fp_read, 0, SEEK_END);                    //把指针移到文�?最�?
        file_size = ftell(fp_read);                     //算出文本大小
        fseek(fp_read, 0, SEEK_SET);                    //再把指针移到最前面
        tmp = (char *)malloc(file_size * sizeof(char)); // malloc一段内�?
        printf("file_size:%d\n", file_size);
        fread(tmp, file_size, sizeof(char), fp_read); //读取文件
        fclose(fp_read);
        snprintf(str1, sizeof(str1), "<a href=\"");
        printf("str1 = %s\n", str1);
        snprintf(str2, sizeof(str2), "\"");
        printf("str2 = %s\n", str2);

        // printf("tmp = %s\n", tmp);
        // get_key_from_str(tmp, str1, str2, key); //取得网址
        get_href_title_from_str(tmp);

        // printf("key : %s\n", key);
        free(tmp);
    }

    if (!flag)
    {
        fclose(fp);
    }

    return 0;
}

//抓取str1和str2之间的关�?�?
void get_key_from_str(char *origin, char *str1, char *str2, char *key)
{
    str1 = "�?点�?�闻";
    char *p = strstr(origin, str1);
    str1 = "<a href=\"";
    char *str11 = "";
    origin = p;
    p = strstr(origin, str1);
    int count = 0;
    while (count != 20)
    {
        count++;
        p = strstr(p, str1);
        char *q = strstr(p + strlen(str1), str2);
        int len = q - p - strlen(str1);
        snprintf(key, len + 1, "%s", p + strlen(str1));
        key[len + 1] = '\0';
        printf("key %d = %s\n", count, key);
        p = q + 1;
    }
}