#include "marker.h"

marker::marker()
{
}

int marker::get_yPOS(){
    return marker::yPOS;
}
int marker::get_xPOS(){
    return marker::xPOS;
}

void marker::set_yPOS(int y){
    marker::yPOS=y;
}
void marker::set_xPOS(int x){
    marker::xPOS=x;
}
