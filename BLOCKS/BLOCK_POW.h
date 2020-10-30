#ifndef BLOCKS_H
    #include "BLOCKS.h"   
#endif

namespace BLOCKS{

 class BlockPOW : public BLOCK {
        private:
            static int count;
        public:

            struct Properties{
                public:
                    int N_IN;
                    int N_OUT;
                    int val2;
            }Properties;
            
            BlockPOW(){
                name = "POW";
                TYPE = BLKType_Sum;
                Properties.val2 = 545;
                //props.IN = 2;
                //props.OUT = 1;
            }
            virtual void Exec() override{
                cout<<"\n"<<name;
            }
            virtual BLOCK * Create(){
                return new BlockPOW();
            }

           
    };

    void BlockPOW_INIT(){
        ALL_BLOCKS_GUI[BLKType_Pow] = new BlockPOW();
    }
 

}