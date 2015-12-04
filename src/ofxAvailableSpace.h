//
//  ofxAvailableSpace.h
//
//  Created by nausea on 12/2/15.
//
//

#pragma once
#include "ofMain.h"

class ofxAvailableSpace{
public:
    enum SpaceFormat{
        BYTES,
        KB,
        MB,
        GB
    };
    
    static bool isNumber(char c){
        return (c=='0'||c=='1'||c=='2'||c=='3'||c=='4'||c=='5'||c=='6'||c=='7'||c=='8'||c=='9');
    }
    
    static float getSizeMultiplier(char c){
        float sm = -1;
        if(c=='G'||c=='g'){
            sm = 1000000000;
        }else if(c=='M'||c=='m'){
            sm = 1000000;
        }else if(c=='K'||c=='k'){
            sm = 1000;
        }
        return sm;
    }
    
    static float getAvailableSpace(SpaceFormat sf=MB){
        string sAvSpace = ofSystem("df -Ph . | awk 'NR==2 {print $4}'");
        string sNum="";
        float mult = 0;
        bool bNum = false;
        for(int i=0;i<sAvSpace.length();i++){
            if(!bNum){
                if(isNumber(sAvSpace[i])){
                    sNum+=sAvSpace[i];
                }else{
                    bNum=true;
                    if(i>0)i--;
                }
            }else{
                float mm = getSizeMultiplier(sAvSpace[i]);
                if(mm>0){
                    mult = mm;
                    switch (sf) {
                        case KB:
                            mult/=1000;
                            break;
                        case MB:
                            mult/=1000000;
                            break;
                        case GB:
                            mult/=1000000000;
                            break;
                            
                        default:
                            break;
                    }
                    i=sAvSpace.length()+2;
                }
            }
        }
        return (ofToFloat(sNum)*mult);
    }
};