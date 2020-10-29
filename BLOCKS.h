/*
    Si desea adicionar un bloque necesita modificar : 
        enum TypeBlock_
        BLOCKS::Init()
        BLOCKS::functionNameBlock(arg 1, arg 2)
*/

#define BLOCKS_H
#define MAX_NUM_BLOCKS 100
enum TypeBlock_{
    BLKType_Default,
    BLKType_Sum,
    BLKType_Pow,
    BLKType_COUNT
};

namespace BLOCKS{

    void Init();

    void functionDefaultBlock(){}

    void functionADD(){
        cout<<"SUMA\t"<<endl;
    }



    void functionPOW(){
        cout<<"POW\t"<<endl;
    }

    namespace EVENTS{
        ImGuiID ActiveBlock;
    }
    class BLOCK {
        public:
            ImGuiID ID;
            TypeBlock_ TYPE;
            int indexType = 0;

            std::string name = "DefaultBlock";
            std::string helpText;

            bool ENABLED = false;
            bool ACTIVE  = false;

            ImVec2 posBlock  = ImVec2(250,250);
            ImVec2 sizeBlock = ImVec2(100,50);

        void Draw();
        void Exec();
    };

    

    BLOCK * ALL_BLOCKS = new BLOCK[MAX_NUM_BLOCKS];

    class BlockSUM : public BLOCK {
        private:
            static int count;
        public:
            struct Properties{
                    float val;
            }props;

            BlockSUM(){
                name = "BlockSUM";
                TYPE = BLKType_Sum;
                props.val = 1;
            }
            void Exec(){
                cout<<"\n SUMA "<< props.val <<"\t";
            }
    };

    class BlockPOW : public BLOCK {

        public:
            struct Properties{
                    float y;
            }props;

            BlockPOW(){
                name = "BlockPOW";
                TYPE = BLKType_Pow;
                props.y = 2;
            }
            void Exec(){
                cout<<"\n POW "<< props.y <<"\t";
            }
    };

    void AddBLOCK(TypeBlock_ TypeBlock);
    void DROOPBLOCK(ImGuiID ID);



}