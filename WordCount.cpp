#include <stdio.h>
#include <string.h>

char order;
char file[30];
int *getCharNum(char *filename, int *totalNum);
void getOrderAndFilename(char info[]);

int main(int num,char *info[]){
    char filename[30];
    // totalNum[0]: ���ַ���  totalNum[1]: �ܵ�����
    int totalNum[2] = {0, 0};
	getCharNum(info[2],totalNum);
    if(!strcmp(info[1],"-c")){
        printf("�ַ���:%d chars\n",totalNum[0]);
    }else if(!strcmp(info[1],"-w")){
        printf("������:%d words\n",totalNum[1]);
    }else{
    	printf("ָ����󣡣�"); 
	}

    return 0;
}

/**
 * ͳ���ļ����ַ�����������
 *
 * @param  filename  �ļ���
 * @param  totalNum  �ļ�ͳ������
 *
 * @return  �ɹ�����ͳ�����ݣ����򷵻�NULL
**/
int *getCharNum(char *filename, int *totalNum){
    FILE *fp;  // ָ���ļ���ָ��
    char buffer[1003];  //���������洢��ȡ����ÿ�е�����
    int bufferLen;  // ��������ʵ�ʴ洢�����ݵĳ���
    int i;  // ��ǰ�����������ĵ�i���ַ�
    char c;  // ��ȡ�����ַ�
    int isLastBlank = 0;  // �ϸ��ַ��Ƿ��ǿո�
    int charNum = 0;  // ��ǰ�е��ַ���
    int wordNum = 0; // ��ǰ�еĵ�����
    int isLLastBlank=0; 

    if( (fp=fopen(filename, "rb")) == NULL ){
        perror(filename);
        return NULL;
    }

    // ÿ�ζ�ȡһ�����ݣ����浽buffer��ÿ�����ֻ����1000���ַ�
    while(fgets(buffer, 1003, fp) != NULL){
        bufferLen = strlen(buffer);
        // ����������������
        for(i=0; i<bufferLen; i++){
            c = buffer[i];
            if( c==' ' || c=='\t'){  // �����ո�
                !isLastBlank && wordNum++; 
				 charNum++; // ����ϸ��ַ����ǿո���ô��������1
                isLastBlank = 1;
            }else{  // ���Ի��з�
                charNum++;  // ����Ȳ��ǻ��з�Ҳ���ǿո��ַ�����1
                isLastBlank = 0;
            }
            if(i==bufferLen-2){
            	if(c==' '){
            		isLLastBlank=0;
				}
			} 
        }

         !isLLastBlank && wordNum++;  // ������һ���ַ����ǿո���ô��������1,//�߼���Щ���� 
        isLastBlank = 1;  // ÿ�λ�������Ϊ1

        // һ�н������������ַ������ܵ�����
        totalNum[0] += charNum;  // ���ַ���
        totalNum[1] += wordNum;  // �ܵ�����
        // ���㣬����ͳ����һ��
        charNum = 0;
        wordNum = 0;
    }

    return totalNum;
}
