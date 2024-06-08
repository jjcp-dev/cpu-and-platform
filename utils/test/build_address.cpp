import Utils;

using namespace Utils;

int main()
{
    #if defined ALIGNMENT_EQ_0

        auto x = Address<0>::create(10);

    #elif defined ALIGNMENT_POT

        auto x = Address<3>::create(10);

    #elif defined COPY_CTOR_UNDER_ALIGNED

        Address<4>(Address<2>::create_aligned(2));

    #elif defined COPY_ASSIGNMENT_UNDER_ALIGNED

        auto x = Address<8>::create_aligned(32);

        x = Address<4>::create_aligned(32);

    #else
        
       // No build failure tests enabled!

    #endif

    return 0;
}
