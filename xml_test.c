#include "ts_xml.h"

int main(int argc, char **argv)
{

	char *xml_ch = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\
				   <maps>\
				   <key name =\"shahai_bind\">ZmFsc2U.</key>\
				   <key name =\"shahai_crypt_data\">DZya0GizgFpofi40KUu3mrw5GdC3PMOP</key>\
				   </maps>";

	char *xml_ch_1 = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\
				   <maps>\
				   <key name =\"shahai_bind\">ZmFsc2U.</key>\
				   <key name =\"shahai_crypt_data\">DZya0GizgFpofi40KUu3mrw5GdC3PMOP</key>\
				   </maps>";

	char des[1024] = {0};
	/*char *temp = strtok(xml_ch_1, "</key>");*/
	char *temp = NULL;
	//GetValueByTag(xml_ch, des, "key"); // --> ZmFsc2U.
	//GetValueByTag(xml_ch, des, "maps"); // --> <key name =\"shahai_bind\">ZmFsc2U.</key><key name =\"shahai_crypt_data\">DZya0GizgFpofi40KUu3mrw5GdC3PMOP</key>

	//GetValueByPath(xml_ch, des, "/key");
	//GetValueByTag(xml_ch, des, "key");
	//printf("%s \n", des);

	//temp = strstr(xml_ch_1, "shahai_bind");
	//printf("temp = %s \n", temp);
	GetValueByTagAndName(xml_ch_1, "/key", "shahai_crypt_data",des);
	printf("%s \n", des);
	

	



	getchar();


	return 0;
}
