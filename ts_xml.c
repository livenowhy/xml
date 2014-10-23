/** 
 * 解析xml包
 * add by liuzhangpei 2014-10-23
 */

#include "ts_xml.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #include <strings.h>

// 不区分大小写比较 s1和s2
int strcasecmp(const char *s1, const char *s2)  
{  
	int c1, c2;  
	do {  
		c1 = tolower(*s1++);  
		c2 = tolower(*s2++);  
	} while(c1 == c2 && c1 != 0);  
	return c1 - c2;  
}


/*************************************************************************
 Function: Trim(char* str) 
 Purpose : Trim the left and right spaces of the string 
 Input   : char* str --- the string pointer that need to trim the space char
 Return  : None
 Modify  :
 Remark  :
 *************************************************************************/
void Trim(char* str) 
{
	char *ptail, *p;
	int L;
	p = str;
	while(*p && (*p==' '||*p=='\t'||*p=='\r'||*p=='\n')) p++;
	if (!*p) 
	{
		*str = 0;
		return ;
	}

	ptail = p+strlen(p)-1;
	while(ptail > p && (*ptail == ' ' || *ptail == '\t' || *ptail == '\n' || *ptail == '\r')) 
	{
		*ptail = 0;
		ptail--;
	}

	L = strlen(p);
	memmove(str, p, L);
	str[L] = 0;
}


/*************************************************************************
 Function: GetItem(char *strSource, char *strDest, int pos, char sep)
 Purpose : 从一个格式化字符串中得到一项的值
 Input   : char *strSource  --- the source string      源字符串
           char *strDest    --- the destination string  目标字符串
           int  pos         --- the pos the field need to get  需要获得字段的位置(0开始)
           char sep         --- the seperate byte such as '|'  分割字段,例如 '|'
 Return  : 0 --- get succeed
 Modify  :
 Remark  : the source sting should be like "111|2222|4333|"
           to get the second field of the sting, you can call
           GetItem(strSource, strDest, 1, '|');
           the strDest should be "2222"
 *************************************************************************/
int GetItem(char *strSource, char *strDest, int pos, char sep)
{
	char* temp1;
	char* temp2;
	char  strSource_temp[2048];
	int i;

	strcpy(strSource_temp, strSource);
	temp1 = strSource_temp;

	for (i = 0; i < pos; i++)
	{
		temp2 = strchr(temp1, sep);
		if (temp2)
		{
			*temp2 = 0;
			temp1 = temp2 + 1;
		}
		else
			return -1;
	}

	temp2 = strchr(temp1, sep);
	if (temp2)
	{
		*temp2 = 0;
		strcpy(strDest, temp1);
	}
	else
		strcpy(strDest, temp1);

	return 0;
}



/*************************************************************************
 Function: GetValueByTag(char *src, char *des, char* tag)
 Purpose : 取得xml包中第一个 tag 标签,包裹的内容   去XML的一个tag的值
 Input   : char *src        --- the source string
           char *des        --- the destination string
           char* tag        --- the tag need to get
 Return  : 0 --- get succeed
 Remark  : char *xml_ch = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\
           <maps><key name =\"shahai_bind\">ZmFsc2U.</key>\
		   <key name =\"shahai_crypt_data\">DZya0GizgFpofi40KUu3mrw5GdC3PMOP</key>\
		   </maps>";

 char des[1024] = {0};
 GetValueByTag(xml_ch, des, "key"); // --> ZmFsc2U.
 GetValueByTag(xml_ch, des, "maps");
 --> <key name =\"shahai_bind\">ZmFsc2U.</key><key name =\"shahai_crypt_data\">DZya0GizgFpofi40KUu3mrw5GdC3PMOP</key>
 *************************************************************************/
int GetValueByTag(char *src, char *des, char* tag)
{
	char* temp1;
	char* temp2;



	char strTemp[MAX_DATA_LEN];
	
	char strTag[1024];
	char strTagName[1024];

	char *temp3 = NULL;

	if (src == NULL || des == NULL || tag == NULL)
		return -1;

	strcpy(strTemp, src);

	// 找到<tag>标签头
	sprintf(strTag, "<%s", tag);
	temp1 = strTemp;

	while(1)
	{
		temp1 = strstr(temp1, strTag);
		if (temp1 == NULL)
			return -1;

		temp2 = strchr(temp1, '>');
		if (temp2 == NULL)
			return -1;

		// get tag name
		*temp2 = 0;
		/*char **/temp3 = strchr(temp1 + 1, ' ');
		if (temp3)
			*temp3 = 0;
		strTagName[0] = 0;
		strcpy(strTagName, temp1 + 1); 
		temp1 = temp2 + 1;
		if (strcasecmp(strTagName, tag) == 0)
			break;
	}

	// 找到</tag>标签尾
	sprintf(strTag, "</%s>", tag);
	temp2 = strstr(temp1, strTag);
	if (temp2 == NULL)
		return -1;

	*temp2 = 0;
	strcpy(des, temp1);
	Trim(des);
	return 0;
}



/*************************************************************************
 Function: GetValueByPath(char *src, char *des, char* path)
 Purpose : Get item's value from a format string
 Input   : char *src      --- 待解析的XML缓冲区
           char *des      --- 解析得到的结果
           char *path     --- 以'/'分割的路径
 Return  : 0 --- get succeed
 Modify  :
 Remark  : 
 *************************************************************************/
int GetValueByPath(char *src, char *des, const char* path)
{
	char *temp1;
	char *temp2;
	char szPath[1024];
	char strTemp[MAX_DATA_LEN];
	char strTag[1024];
	int iSn = 1;

	if (src == NULL || des == NULL || path == NULL)
		return -1;

	strcpy(szPath, path);
	
	strcpy(strTemp, src);
	
	// 找到第一个头
	strTag[0] = 0;
	GetItem(szPath, strTag, 1, '/');
	

	while(strlen(strTag))
	{
		if (GetValueByTag(strTemp, strTemp, strTag))
			return -1;

		iSn++;
		strTag[0] = 0;
		GetItem(szPath, strTag, iSn, '/');
	}

	strcpy(des, strTemp);
	return 0;
}

/** 
 * 解析xml包数据,类似:
 * <key name ="shahai_user_name">bGlseQ..</key>
 * <key name ="shahai_init_time">MjAxNDEwMTU.</key>
 * 相同的标签,name属性不同解析出标签中的信息
 * src:xml包源字符串; tag:Tag标签字符串(带/); name:Tab标签中的name属性;  des:解析的数据
 */
int GetValueByTagAndName(const char *src, const char *tag, const char *name, char *des)
{

	char *temp = NULL;
	char tmp_xml[MAX_READ_BUF] = {0};
	char tmp_des[1024] = {0};

	char *head_xml = "<key name = \"";
	temp = strstr(src, name);

	printf("temp = %s \n", temp);

	//sprintf(tmp_xml, "<key name = \"%s", temp); 使用memcpy替换sprintf函数

	memcpy(tmp_xml, head_xml, strlen(head_xml));
	memcpy(tmp_xml+strlen(head_xml), temp, strlen(temp));

	printf("------\n%s \n ", tmp_xml);

	GetValueByPath(tmp_xml, tmp_des, tag);

	printf("------\ndes --> %s \n ", tmp_des);

	memcpy(des, tmp_des, strlen(tmp_des));


	return 0;
}