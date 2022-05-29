#include <stdio.h>
#include <string.h>

int *getCharNum(char *filename, int *totalNum);
int main(int argc, char *argv[]){
    char filename[30];
    // totalNum[0]: ������  totalNum[1]: ���ַ���  totalNum[2]: �ܵ�����
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
 * ͳ���ļ����ַ�����������������
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
                !isLastBlank && wordNum++;  // ����ϸ��ַ����ǿո���ô��������1
                isLastBlank = 1;
            }
            else{  
                charNum++;  // �ַ�����1
                isLastBlank = 0;
            }
        }
        
        !isLastBlank && wordNum++;  // ������һ���ַ����ǿո���ô��������1
        isLastBlank = 1;  // ÿ�λ�������Ϊ1
        
        // һ�н������������ַ������ܵ�������������
        totalNum[0]++;  // ������
        totalNum[1] += charNum;  // ���ַ���
        totalNum[2] += wordNum;  // �ܵ�����

        // ���㣬����ͳ����һ��        
        charNum = 0;
        wordNum = 0;
    }
    return totalNum;
}
