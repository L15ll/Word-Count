#include <stdio.h>
#include <string.h>

int *getCharNum(char *filename, int *totalNum);
int main(int argc, char *argv[]){
    char filename[30];
    // totalNum[0]: 总行数  totalNum[1]: 总字符数  totalNum[2]: 总单词数
    int totalNum[3] = {0, 0, 0};
    strcpy(filename, argv[2]);
    
    if(getCharNum(filename, totalNum)){
		if((strcmp(argv[1], "-c")==0) && (strcmp(argv[1], "-w")!=0)){
			printf("TotalChars: %d\n", totalNum[1]);
		}else if((strcmp(argv[1], "-c")!=0) && (strcmp(argv[1], "-w")==0)){
			printf("TotalWords: %d\n", totalNum[2]);
		}
    }else{
        printf("Error!\n");
    }
    
    return 0;
}

/**
 * 统计文件的字符数、单词数、行数
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
                !isLastBlank && wordNum++;  // 如果上个字符不是空格，那么单词数加1
                isLastBlank = 1;
            }
            else{  
                charNum++;  // 字符数加1
                isLastBlank = 0;
            }
        }
        
        !isLastBlank && wordNum++;  // 如果最后一个字符不是空格，那么单词数加1
        isLastBlank = 1;  // 每次换行重置为1
        
        // 一行结束，计算总字符数、总单词数、总行数
        totalNum[0]++;  // 总行数
        totalNum[1] += charNum;  // 总字符数
        totalNum[2] += wordNum;  // 总单词数

        // 置零，重新统计下一行        
        charNum = 0;
        wordNum = 0;
    }
    return totalNum;
}
