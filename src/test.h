enum flags
{
    something  = 0,
    something2 = 1 << 0,
    something3 = 1 << 1
}; // this is wrong because there is a limit of 64 bits
   //

enum high_level_flag
{
    nothing,
    nothing1,
    nothing2,
    nothing3
};

static unsigned char arr[128];
static int flaggy = something;

inline void test()
{
    if (flaggy & something)
    {
    }

    arr[nothing] = true;
    if(arr[nothing]) {

    }
}
