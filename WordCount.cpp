#include <stdio.h>
#include <string.h>

char order;
char file[30];
int *getCharNum(char *filename, int *totalNum);
void getOrderAndFilename(char info[]);

int main(int num,char *info[]){
    char filename[30];
    // totalNum[0]: 总字符数  totalNum[1]: 总单词数
    int totalNum[2] = {0, 0};
	getCharNum(info[2],totalNum);
    if(!strcmp(info[1],"-c")){
        printf("字符数:%d chars\n",totalNum[0]);
    }else if(!strcmp(info[1],"-w")){
        printf("单词数:%d words\n",totalNum[1]);
    }else{
    	printf("指令错误！！"); 
	}

    return 0;
}

/**
 * 统计文件的字符数、单词数
 *
 * @param  filename  文件名
 * @param  totalNum  文件统计数据
 *
 * @return  成功返回统计数据，否则返回NULL
**/
int *getCharNum(char *filename, int *totalNum){
    FILE *fp;  // 指向文件的指针
    char buffer[1003];  //缓冲区，存储读取到的每行的内容
    int bufferLen;  // 缓冲区中实际存储的内容的长度
    int i;  // 当前读到缓冲区的第i个字符
    char c;  // 读取到的字符
    int isLastBlank = 0;  // 上个字符是否是空格
    int charNum = 0;  // 当前行的字符数
    int wordNum = 0; // 当前行的单词数
    int isLLastBlank=0; 

    if( (fp=fopen(filename, "rb")) == NULL ){
        perror(filename);
        return NULL;
    }

    // 每次读取一行数据，保存到buffer，每行最多只能有1000个字符
    while(fgets(buffer, 1003, fp) != NULL){
        bufferLen = strlen(buffer);
        // 遍历缓冲区的内容
        for(i=0; i<bufferLen; i++){
            c = buffer[i];
            if( c==' ' || c=='\t'){  // 遇到空格
                !isLastBlank && wordNum++; 
				 charNum++; // 如果上个字符不是空格，那么单词数加1
                isLastBlank = 1;
            }else{  // 忽略换行符
                charNum++;  // 如果既不是换行符也不是空格，字符数加1
                isLastBlank = 0;
            }
            if(i==bufferLen-2){
            	if(c==' '){
            		isLLastBlank=0;
				}
			} 
        }

         !isLLastBlank && wordNum++;  // 如果最后一个字符不是空格，那么单词数加1,//逻辑有些不对 
        isLastBlank = 1;  // 每次换行重置为1

        // 一行结束，计算总字符数、总单词数
        totalNum[0] += charNum;  // 总字符数
        totalNum[1] += wordNum;  // 总单词数
        // 置零，重新统计下一行
        charNum = 0;
        wordNum = 0;
    }

    return totalNum;
}
