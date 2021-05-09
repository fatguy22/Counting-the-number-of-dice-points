/*
* �t�šG��u��1�~��
* �Ǹ��G7109056124 
* �m�W�G���@�Z 
* �p���q�l�H�c�Gingredienter@gmail.com 
*/ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
	
	FILE *fptr;//diceData�t�C��  
	FILE *rptr;//result�ɮ� 
	int i, zero, j;
	char filename[20];
	char number[4]={0};
	int count[10]={0};//�έpcsv�ɤ��e���}�C 
	float ratio[10]={0};
	
	for(i=0;i<1000;i++){
		strcpy(filename, "diceData");
		sprintf(number, "%d", i);//sprintf�i�H��int�g�i�r���}�C�̭�  
		int len = strlen(number);
		
		zero = 6 - len;
		 
		for(j=0;j<zero;j++){
			strcat(filename, "0");
		}
		
		strcat(filename, number);//���ɦW���_�� 
		strcat(filename, ".csv");
		//��W������O���ɦW���`�� 
		
		fptr = fopen(filename, "r");
		/*if(fptr == NULL){//��ثe����A�}�ɦ��\ 
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
				//�n�O�o�B�z�e��[����F�Ʀr�F�r�I] �H�� �᭱[�r�I�F�Ʀr�F����] �����p  
				//if���󤺪��Ĥ@��O�b�@��row�̭��ƪ�pattern�A�ĤG�B�T��O��ɱ���  
					
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
					count[7]++;//�n�O���~�I�ƪ����� 
				}
				else if((ch_b == ',' && ch == ',') || (ch_b == ',' && ch == '\n')
				|| (ch_b == '\n' && ch == ',')){
					count[8]++;//count[8]�O���Ů� 
				}
				
			}
		}
		
		fclose(fptr);//fopen���W���O512���ɮסA�n�O�o����  
		
	}
	
	for(j=1;j<=8;j++){//�p��total���ƥ�(count[9])
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
//��1���ɮת����ե��T
//��30���ɮת����ե��T 
//��50���ɮת����ե��T 
