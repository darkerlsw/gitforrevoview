#include "stdlib.h"


int mid_sort2(int *sort_pointer, int line, int row){
    int i, j, s;
    int mid_num;
    int iTemp;
    int nums[line*row];
    int n = 0;

    for(i = 0; i < line; i++){
        for(j = 0; j < row; j++){
            nums[n++] = sort_pointer[i*line+j];
        }
    }

    for(i = 0; i < line*row-1; i++){
        for(j = 0; j < line*row-i-1; j++){
            if(nums[j+1] > nums[j]){
                iTemp = nums[j];
                nums[j] = nums[j+1];
                nums[j+1] = iTemp;
            }
        }
    }

    n = 0;
    for(i = 0; i < line; i++){
        for(j = 0; j < row; j++){
            sort_pointer[i*line+j] = nums[n++];
        }
    }




    /*
    //列排序
    for(s = 0; s < row; s++){
        for(i = 0; i < line-1; i++){
            for(j = 0; j < line-i-1; j++){
                if(sort_pointer[j*line+s+row] > sort_pointer[j*line+s]){
                    iTemp = sort_pointer[j*line+s];
                    sort_pointer[j*line+s] = sort_pointer[j*line+s+row];
                    sort_pointer[j*line+s+row] = iTemp;
                }
            }
        }
    }



    //行排序
    for(s = 0; s < line; s++){
        for(i = 0; i < row-1; i++){
            for(j = 0; j < row-i-1; j++){
                if(sort_pointer[s*line+j+1] > sort_pointer[s*line+j]){
                    iTemp = sort_pointer[s*line+j];
                    sort_pointer[s*line+j] = sort_pointer[s*line+j+1];
                    sort_pointer[s*line+j+1] = iTemp;
                }
            }
        }
    }
    */


    if((line*row) % 2 == 0){
        mid_num = (sort_pointer[line*row/2] + sort_pointer[line*row/2 - 1]) / 2;
        return mid_num;
    }
    else{
        mid_num = sort_pointer[(line*row-1)/2];
        return mid_num;
    }
}

