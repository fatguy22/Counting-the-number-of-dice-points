#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
	
	FILE *fptr;//diceData系列檔  
	FILE *rptr;//result檔案 
	int i, zero, j;
	char filename[20];
	char number[4]={0};
	int count[10]={0};//統計csv檔內容的陣列 
	float ratio[10]={0};
	
	for(i=0;i<1000;i++){
		strcpy(filename, "diceData");
		sprintf(number, "%d", i);//sprintf可以把int寫進字元陣列裡面  
		int len = strlen(number);
		
		zero = 6 - len;
		 
		for(j=0;j<zero;j++){
			strcat(filename, "0");
		}
		
		strcat(filename, number);//把檔名接起來 
		strcat(filename, ".csv");
		//到上面為止都是改檔名的循環 
		
		fptr = fopen(filename, "r");
		/*if(fptr == NULL){//到目前為止，開檔成功 
			printf("i=%d,No\n", i);
		}
		else{
			printf("i=%d,Yes\n", i);
		}*/ 
		if(fptr!=NULL){
			
			char ch = ',';
			char ch_b = ',';
			char ch_bb = ',';
			
			while(!feof(fptr)){
				
				ch_bb = ch_b;
				ch_b = ch;
				ch = getc(fptr);
				
				if((ch_bb == ',' && ch_b >= '1' && ch_b <='6' && ch == ',') ||
				(ch_bb == ',' && ch_b >= '1' && ch_b <='6' && ch == '\n') ||
				(ch_bb == '\n' && ch_b >= '1' && ch_b <='6' && ch == ',')){
				//要記得處理前面[換行；數字；逗點] 以及 後面[逗點；數字；換行] 的情況  
				//if條件內的第一行是在一個row裡面數的pattern，第二、三行是邊界條件  
					
					switch(ch_b){
						case'1':
							count[1]++;
							break;
						case'2':
							count[2]++;
							break;
						case'3':
							count[3]++;
							break;
						case'4':
							count[4]++;
							break;
						case'5':
							count[5]++;
							break;
						case'6':
							count[6]++;
							break;
						default:
							break;
					}
				}
				else if((ch_bb == ',' && ch_b <= '9' && ch_b >= '0' && ch >= '0' && ch <= '9') || 
				(ch_bb == '\n' && ch_b <= '9' && ch_b >= '0' && ch >= '0' && ch <= '9')){
					count[7]++;//登記錯誤點數的次數 
				}
				else if((ch_b == ',' && ch == ',') || (ch_b == ',' && ch == '\n')
				|| (ch_b == '\n' && ch == ',')){
					count[8]++;//count[8]記錄空格 
				}
				
			}
		}
		
		fclose(fptr);//fopen的上限是512個檔案，要記得關檔  
		
	}
	
	for(j=1;j<=8;j++){//計算total的數目(count[9])
        	count[9] += count[j];
    }

    int total = count[9];
    int skip = count[8];
    int error = count[7];

    for(j=1;j<=9;j++){
        ratio[j] = (float)count[j]/total;
    }

    rptr = fopen("result.csv","w");
    
    if (rptr != NULL){
        fprintf(rptr," ,1,2,3,4,5,6,Error,Skip,Total\n");

        fprintf(rptr,"Count,%d,%d,%d,%d,%d,%d,%d,%d,%d\n",count[1],count[2],
        count[3],count[4],count[5],count[6],error,skip,total);

        fprintf(rptr,"Ratio,%.6f,%.6f,%.6f,%.6f,%.6f,%.6f,%.6f,%.6f,%.6f",ratio[1],
        ratio[2],ratio[3],ratio[4],ratio[5],ratio[6],ratio[7],ratio[8],ratio[9]);
    }
    
    fclose(rptr);
	
	return 0;
	
}
//對1個檔案的測試正確
//對30個檔案的測試正確 
//對50個檔案的測試正確 
