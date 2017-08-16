struct KEY
{
    unsigned height;
    unsigned width;
    unsigned x;
    unsigned y;
    char color;
    unsigned rgb[4];
    char type;
} Keyboard[20][100];

struct LINE
{
    unsigned num;
    unsigned x;
    unsigned y;
    unsigned w;
    unsigned h;
} Line[20];

bool IsWhite(unsigned i, unsigned j)
{
    if(pixel[i][j].r>=240 && pixel[i][j].r<=255 && pixel[i][j].g>=240 && pixel[i][j].g<=255 && pixel[i][j].b>=240 && pixel[i][j].b<=255)
        return true;
    return false;
}

bool IsLightGrey(unsigned i, unsigned j)
{
    if(pixel[i][j].r>=190 && pixel[i][j].r<=220 && pixel[i][j].g>=200 && pixel[i][j].g<=220 && pixel[i][j].b>=200 && pixel[i][j].b<=220)
        return true;
    return false;
}

bool IsDarkGrey(unsigned i, unsigned j)
{
    if(pixel[i][j].r>=160 && pixel[i][j].r<=190 && pixel[i][j].g>=170 && pixel[i][j].g<=200 && pixel[i][j].b>=180 && pixel[i][j].b<=210)
        return true;
    return false;
    //return false;
}

bool IsBlue(unsigned i, unsigned j)
{
    if(pixel[i][j].r>=0 && pixel[i][j].r<=20 && pixel[i][j].g>=115 && pixel[i][j].g<=135 && pixel[i][j].b>=240 && pixel[i][j].b<=255)
        return true;
    return false;
}

char RGBToColor(KEY i)
{
    char color;
    if(i.rgb[1]>=240 && i.rgb[1]<=255 && i.rgb[2]>=240 && i.rgb[2]<=255 && i.rgb[3]>=240 && i.rgb[3]<=255)
        color = 'W';
    if(i.rgb[1]>=160 && i.rgb[1]<=190 && i.rgb[2]>=170 && i.rgb[2]<=200 && i.rgb[3]>=180 && i.rgb[3]<=210)
        color = 'G';
    if(i.rgb[1]>=0 && i.rgb[1]<=20 && i.rgb[2]>=115 && i.rgb[2]<=135 && i.rgb[3]>=240 && i.rgb[3]<=255)
        color = 'B';
    if(i.rgb[1]>=190 && i.rgb[1]<=220 && i.rgb[2]>=200 && i.rgb[2]<=220 && i.rgb[3]>=200 && i.rgb[3]<=220)
        color = 'S';
    return color;
}
