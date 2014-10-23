/** 
 *  ½âÎöxml°ü
 * add by liuzhangpei 2014-10-23
 */

#ifndef _TS_XML_H_
#define _TS_XML_H_

#include <stdio.h>

#define  MAX_DATA_LEN	    65535
#define  MAX_READ_BUF       131070


void Trim(char* str);

int GetItem(char *strSource, char *strDest, int pos, char sep);
int GetValueByTag(char *src, char *des, char* tag);

int GetValueByPath(char *src, char *des, const char* path);

int GetValueByTagAndName(const char *src, const char *tag, const char *name, char *des);

#endif