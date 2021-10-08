BLOCKS::AddBLOCK((TypeBlock_)4);
BLOCKS::ALL_BLOCKS_GUI.back()->posBlock = ImVec2(129.000000f,155.000000f);
BLOCKS::ALL_BLOCKS_GUI.back()->sizeBlock = ImVec2(80.000000f,40.000000f);
BLOCKS::ALL_BLOCKS_GUI.back()->N_IN  = 0;
BLOCKS::ALL_BLOCKS_GUI.back()->N_OUT = 1;
BLOCKS::ALL_BLOCKS_GUI.back()->UpadateIO();

BLOCKS::AddBLOCK((TypeBlock_)5);
BLOCKS::ALL_BLOCKS_GUI.back()->posBlock = ImVec2(128.000000f,209.000000f);
BLOCKS::ALL_BLOCKS_GUI.back()->sizeBlock = ImVec2(80.000000f,40.000000f);
BLOCKS::ALL_BLOCKS_GUI.back()->N_IN  = 0;
BLOCKS::ALL_BLOCKS_GUI.back()->N_OUT = 1;
BLOCKS::ALL_BLOCKS_GUI.back()->UpadateIO();

BLOCKS::AddBLOCK((TypeBlock_)5);
BLOCKS::ALL_BLOCKS_GUI.back()->posBlock = ImVec2(127.000000f,266.000000f);
BLOCKS::ALL_BLOCKS_GUI.back()->sizeBlock = ImVec2(80.000000f,40.000000f);
BLOCKS::ALL_BLOCKS_GUI.back()->N_IN  = 0;
BLOCKS::ALL_BLOCKS_GUI.back()->N_OUT = 1;
BLOCKS::ALL_BLOCKS_GUI.back()->UpadateIO();

BLOCKS::AddBLOCK((TypeBlock_)16);
BLOCKS::ALL_BLOCKS_GUI.back()->posBlock = ImVec2(255.000000f,167.000000f);
BLOCKS::ALL_BLOCKS_GUI.back()->sizeBlock = ImVec2(100.000000f,125.000000f);
BLOCKS::ALL_BLOCKS_GUI.back()->N_IN  = 3;
BLOCKS::ALL_BLOCKS_GUI.back()->N_OUT = 1;
BLOCKS::ALL_BLOCKS_GUI.back()->UpadateIO();

BLOCKS::AddBLOCK((TypeBlock_)15);
BLOCKS::ALL_BLOCKS_GUI.back()->posBlock = ImVec2(379.000000f,168.000000f);
BLOCKS::ALL_BLOCKS_GUI.back()->sizeBlock = ImVec2(100.000000f,125.000000f);
BLOCKS::ALL_BLOCKS_GUI.back()->N_IN  = 1;
BLOCKS::ALL_BLOCKS_GUI.back()->N_OUT = 3;
BLOCKS::ALL_BLOCKS_GUI.back()->UpadateIO();

BLOCKS::AddBLOCK((TypeBlock_)6);
BLOCKS::ALL_BLOCKS_GUI.back()->posBlock = ImVec2(534.000000f,209.000000f);
BLOCKS::ALL_BLOCKS_GUI.back()->sizeBlock = ImVec2(80.000000f,40.000000f);
BLOCKS::ALL_BLOCKS_GUI.back()->N_IN  = 1;
BLOCKS::ALL_BLOCKS_GUI.back()->N_OUT = 0;
BLOCKS::ALL_BLOCKS_GUI.back()->UpadateIO();

LINES::ALL_LINES_GUI.push_back( new LINES::LINE() );
LINES::ALL_LINES_GUI.back()->posIn = 1;
LINES::ALL_LINES_GUI.back()->posOut = 1;
LINES::ALL_LINES_GUI.back()->blockOut = BLOCKS::ALL_BLOCKS_GUI[0+BLKType_COUNT];
LINES::ALL_LINES_GUI.back()->blockIn = BLOCKS::ALL_BLOCKS_GUI[3+BLKType_COUNT];
LINES::ALL_LINES_GUI.back()->blockIn->IN_ARMA[LINES::ALL_LINES_GUI.back()->posIn] = &(LINES::ALL_LINES_GUI.back()->blockOut->OUT_ARMA[LINES::ALL_LINES_GUI.back()->posOut]);

LINES::ALL_LINES_GUI.push_back( new LINES::LINE() );
LINES::ALL_LINES_GUI.back()->posIn = 2;
LINES::ALL_LINES_GUI.back()->posOut = 1;
LINES::ALL_LINES_GUI.back()->blockOut = BLOCKS::ALL_BLOCKS_GUI[1+BLKType_COUNT];
LINES::ALL_LINES_GUI.back()->blockIn = BLOCKS::ALL_BLOCKS_GUI[3+BLKType_COUNT];
LINES::ALL_LINES_GUI.back()->blockIn->IN_ARMA[LINES::ALL_LINES_GUI.back()->posIn] = &(LINES::ALL_LINES_GUI.back()->blockOut->OUT_ARMA[LINES::ALL_LINES_GUI.back()->posOut]);

LINES::ALL_LINES_GUI.push_back( new LINES::LINE() );
LINES::ALL_LINES_GUI.back()->posIn = 3;
LINES::ALL_LINES_GUI.back()->posOut = 1;
LINES::ALL_LINES_GUI.back()->blockOut = BLOCKS::ALL_BLOCKS_GUI[2+BLKType_COUNT];
LINES::ALL_LINES_GUI.back()->blockIn = BLOCKS::ALL_BLOCKS_GUI[3+BLKType_COUNT];
LINES::ALL_LINES_GUI.back()->blockIn->IN_ARMA[LINES::ALL_LINES_GUI.back()->posIn] = &(LINES::ALL_LINES_GUI.back()->blockOut->OUT_ARMA[LINES::ALL_LINES_GUI.back()->posOut]);

LINES::ALL_LINES_GUI.push_back( new LINES::LINE() );
LINES::ALL_LINES_GUI.back()->posIn = 1;
LINES::ALL_LINES_GUI.back()->posOut = 1;
LINES::ALL_LINES_GUI.back()->blockOut = BLOCKS::ALL_BLOCKS_GUI[3+BLKType_COUNT];
LINES::ALL_LINES_GUI.back()->blockIn = BLOCKS::ALL_BLOCKS_GUI[4+BLKType_COUNT];
LINES::ALL_LINES_GUI.back()->blockIn->IN_ARMA[LINES::ALL_LINES_GUI.back()->posIn] = &(LINES::ALL_LINES_GUI.back()->blockOut->OUT_ARMA[LINES::ALL_LINES_GUI.back()->posOut]);

LINES::ALL_LINES_GUI.push_back( new LINES::LINE() );
LINES::ALL_LINES_GUI.back()->posIn = 1;
LINES::ALL_LINES_GUI.back()->posOut = 2;
LINES::ALL_LINES_GUI.back()->blockOut = BLOCKS::ALL_BLOCKS_GUI[4+BLKType_COUNT];
LINES::ALL_LINES_GUI.back()->blockIn = BLOCKS::ALL_BLOCKS_GUI[5+BLKType_COUNT];
LINES::ALL_LINES_GUI.back()->blockIn->IN_ARMA[LINES::ALL_LINES_GUI.back()->posIn] = &(LINES::ALL_LINES_GUI.back()->blockOut->OUT_ARMA[LINES::ALL_LINES_GUI.back()->posOut]);