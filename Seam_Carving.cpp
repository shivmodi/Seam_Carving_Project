#include<iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
float** calcenergy(Mat img, int r, int c)
{
        float** energyMat = new float*[r];
       for(int i=0; i<r; i++)
       energyMat[i] = new float[c];
       
       for(int i=0; i<r; i++)
       {
              for(int j=0;j<c; j++)
              {
              
                            float vert=0;
                            float horz=0;
                            int upx = i-1;
                            if(upx<0)
                            upx=0;
                            int downx =i+1;
                            if(downx>=r)
                            downx = r-1;
                            //horizontal intensity
                            Vec3b upintensity= img.at<Vec3b>(upx,j);
                            int blueup = upintensity.val[0];
                            int greenup = upintensity.val[1]; 
                            int redup= upintensity.val[2];
                            Vec3b dintensity = img.at<Vec3b>(downx,j);
                            int blued = dintensity.val[0];
                            int greend = dintensity.val[1]; 
                            int redd= dintensity.val[2];
                            horz += (blued -blueup )*(blued -blueup );
                            horz += (greenup-greend)*(greenup-greend);
                            horz += (redup-redd)*(redup-redd);
                            
                            //vertical intensity

                            int left = j-1;
                            int right = j+1;
                            if(left<0)
                            left =0;
                            if(right>=c)
                            right = c-1;
                             Vec3b lintensity= img.at<Vec3b>(i,left);
                            int bluel = lintensity.val[0];
                            int greenl = lintensity.val[1]; 
                            int redl= lintensity.val[2];
                             Vec3b rintensity= img.at<Vec3b>(i,right);
                            int bluer = rintensity.val[0];
                            int greenr = rintensity.val[1]; 
                            int redr = rintensity.val[2];
                            vert += (bluel-bluer)*(bluel-bluer);
                            vert += (greenl-greenr)*(greenl-greenr);
                            vert += (redl - redr)*(redl - redr);
                            horz = horz+vert;
                            horz = (float)sqrt(horz);
                            energyMat[i][j] = horz;
                           // cout<<" ("<<i<<" , "<<j<<" ) -- "<<horz;
                    
              }
            //  cout<<endl;
       }
       return energyMat;
}
int main()
{
       string s;
       cin>>s;  //./sample_input/sample1.jpeg
       Mat img = imread(s,IMREAD_COLOR);
      int r = img.rows;
       int c = img.cols;
      cout<<r<<" "<<c<<endl;
      float** energyMat= calcenergy(img, r,c);
       int** cost = new int*[r];
       for(int i=0; i<r; i++)
       {
              cost[i] = new int[c];
       }
       for(int i=0;i<c; i++)
           cost[0][i] = (int)energyMat[0][i];
       for(int i=1; i<r; i++)
       {
              for(int j=0; j<c; j++)
              {
                     int up = i-1;
                     int left = j-1;
                     int st = j;
                     int right = j+1;
                     if(left<0)
                     left = 0;
                     else if(right==c)
                     right = c-1;
                     cost[i][j] = energyMat[i][j]+min(cost[up][left],min(cost[up][right],cost[up][st]));
              }

       }
       int width;
       int height;
       cout<<"enter width and height"<<endl;
       cin>>width;
       cin>>height;
       int co = width;
       while(co>0)
       {
       
       co--;
       float min = 255;
       int x=0;

       for(int i=0; i<c; i++)
       {
              if(cost[r-1][i]<min)
              {
                     min = cost[r-1][i];
                     x =i;
              }
       }
        
       for(int j=r-1; j>0; j--)
       {      

              cost[j][x] = 256; 
              for(int i=x; i<c-1; i++)
              {
                     img.at<Vec3b>(j,i).val[0] = img.at<Vec3b>(j,i+1).val[0] ;
                     img.at<Vec3b>(j,i).val[1] = img.at<Vec3b>(j,i+1).val[1] ;
                     img.at<Vec3b>(j,i).val[2] = img.at<Vec3b>(j,i+1).val[2] ;
              }
              int left = x-1;
              int right = x+1;
              if(left<0)
              left = 0;
              if(right>=c)
              right = c-1;
              int up = j-1;
              int nex=x;
              if(cost[up][left]<=cost[up][x] && cost[up][left]<=cost[up][right])
              nex = left;
              if(cost[up][right]<=cost[up][left] && cost[up][right]<=cost[up][x])
              nex = right;
              x = nex;
       }
       
      

   }   
   
       Mat newi = img(Range(0,r),Range(0,c-width));
       energyMat = calcenergy(newi, r, c-width);
       c=c-width;
       
       for(int i=0; i<r; i++)
       {
              cost[i] = new int[c];
       }
       
       for(int i=0;i<r; i++)
           cost[i][0] = (int)energyMat[i][0];
       for(int j=1; j<c; j++)
       {
              for(int i=0;i<r; i++)
              {
                     int up = j-1;
                     int l = i-1;
                     int ri = i+1;
                     int s = i;
                     if(l<0)l=0;
                     if(ri>=r)ri=r-1;
                     cost[i][j] = energyMat[i][j]+min(cost[l][up],min(cost[s][up],cost[ri][up]) );
              }
       }
       co = height;
       while(co>0)
       {
              co--;
              int min = 255;
              int x=0;
              for(int i=0; i<r; i++)
              {
                     if(min>cost[i][c-1])
                     {
                            x= i;
                            min = cost[i][c-1];
                     }
              }
                cost[x][c-1] = 255;
              for(int j=c-1; j>0; j--)
              {
                    
                     for(int i=x; i<r-1; i++)
                     {
                            newi.at<Vec3b>(i,j).val[0] = newi.at<Vec3b>(i+1,j).val[0] ;
                            newi.at<Vec3b>(i,j).val[1] = newi.at<Vec3b>(i+1,j).val[1] ;
                            newi.at<Vec3b>(i,j).val[2] = newi.at<Vec3b>(i+1,j).val[2] ;
                     }
                    
                     int up = j-1;
                     int left = x-1;
                     int right = x+1;
                     if(left<0)
                     left = 0;
                     if(right>=r)
                     right = r-1;
                     if(cost[left][up]<cost[x][up] && cost[left][up]<cost[right][up])
                     x=left;
                     else if(cost[right][up]<cost[left][up] && cost[right][up]<cost[x][up])
                     x= right;
                     else
                     x = x;
              }
       }
       

    Mat newimg = newi(Range(0,r-height),Range(0,c));
        namedWindow("image", WINDOW_NORMAL);
      //  imshow("image", newimg);
       imwrite("sol.jpeg",newimg);
        waitKey();
}