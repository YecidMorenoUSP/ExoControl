#ifndef BLOCKS_H
    #include "BLOCKS.h"   
#endif

namespace BLOCKS{

 class BlockSUM : public BLOCK {
        private:
            static int count;
        public:

            struct Properties{
                    int N_IN;
                    int N_OUT;
                    int val;
            }Properties;
            
            BlockSUM(){
                name = "SUM";
                TYPE = BLKType_Sum;
                Properties.val = 2;
                //props.OUT = 1;
            }

            virtual void Exec() override{
                cout<<"\n"<<name;
            }
            
            virtual BLOCK * Create(){
                return new BlockSUM();
            }

            
            
    };

    void BlockSUM_INIT(){
        ALL_BLOCKS_GUI[BLKType_Sum] = new BlockSUM();
    }
 
 

}