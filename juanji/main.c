#include "stdio.h"
#include "string.h"

typedef unsigned char  uint8;

#define  C_K_COL  3    //卷积核列数    convolution kernel
#define  C_K_ROW  3    //卷积核行数    普通卷积核一般为行数=列数
#define  ROW      8
#define  COL      16

//convolution kernel 卷积核
int CVL_K[3][3] = {1, 1, 1,
                   1, 1, 1,
                   1, 1, 1};
//高斯卷积核
int CVL_K2[3][3] = {1, 2, 1,
                    2, 4, 2,
                    1, 2, 1};

//uint8 image[ROW][COL] = {0, 1, 1, 1, 1, 0,
//                         0, 1, 1, 1, 1, 0,
//                         0, 1, 1, 1, 1, 0,
//                         0, 1, 1, 1, 1, 0,
//                         0, 1, 1, 1, 1, 0,
//                         0, 1, 1, 1, 1, 0};

//uint8 image[ROW][COL] = {0, 1, 1, 1, 1, 1, 1, 0,
//                         0, 1, 1, 1, 1, 1, 1, 0,
//                         0, 1, 1, 1, 1, 1, 1, 0,
//                         0, 1, 1, 1, 1, 1, 1, 0};

uint8 image[ROW][COL] =
{
    0, 1, 0, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 0, 1, 0,
    0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,
    0, 1, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 1, 0,
    0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0,
    0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 0,
    0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0,
    0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
};

//uint8 image[ROW][COL] =
//{
//    0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0,
//    0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,
//    0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
//    0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0,
//    0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0,
//    0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0,
//    0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
//    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
//};



int image_change0[ROW][COL] = {0};

int a[3][3] = {1, 5, 100,
               2, 3, 111,
               7, 6, 15};

int a2[2][3] = {11, 5, 100,
                2, 3, 111};

enum BUBBLING_NUM {
    BUBBLING_MAX,
    BUBBLING_MIN,
    BUBBLING_AVER,
    BUBBLING_MIDDLE,
};

int bubbling_sort(int (*sort_pointer)[C_K_COL], int row, int col, int return_flag);
int mid_sort(int (*p)[C_K_COL], int row, int col);
int max_sort(int (*p)[C_K_COL], int row, int col);
int min_sort(int (*p)[C_K_COL], int row, int col);
int aver_sort(int (*p)[C_K_COL], int row, int col);
void picture_init(int (*p)[3], int gray, int row, int col);
void gray_overflow_protection(int (*p)[C_K_COL], int row, int col);
void picture_convolution(int (*og_img)[COL], int re_gray, int p_row, int p_col, int ck_row, int ck_col);
void picture_filter(int (*ep_img)[C_K_COL+COL-1], int mf_gray, int ep_row, int ep_col, int ck_row, int ck_col);
void restore_picture(int (*rp_img)[C_K_COL+COL-1], int rp_gray, int rp_row, int rp_col, int ck_row, int ck_col);
void pixel_datatype_conversion(int flag);

/**
 * 应根据数组的具体列数更改形参指针中的常数
 * 选择数组需要输出的值：最大，最小，中值，平均值
 * @param sort_pointer
 * @param row
 * @param col
 * @param return_flag
 * @return
 */
int bubbling_sort(int (*sort_pointer)[C_K_COL], int row, int col, int return_flag) {

    int (*sort_pointer_func)(int (*sort_pointer)[C_K_COL], int row, int col);

    switch(return_flag) {
        case 0 :
            sort_pointer_func = &max_sort;
            return (*sort_pointer_func)(&sort_pointer[0], row, col);
        case 1 :
            sort_pointer_func = &min_sort;
            return (*sort_pointer_func)(&sort_pointer[0], row, col);
        case 2 :
            sort_pointer_func = &aver_sort;
            return (*sort_pointer_func)(&sort_pointer[0], row, col);
        case 3 :
            sort_pointer_func = &mid_sort;
            return (*sort_pointer_func)(&sort_pointer[0], row, col);
        default :
            break;
    }

    return 0;
}


/**
 * 输出数组中间值
 * 应根据函数图像的具体列数更改形参指针中的常数
 * @param p
 * @param row
 * @param col
 * @return
 */
int mid_sort(int (*p)[C_K_COL], int row, int col) {

    int i, j;
    int mid_num;
    int iTemp;
    int nums[row*col];
    int n = 0;

    for(i = 0; i < row; i++) {
        for(j = 0; j < col; j++) {
            nums[n++] = p[i][j];
        }
    }

    for(i = 0; i < row*col; i++) {
        for(j = 0; j < row*col-i-1; j++) {
            if(nums[j+1] > nums[j]) {
                iTemp = nums[j];
                nums[j] = nums[j+1];
                nums[j+1] = iTemp;
            }
        }
    }

    n = 0;
    for(i = 0; i < row; i++) {
        for(j = 0; j < col; j++) {
            p[i][j] = nums[n++];
        }
    }

    if((row*col) % 2 == 0) {
        mid_num = (nums[row*col/2] + nums[row*col/2 - 1]) / 2;
        return mid_num;
    }
    else {
        mid_num = nums[(row*col-1)/2];
        return mid_num;
    }

}

/**
 * 输出数组最大值
 * 应根据函数图像的具体列数更改形参指针中的常数
 * @param p
 * @param row
 * @param col
 * @return
 */
int max_sort(int (*p)[C_K_COL], int row, int col) {

    int i, j;
    int max_num = 0;

    for(i = 0; i < row; i++) {
        for(j = 0; j < col; j++) {
            if(max_num <= p[i][j]) {
                max_num = p[i][j];
            }
        }
    }

    return max_num;
}

/**
 * 输出数组最小值
 * 应根据函数图像的具体列数更改形参指针中的常数
 * @param p
 * @param row
 * @param col
 * @return
 */
int min_sort(int (*p)[C_K_COL], int row, int col) {

    int i, j;
    int min_num = p[0][0];

    for(i = 0; i < row; i++) {
        for(j = 0; j < col; j++) {
            if(min_num >= p[i][j]) {
                min_num = p[i][j];
            }
        }
    }

    return min_num;
}

/**
 * 输出数组平均值
 * 应根据函数图像的具体列数更改形参指针中的常数
 * @param p
 * @param row
 * @param col
 * @return
 */
int aver_sort(int (*p)[C_K_COL], int row, int col) {
    int i, j;
    int aver_num = 0;

    for(i = 0; i < row; i++) {
        for(j = 0; j < col; j++) {
            aver_num += p[i][j];
        }
    }

    aver_num /= row * col;
    return aver_num;
}

/**
 * 图像初始化赋值
 * 应根据函数图像数组的具体列数更改形参指针中的常数
 * @param p
 * @param gray
 * @param row
 * @param col
 */
void picture_init(int (*p)[3], int gray, int row, int col) {
    int i, j;
    for(i = 0; i < row; i++) {
        for(j = 0; j < col; j++) {
            p[i][j] = gray;
        }
    }
}
/**
 * 图像灰度保护 灰度值应在0-255之间
 * 应根据函数图像的具体列数更改形参指针中的常数
 * @param p
 * @param row
 * @param col
 */
void gray_overflow_protection(int (*p)[C_K_COL], int row, int col) {
    int i, j;
    for(i = 0; i < row; i++) {
        for(j = 0; j < col; j++) {
            if(p[i][j] > 256)
                p[i][j] = 255;
            if(p[i][j] < 0)
                p[i][j] = 0;
            else;
        }
    }
}

/**
 * 图像卷积
 * 应根据函数图像的具体列数更改形参指针中的常数
 * @param og_img  原始图像
 * @param re_gray 扩充边缘图像灰度值
 * @param p_row   原始图像行数
 * @param p_col   原始图像列数
 * @param ck_row  卷积核行数
 * @param ck_col  卷积核列数
 */
void picture_convolution(int (*og_img)[COL], int re_gray, int p_row, int p_col, int ck_row, int ck_col) {

    int i, j;
    int e_p_row = ck_row + p_row -1;
    int e_p_col = ck_col + p_col -1;
    int ep_pic[C_K_ROW+ROW-1][C_K_COL+COL-1] = {re_gray};

    //将原始图像拷贝到扩充后图像的正确位置
    for(i = (ck_row-1)/2; i <= e_p_row-1-(ck_row-1)/2; i++) {
        for(j = (ck_col-1)/2; j <= e_p_col-1-(ck_col-1)/2; j++) {
            ep_pic[i][j] = og_img[i-1][j-1];
        }
    }

    //打印扩充后的数组
    for(int i = 0; i < e_p_row; i++) {
        for (int j = 0; j < e_p_col; j++) {
            printf("%d ", ep_pic[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    //图像滤波
    picture_filter(&ep_pic[0], re_gray, e_p_row, e_p_col, ck_row, ck_col);

}

/**
 * 图像滤波
 * 应根据函数图像的具体列数更改形参指针中的常数
 * @param ep_img 已的扩充图像
 * @param mf_gray 初始化灰度值
 * @param ep_row 已扩充后图像的行数
 * @param ep_col 已扩充后图像的列数
 * @param ck_row 卷积核的行数
 * @param ck_col 卷积核的列数
 */
void picture_filter(int (*ep_img)[C_K_COL+COL-1], int mf_gray, int ep_row, int ep_col, int ck_row, int ck_col) {
    int i, j;
    int mf_pic[C_K_ROW+ROW-1][C_K_COL+COL-1] = {mf_gray};
    int ck_pic[C_K_ROW][C_K_COL] = {mf_gray};

    for(i = (ck_row-1)/2; i <= ep_row-1-(ck_row-1)/2; i++) {
        for(j = (ck_col-1)/2; j <= ep_col-1-(ck_col-1)/2; j++) {
            //如果要更改卷积核的大小，需要改这里面的算法
            //第一行
            ck_pic[0][0] = CVL_K[0][0] * ep_img[i-1][j-1];
            ck_pic[0][1] = CVL_K[0][1] * ep_img[i-1][j];
            ck_pic[0][2] = CVL_K[0][2] * ep_img[i-1][j+1];
            //第二行
            ck_pic[1][0] = CVL_K[1][0] * ep_img[i][j-1];
            ck_pic[1][1] = CVL_K[1][1] * ep_img[i][j];
            ck_pic[1][2] = CVL_K[1][2] * ep_img[i][j+1];
            //第三行
            ck_pic[2][0] = CVL_K[2][0] * ep_img[i+1][j-1];
            ck_pic[2][1] = CVL_K[2][1] * ep_img[i+1][j];
            ck_pic[2][2] = CVL_K[2][2] * ep_img[i+1][j+1];

            //灰度值溢出保护
            gray_overflow_protection(&ck_pic[0], ck_row, ck_col);

            //在这里更换卷积算法
            mf_pic[i][j] = bubbling_sort(&ck_pic[0], ck_row, ck_col,BUBBLING_MIDDLE);

        }
    }

    //打印卷积后的数组
    for(int i = 0; i < ep_row; i++) {
        for (int j = 0; j < ep_col; j++) {
            printf("%d ", mf_pic[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    //图像还原
    restore_picture(&mf_pic[0], mf_gray, ep_row, ep_col, ck_row, ck_col);
}

/**
 * 图像还原
 * @param rp_img
 * @param rp_gray
 * @param rp_row
 * @param rp_col
 * @param ck_row
 * @param ck_col
 */
void restore_picture(int (*rp_img)[C_K_COL+COL-1], int rp_gray, int rp_row, int rp_col, int ck_row, int ck_col) {
    int i, j;
    int r_p_row = rp_row - ck_row + 1;
    int r_p_col = rp_col - ck_col + 1;
    int rp_pic[ROW][COL] = {rp_gray};

    for(i = 0; i < r_p_row; i++) {
        for (j = 0; j < r_p_col; j++) {
            rp_pic[i][j] = rp_img[i+1][j+1];
        }
    }

    //打印还原后的图像
    for(int i = 0; i < r_p_row; i++) {
        for (int j = 0; j < r_p_col; j++) {
            printf("%d ", rp_pic[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    //将还原后的图像拷贝到image_change0数组中
    memcpy(image_change0[0], rp_pic[0], sizeof(image_change0));

}

/**
 * 图像像素数据类型转换(仅限于摄像头直接采集回来的数组图像)
 * @param flag=1,将uint8 image 转换成 int image_change0
 *        flag=2,将int image_change0 转换成 uint8 image
 */
void pixel_datatype_conversion(int flag) {
    int i, j;

    if(flag == 1) {
        for(i = 0; i < ROW; i++) {
            for(j = 0; j < COL; j++) {
                image_change0[i][j] = (int)image[i][j];
            }
        }
    }
    if(flag == 2) {
        for(i = 0; i < ROW; i++) {
            for(j = 0; j < COL; j++) {
                image[i][j] = (uint8)image_change0[i][j];
            }
        }
    }
    else;
}



int main(int argc, char **argv) {

    //打印image原始数组
    for(int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            printf("%d ", image[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    //将image原始数组拷贝到image_change0数组中并将数组类型强制转换为int
    pixel_datatype_conversion(1);
    //图像中值滤波
    picture_convolution(&image_change0[0], 0, ROW, COL, C_K_ROW, C_K_ROW);
    //将image_change0数组拷贝到image数组中并将数组类型强制转换为uint8
    pixel_datatype_conversion(2);

    //打印卷积后的image数组
    for(int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            printf("%d ", image[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    return 0;
}

