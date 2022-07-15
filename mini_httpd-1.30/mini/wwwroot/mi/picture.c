#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include <sys/types.h>
#include <dirent.h>

#define RESOURCE_DIR	"../resource"
#define RESOURCE_DIR_PICTURE "../resource/picture"
#define RESOURCE_DIR_MUSIC	"../resource/music"
#define RESOURCE_DIR_VIDEO	"../resource/video"
#define RESOURCE_DIR_DOCUMENT	"../resource/document"
#define RESOURCE_DIR_SOFTWARE	"../resource/software"

#define RESULT(X,Y) X##Y

//.png/.jpg/...
int endsWith(const char* str, char* p)
{
	int len1,len2;
	len1 = strlen(str);
	len2 = strlen(p);
	if(len2 <=0 )
	  return 0;
	if(strncmp(str + len1 - len2,p,len2) == 0)
	  return 1;
	return 0;
}


static const int COLUMN_MAX_NUM = 3;

void main()
{
    DIR* dp;
    struct dirent* ep;
	int loop = 0;
	char buffer[4096];

    dp = opendir(RESOURCE_DIR_PICTURE);
    if(dp == NULL){
        printf("----error---\n");
	return;
    }

    printf("Content-type: text/html;charset=gb2312\n\n");//注意这里要两个换行符，这是HTML的规定
    printf("\n");
    printf("<html><head><title>MIShare</title></head>");
    printf("<body>");
    printf("<h1>MI Share</h1>");
    printf("<h2>Author:duguowei</h2>");
	printf("<form id=\"upload-form\" action=\"upload.php\" method=\"post\" enctype=\"multipart/form-data\">");
	printf("<input type=\"file\" id=\"upload\" name=\"upload\" /> <br/>");
	printf("<input type=\"submit\" value=\"Upload\" />");
	printf("</form>");
    //printf("Hello\n");
	//printf("<a href=\"../Screenshot_from_2022-03-10_12-22-20.png\">");
	//printf("<img src=\"../Screenshot_from_2022-03-10_12-22-20.png\" width=\"100\" height=\"100\" />");
    if (dp != NULL)
    {

		while (ep = readdir(dp)){
			if(!strcmp(ep->d_name,".") || !strcmp(ep->d_name,".."))
				continue;
			if(!endsWith(ep->d_name,".png") && !endsWith(ep->d_name,".jpg"))
				continue;
			if(loop > COLUMN_MAX_NUM){
				loop = 0;
				printf("<p>");
			}
			snprintf(buffer,sizeof(buffer),"<a href=%s/%s download=\"%s\">",RESOURCE_DIR_PICTURE,ep->d_name,ep->d_name);
			printf("%s",buffer);
			snprintf(buffer,sizeof(buffer),"<img src=\"%s/%s\" width=\"200\" height=\"200\" hspace=\"10\"/>",RESOURCE_DIR_PICTURE,ep->d_name);
			printf("%s",buffer);
			//printf("<p>");
			//printf("<a href=../resource/picture/%s>",ep->d_name);// /a>
			//printf("<img src=\"../resource/picture/%s\" width=\"200\" height=\"200\" hspace=\"10\"/>",ep->d_name);
			loop++;
		}
		closedir(dp);
    }
    printf("</body></html>");
}
