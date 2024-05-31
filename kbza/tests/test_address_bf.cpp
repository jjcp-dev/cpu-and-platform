import Kbza;

int main()
{
    #if defined ALIGNMENT_EQ_0

    //
        auto x = Kbza::Address<0>::create(10);

    #elif defined ALIGNMENT_POT

        auto x = Kbza::Address<3>::create(10);

    #elif defined COPY_CTOR_UNDER_ALIGNED

        Kbza::Address<4>(Kbza::Address<2>::create_aligned(2));

    #elif defined COPY_ASSIGNMENT_UNDER_ALIGNED

        auto x = Kbza::Address<8>::create_aligned(32);

        x = Kbza::Address<4>::create_aligned(32);

    #else
        
        #error "No build failure tests enabled!"

    #endif

    return 0;
}
