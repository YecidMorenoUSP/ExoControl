// Fun��o de controle Plataforma de rehabilita��o 2ms

void POSICIONA_J(int T){
	
	
		//Inicializa o loop
		total_time = 0;
   // int indice = 0;
		loopTime = 0;

		//ZERA OS DATALOGGERS
		printf("\nInicializando datalog.....");
		//Inicializando o vetor de datalog
    
    vet_adjust = 5;



		for (i_dt=0; i_dt<60000*vet_adjust; i_dt++){
           datalog01[i_dt] = 0.0; 
		       datalog02[i_dt] = 0.0; 
		       datalog03[i_dt] = 0.0; 
		       datalog04[i_dt] = 0.0; 
    	  	 datalog05[i_dt] = 0.0;
           datalog06[i_dt] = 0.0;
           datalog07[i_dt] = 0.0;
           datalog08[i_dt] = 0.0;
           datalog09[i_dt] = 0.0;
           datalog10[i_dt] = 0.0;
		       datalog11[i_dt] = 0.0; 
		       datalog12[i_dt] = 0.0; 
		       datalog13[i_dt] = 0.0; 
		       datalog14[i_dt] = 0.0; 
		       datalog15[i_dt] = 0.0;
           datalog16[i_dt] = 0.0;
           datalog17[i_dt] = 0.0;
           datalog18[i_dt] = 0.0;
           datalog19[i_dt] = 0.0;
           datalog20[i_dt] = 0.0;
           datalog21[i_dt] = 0.0;
           datalog22[i_dt] = 0.0;
           datalog23[i_dt] = 0.0;
           datalog24[i_dt] = 0.0;
           datalog25[i_dt] = 0.0;
           datalog26[i_dt] = 0.0;
           datalog27[i_dt] = 0.0;
           datalog28[i_dt] = 0.0;
           datalog29[i_dt] = 0.0;
           datalog30[i_dt] = 0.0;
           datalog31[i_dt] = 0.0;
           datalog32[i_dt] = 0.0;
           datalog33[i_dt] = 0.0;
           datalog34[i_dt] = 0.0;
           datalog35[i_dt] = 0.0;
           datalog36[i_dt] = 0.0;
           datalog37[i_dt] = 0.0;
           datalog38[i_dt] = 0.0;
            datalog39[i_dt] = 0.0;
           datalog40[i_dt] = 0.0;
           datalog41[i_dt] = 0.0;
           datalog42[i_dt] = 0.0;
           datalog43[i_dt] = 0.0;
           datalog44[i_dt] = 0.0;
           datalog45[i_dt] = 0.0;
           datalog46[i_dt] = 0.0;
           datalog47[i_dt] = 0.0;
           datalog48[i_dt] = 0.0;
           datalog49[i_dt] = 0.0;
           datalog50[i_dt] = 0.0;
           datalog51[i_dt] = 0.0;
           datalog52[i_dt] = 0.0;
           datalog53[i_dt] = 0.0;
           datalog54[i_dt] = 0.0;
           datalog55[i_dt] = 0.0;
           datalog56[i_dt] = 0.0;
           datalog57[i_dt] = 0.0;
           datalog58[i_dt] = 0.0;
        }
        i_dt = 0;

    memset( Af, 0, 7 * sizeof(double) );
    memset( Bf, 0, 7 * sizeof(double) );
    memset( force, 0, 7 * sizeof(double) );
    memset( force_f, 0, 7 * sizeof(double) );
    memset( error_f, 0, 7 * sizeof(double) );
    memset( control_PD, 0, 7 * sizeof(double) );
    memset( tension, 0, 7 * sizeof(double) );
    memset( dot_force, 0, 2 * sizeof(double) );
    memset( filt_dot_force, 0, 2 * sizeof(double) );
    memset( int_force_error, 0, 2 * sizeof(double) );
    memset( filtro_modo, 0, 22 * sizeof(double) );
    memset( filtro_Tau_h, 0, 22 * sizeof(double) );
    




    /////////////// DECLARACION MATRIZES MARKOVIANO /////////

    mat LKP,L,K,X,Cref,I3,Kref,Mnum;
    mat L_kalman,C_kalman,Y_kalman;
    double alpha,mu,beta;
    int Nk=15000/4;

    

    cube Fk(4,4,3);
    
    mat Fk_1;
    Fk_1.zeros(4,4);

    Fk_1(0,0) =  0.016313941052918;
    Fk_1(1,0) =  0.000488510367508;
    Fk_1(2,0) = -0.000000050886497;
    Fk_1(3,0) = -0.000000752989061;

    Fk_1(0,1) = -4.318501501849671;
    Fk_1(1,1) = 0.993343469026164;
    Fk_1(2,1) = 0.000000693388643;
    Fk_1(3,1) = -0.001994502043676;

    Fk_1(0,2) = 0;
    Fk_1(1,2) = 0;
    Fk_1(2,2) = 1;
    Fk_1(3,2) = 0;

    Fk_1(0,3) = 0;
    Fk_1(1,3) = 0;
    Fk_1(2,3) = 0;
    Fk_1(3,3) = 1;


    Fk.slice(0) = Fk_1;

    mat Fk_2;
    Fk_2.zeros(4,4);
    
    Fk_2(0,0) =  0.799430491833627 ;
    Fk_2(1,0) =  0.001796532507281;
    Fk_2(2,0) = -0.000000187138803;
    Fk_2(3,0) = -0.000001863399284;

    Fk_2(0,1) = -12.282984664612931;
    Fk_2(1,1) =  0.987259843763329;
    Fk_2(2,1) =  0.000001327099608;
    Fk_2(3,1) = -0.001991352850606;

    Fk_2(0,2) = 0;
    Fk_2(1,2) = 0;
    Fk_2(2,2) = 1;
    Fk_2(3,2) = 0;

    Fk_2(0,3) = 0;
    Fk_2(1,3) = 0;
    Fk_2(2,3) = 0;
    Fk_2(3,3) = 1;

    Fk.slice(1) = Fk_2;


    mat Fk_3;
    Fk_3.zeros(4,4);
    
    Fk_3(0,0) =   0.663101913644911;
    Fk_3(1,0) =   0.001650422455473;
    Fk_3(2,0) =  -0.000000171919006;
    Fk_3(3,0) =  -0.000001762677493;

    Fk_3(0,1) = -25.242691627974363;
    Fk_3(1,1) =  0.973040402935565;
    Fk_3(2,1) =  0.000002808291361;
    Fk_3(3,1) = -0.001981441702912;

    Fk_3(0,2) = 0;
    Fk_3(1,2) = 0;
    Fk_3(2,2) = 1;
    Fk_3(3,2) = 0;

    Fk_3(0,3) = 0;
    Fk_3(1,3) = 0;
    Fk_3(2,3) = 0;
    Fk_3(3,3) = 1;

    Fk.slice(2) = Fk_3;

    
    cube Bk(4,1,3);
    
    mat Bk_1,Bk_2,Bk_3;
    
    Bk_1.zeros(4,1);
    Bk_1(0,0) = 62.199631569473361 ;
    Bk_1(1,0) =  0.095874407806971;
    Bk_1(2,0) =  0.000003275994444;
    Bk_1(3,0) = -0.000079187388866;
    Bk.slice(0) = Bk_1;
    
    Bk_2.zeros(4,1);
    Bk_2(0,0) = 11.957587926943695;
    Bk_2(1,0) = 0.012402648262021;
    Bk_2(2,0) = 0.000011970969397;
    Bk_2(3,0) = -0.000008418071993;
    Bk.slice(1) = Bk_2;
    

    Bk_3.zeros(4,1);
    Bk_3(0,0) =19.731297050016813 ;
    Bk_3(1,0) =0.021073339795413 ;
    Bk_3(2,0) =0.000011067772362 ;
    Bk_3(3,0) = -0.000014506348134;
    Bk.slice(2) = Bk_3;


    cube Ef(1,4,3);
    mat Ef_1, Ef_2, Ef_3;
    
    Ef_1.zeros(1,4);
    Ef_1(0,0) = -0.3;     // derivada fuerza
    Ef_1(0,1) = -99.2;    // fuerza     
    Ef_1(0,2) = 0;        // theta carga
    Ef_1(0,3) = 2616;     // integral error fuerza
    Ef.slice(0) = Ef_1;


    
    Ef_2.zeros(1,4);
    Ef_2(0,0) = -0.6*0.01*100;      // derivada fuerza
    Ef_2(0,1) = -99.2*5;            // fuerza  
    Ef_2(0,2) = 108*1.2;            // theta carga
    Ef_2(0,3) = 6673*0.5*2*0.8*0.9; //  integral error fuerza
    Ef.slice(1) = Ef_2;

    Ef_3.zeros(1,4);
    Ef_3(0,0) = -0.2*5*4;//4// 0.2*5*2 mejor  //-0.2*5*0.01 full // derivada fuerza -0.6 *0.1   5 10
    Ef_3(0,1) = -31.8*15;//18 //20  //26           // fuerza  2.3 2.7   6 10 8   7 8  4  6 10
    Ef_3(0,2) = 57*0.1*5*4*16;//20 //16      //0.5       // theta carga    2.  2.5 0.7  0.3     -57*0.1 kv grande //hay que probar un punto intermedio aqui  vamos aqui -57*0.1*5*  16  32 64
    Ef_3(0,3) = 6673*1;//0.5 //1  //0.9       //  integral error fuerza 6673*0.5  0.4  0.35 0.4 0.3 0.1  0.1 0.7
    Ef.slice(2) = Ef_3;
   

    cube Eb(1,1,3);
    mat Eb_1, Eb_2, Eb_3;
    
    Eb_1.zeros(1,1);
    Eb_1(0,0) =  -118.6592140461666;
    Eb.slice(0) = Eb_1;

    Eb_2.zeros(1,1);
    Eb_2(0,0) =  -59.329607023083298;
    Eb.slice(1) = Eb_2;

    Eb_3.zeros(1,1);
    Eb_3(0,0) =  -47.463685618466641*0.6*5;//4 //-59.329607023083298;//0.8   1.2  2
    Eb.slice(2) = Eb_3;

    
    cube Hk(4,1,3);
    mat Hk_1,Hk_2,Hk_3;

    Hk_1.zeros(4,1);
    Hk_1(0,0) = -1187.7;
    Hk_1(1,0) = -10.3;    
    Hk_1(2,0) = 1e5;
    Hk_1(3,0) = 10;
    Hk_1 = Hk_1*0.0001;
    Hk.slice(0) = Hk_1;



     Hk_2.zeros(4,1);
    Hk_2(0,0) = -0.0594;
    Hk_2(1,0) = -0.0005;
    Hk_2(2,0) = 5;
    Hk_2(3,0) = 0.0005;
    Hk.slice(1) = Hk_2;

    Hk_3.zeros(4,1);
    Hk_3(0,0) = -0.0594;
    Hk_3(1,0) = -0.0005;
    Hk_3(2,0) = 5;
    Hk_3(3,0) = 0.0005;
    Hk.slice(2) = Hk_3;


    cube P(16,Nk,3);
    mat P_1, P_slice0_mat, P_2, P_slice1_mat, P_3, P_slice2_mat;
    P_slice0_mat.zeros(16,Nk);
    P_slice1_mat.zeros(16,Nk);
    P_slice2_mat.zeros(16,Nk);

    P_1.zeros(16,1);
    P_1(0,0) = 1e10;
    P_1(1,0) = 0;
    P_1(2,0) = 0;
    P_1(3,0) = 0;
    

    P_1(4,0) = 0;
    P_1(5,0) = 1e10;
    P_1(6,0) = 0;
    P_1(7,0) = 0;
   
    
    P_1(8,0) = 0;
    P_1(9,0) = 0;
    P_1(10,0) = 1e10;
    P_1(11,0) = 0;
    
    
    P_1(12,0) = 0;
    P_1(13,0) = 0;
    P_1(14,0) = 0;
    P_1(15,0) = 1e10;
    

    
    
    P_slice0_mat.submat(0,0,15,0) = P_1;
    P.slice(0) = P_slice0_mat; 
    //submat( first_row, first_col, last_row, last_col )
    
    P_2.zeros(16,1);
 
    P_2(0,0) = 1e10;
    P_2(1,0) = 0;
    P_2(2,0) = 0;
    P_2(3,0) = 0;
    

    P_2(4,0) = 0;
    P_2(5,0) = 1e10;
    P_2(6,0) = 0;
    P_2(7,0) = 0;
   
    
    P_2(8,0) = 0;
    P_2(9,0) = 0;
    P_2(10,0) = 1e10;
    P_2(11,0) = 0;
    
    
    P_2(12,0) = 0;
    P_2(13,0) = 0;
    P_2(14,0) = 0;
    P_2(15,0) = 1e10;
    



    P_slice1_mat.submat(0,0,15,0) = P_2;
    P.slice(1) = P_slice1_mat; 

    P_3.zeros(16,1);


 
    P_3(0,0) = 1e10;
    P_3(1,0) = 0;
    P_3(2,0) = 0;
    P_3(3,0) = 0;
    

    P_3(4,0) = 0;
    P_3(5,0) = 1e10;
    P_3(6,0) = 0;
    P_3(7,0) = 0;
   
    
    P_3(8,0) = 0;
    P_3(9,0) = 0;
    P_3(10,0) = 1e10;
    P_3(11,0) = 0;
    
    
    P_3(12,0) = 0;
    P_3(13,0) = 0;
    P_3(14,0) = 0;
    P_3(15,0) = 1e10;
    


    
    P_slice2_mat.submat(0,0,15,0) = P_3;
    P.slice(2) = P_slice2_mat;


    
    mat columnas,filas,matrices;

    cube Q(4,4,3);
    mat Q_1,Q_2,Q_3;

    Q_1.eye(4,4);
    Q.slice(0) = Q_1;

    Q_2.eye(4,4);
    Q.slice(1) = Q_2;
    
    Q_3.eye(4,4);
    Q.slice(2) = Q_3;

    
    cube R(1,1,3);
    mat R_1,R_2,R_3;

    R_1.zeros(1,1);
    R_1(0,0) = 1;
    R.slice(0) = R_1;

    R_2.zeros(1,1);
    R_2(0,0) = 1;
    R.slice(1) = R_2;

    R_3.zeros(1,1);
    R_3(0,0) = 1;
    R.slice(2) = R_3;
    


    cube M(1,4,3);
    mat M_1,M_2,M_3;

    M_1.zeros(1,4);
    M.slice(0) = M_1;

    M_2.zeros(1,4);
    M.slice(1) = M_2;

    M_3.zeros(1,4);
    M.slice(2) = M_3;
    
    int s = 3;

    mat prob;
    prob.zeros(3,3);
    

    prob(0,0) = 0.99;   prob(0,1) = 0.01;   prob(0,2) = 0.000; // 
    prob(1,0) = 0.00;   prob(1,1) = 0.60;   prob(1,2) = 0.400; // 
    prob(2,0) = 0.00;   prob(2,1) = 0.40;   prob(2,2) = 0.600; // 


   

    L.zeros(4,4);
    K.zeros(1,4);
    
    X.zeros(4,1);



    ///////////////  MARKOVIANO //////////////////
    
    
      field<cube> RLQR(3,1);
      cube RLQR_Pr(16,Nk,3);
      cube RLQR_Kr(4,Nk,3);
      cube RLQR_Lr(16,Nk,3);
      
      mat RLQR_Pr_mat_modo1, RLQR_Pr_mat_modo2, RLQR_Pr_mat_modo3;
      mat RLQR_Kr_mat_modo1, RLQR_Kr_mat_modo2, RLQR_Kr_mat_modo3;
      mat RLQR_Lr_mat_modo1, RLQR_Lr_mat_modo2, RLQR_Lr_mat_modo3;
      
      RLQR_Pr_mat_modo1.zeros(16,Nk);
      RLQR_Pr_mat_modo2.zeros(16,Nk);
      RLQR_Pr_mat_modo3.zeros(16,Nk);
      
      RLQR_Kr_mat_modo1.zeros(4,Nk);
      RLQR_Kr_mat_modo2.zeros(4,Nk);
      RLQR_Kr_mat_modo3.zeros(4,Nk);

      RLQR_Lr_mat_modo1.zeros(16,Nk);
      RLQR_Lr_mat_modo2.zeros(16,Nk);
      RLQR_Lr_mat_modo3.zeros(16,Nk);


      RLQR = rlqr_slsm(Fk, Ef, Bk, Eb, Hk, P, Q, R, M, s, prob, Nk);
      
      RLQR_Pr = RLQR(0,0);
      RLQR_Kr = RLQR(1,0);
      RLQR_Lr = RLQR(2,0);

      RLQR_Pr_mat_modo1 = RLQR_Pr.slice(0);
      RLQR_Pr_mat_modo1.save("Pr_modo1.dat", raw_ascii);

      RLQR_Pr_mat_modo2 = RLQR_Pr.slice(1);
      RLQR_Pr_mat_modo2.save("Pr_modo2.dat", raw_ascii);

      RLQR_Pr_mat_modo3 = RLQR_Pr.slice(2);
      RLQR_Pr_mat_modo3.save("Pr_modo3.dat", raw_ascii);



      RLQR_Kr_mat_modo1 = RLQR_Kr.slice(0);
      RLQR_Kr_mat_modo1.save("Kr_modo1.dat", raw_ascii);

      RLQR_Kr_mat_modo2 = RLQR_Kr.slice(1);
      RLQR_Kr_mat_modo2.save("Kr_modo2.dat", raw_ascii);

      RLQR_Kr_mat_modo3 = RLQR_Kr.slice(2);
      RLQR_Kr_mat_modo3.save("Kr_modo3.dat", raw_ascii);

      RLQR_Lr_mat_modo1 = RLQR_Lr.slice(0);
      RLQR_Lr_mat_modo1.save("Lr_modo1.dat", raw_ascii);

      RLQR_Lr_mat_modo2 = RLQR_Lr.slice(1);
      RLQR_Lr_mat_modo2.save("Lr_modo2.dat", raw_ascii);

      RLQR_Lr_mat_modo3 = RLQR_Lr.slice(2);
      RLQR_Lr_mat_modo3.save("Lr_modo3.dat", raw_ascii);


      
      mat K1a, K2a, K3a;
      mat K1,  K2,  K3;

      K1a = RLQR_Kr_mat_modo1.submat(0,Nk-2,3,Nk-2);
      K2a = RLQR_Kr_mat_modo2.submat(0,Nk-2,3,Nk-2);
      K3a = RLQR_Kr_mat_modo3.submat(0,Nk-2,3,Nk-2);

      K1 = K1a.t();
      K1.save("K1.dat", raw_ascii);
      
      K2 = K2a.t();
      K2.save("K2.dat", raw_ascii);

      K3 = K3a.t();
      K3.save("K3.dat", raw_ascii);

      double modo = 0.0;
      int modo = 0, modov = 0;


      //////////////// FINAL MARKOVIANO ////////////////////


   
     /////////////////////////////////////////////
    /////// DECLARACION VARIABLES RKF MARKOV///////////

   // mat  R_f, Q_f, G_f, Ef_f, Eg_f, Ec_f, Ed_f, C_f, D_f, B_f, Eb_f, xest, y, u1, M_f, N_f;
   mat  R_f, Q_f, xest, y, u1;
    double mu_f, alpha_f;
    

    cube P_f(2,2,3);

    mat P_f1;
    P_f1.eye(2,2);
    P_f1 = 1e15*P_f1;
    P_f.slice(0) = P_f1;

    mat P_f2;
    P_f2.eye(2,2);
    P_f2 = 1e15*P_f2;
    P_f.slice(1) = P_f2;

    mat P_f3;
    P_f3.eye(2,2);
    P_f3 = 1e15*P_f3;
    P_f.slice(2) = P_f3;

    


    R_f.eye(1,1);
    R_f=0.1*R_f;

    Q_f.eye(2,2);
    Q_f(0,0) = 1 ;
    Q_f(1,1) = 1*1;
    

    cube F_f(2,2,3);
    
    mat F_f1;
    F_f1.zeros(2,2);

    F_f1(0,0)=Fk_1(0,0);
    F_f1(0,1)=Fk_1(0,1);
    F_f1(1,0)=Fk_1(1,0);
    F_f1(1,1)=Fk_1(1,1);
    
    F_f.slice(0) = F_f1;


    mat F_f2;
    F_f2.zeros(2,2);

    F_f2(0,0)=Fk_2(0,0);
    F_f2(0,1)=Fk_2(0,1);
    F_f2(1,0)=Fk_2(1,0);
    F_f2(1,1)=Fk_2(1,1);
    
    F_f.slice(1) = F_f2;


    mat F_f3;
    F_f3.zeros(2,2);

    F_f3(0,0)=Fk_3(0,0);
    F_f3(0,1)=Fk_3(0,1);
    F_f3(1,0)=Fk_3(1,0);
    F_f3(1,1)=Fk_3(1,1);
    
    F_f.slice(2) = F_f3;



    cube G_f(2,2,3);
    
    mat G_f1;
    G_f1.zeros(2,2);


  

    G_f1(0,0) = 0.0937915519811;
    G_f1(1,0) = 0.0001445701410;

    G_f1(0,1) = 248.7898186342412;
    G_f1(1,1) = 0.3834842092806;

    G_f.slice(0) = G_f1;

    mat G_f2;
    G_f2.zeros(2,2);

    G_f2(0,0) = 212.1366798264865;
    G_f2(1,0) = 0.2200323877554;

 
    G_f2(0,1) = 281.3550100457339;
    G_f2(1,1) = 0.2918270179299;

    G_f.slice(1) = G_f2;
    
    mat G_f3;
    G_f3.zeros(2,2);

    G_f3(0,0) = 743.8523742975691;
    G_f3(1,0) = 0.7944461938544;


    G_f3(0,1) = 98.6564852500840;
    G_f3(1,1) = 0.1053666989771;

    G_f.slice(2) = G_f3;
    


    cube Eg_f(1,2,3);
    
    mat Eg_f1;
    Eg_f1.zeros(1,2);

    Eg_f1(0,0)=-118000;
    Eg_f1(0,1)=-118000;
     
    Eg_f.slice(0) = Eg_f1;


    mat Eg_f2;
    Eg_f2.zeros(1,2);

    Eg_f2(0,0)=-59300;
    Eg_f2(0,1)=-59300;
     
    Eg_f.slice(1) = Eg_f2;


    mat Eg_f3;
    Eg_f3.zeros(1,2);

    Eg_f3(0,0)=-47460;
    Eg_f3(0,1)=-47460;
     
    Eg_f.slice(2) = Eg_f3;


    cube Ec_f(1,2,3);
    
    mat Ec_f1;
    Ec_f1.zeros(1,2);
    Ec_f.slice(0) = Ec_f1;


    mat Ec_f2;
    Ec_f2.zeros(1,2);
    Ec_f.slice(1) = Ec_f2;


    mat Ec_f3;
    Ec_f3.zeros(1,2);
    Ec_f.slice(2) = Ec_f3;


    cube Ed_f(1,1,3);
    
    mat Ed_f1;
    Ed_f1.zeros(1,1);
    Ed_f.slice(0) = Ed_f1;


    mat Ed_f2;
    Ed_f2.zeros(1,1);
    Ed_f.slice(1) = Ed_f2;

    mat Ed_f3;
    Ed_f3.zeros(1,1);
    Ed_f.slice(2) = Ed_f3;

  
    cube Ef_f(1,2,3);

    mat Ef_f1;
    Ef_f1.zeros(1,2);
    Ef_f1(0,0)=Ef_1(0,0);
    Ef_f1(0,1)=Ef_1(0,1);

    Ef_f.slice(0) = Ef_f1;

    mat Ef_f2;
    Ef_f2.zeros(1,2);
    Ef_f2(0,0)=Ef_2(0,0);
    Ef_f2(0,1)=Ef_2(0,1);

    Ef_f.slice(1) = Ef_f2;

    mat Ef_f3;
    Ef_f3.zeros(1,2);
    Ef_f3(0,0)=Ef_3(0,0);
    Ef_f3(0,1)=Ef_3(0,1);

    Ef_f.slice(2) = Ef_f3;

   cube C_f(1,2,3);

    mat C_f1;
    C_f1.zeros(1,2);
    C_f1(0,1)=1;

    C_f.slice(0) = C_f1;

    C_f.slice(1) = C_f1;

    C_f.slice(2) = C_f1;


    
    cube D_f(1,1,3);

    mat D_f1;
    D_f1.eye(1,1);
    D_f.slice(0) = D_f1;
    D_f.slice(1) = D_f1;  
    D_f.slice(2) = D_f1;



   cube B_f(2,1,3);

    mat B_f1;
    B_f1.zeros(2,1);
    B_f1(0,0)=54.970289073749612;
    B_f1(1,0)=0.036116275747391;  
    B_f.slice(0) = B_f1;

    mat B_f2;
    B_f2.zeros(2,1);
    B_f2(0,0)=6.312602030986299;
    B_f2(1,0)=0.003213133195749;  
    B_f.slice(1) = B_f2;

    mat B_f3;
    B_f3.zeros(2,1);
    B_f3(0,0)=10.872081142022878;
    B_f3(1,0)=0.005613321525887;  
    B_f.slice(2) = B_f3;



    cube Eb_f(1,1,3);
    Eb_f.slice(0) = Eb_1;
    Eb_f.slice(1) = Eb_2;
    Eb_f.slice(2) = Eb_3;
   


              

    xest.zeros(2,1);

    y.zeros(1,1);

    u1.zeros(1,1);

    


    cube M_f(2,1,3);

    mat M_f1;
    M_f1.zeros(2,1);
    M_f1(0,0)=Hk_1(0,0)*10000;
    M_f1(1,0)=Hk_1(1,0)*10000;
    M_f.slice(0) = M_f1;

    mat M_f2;
    M_f2.zeros(2,1);
    M_f2(0,0)=Hk_2(0,0)*10000/10000;
    M_f2(1,0)=Hk_2(1,0)*10000/10000;
    M_f.slice(1) = M_f2;

    mat M_f3;
    M_f3.zeros(2,1);
    M_f3(0,0)=Hk_3(0,0)*10000/10000;
    M_f3(1,0)=Hk_3(1,0)*10000/10000;
    M_f.slice(2) = M_f3;



    cube N_f(1,1,3);
    mat N_f1;
    N_f1.eye(1,1);
    N_f.slice(0) = N_f1;
    N_f.slice(1) = N_f1;
    N_f.slice(2) = N_f1;


    mu_f = 1e10;
    alpha_f = 2;

    

      cube  LPPr;
         

   int npf = D_f1.n_rows;
   int mkf = D_f1.n_cols;
   int nxf = G_f1.n_rows;
   int muf = G_f1.n_cols;
   int nrf = Eg_f1.n_rows;
   mat xk, xk1, Pk;
   cube Pk1;

   
field<cube> LPr_campo(4,1);
//CAMPO1(0,0) = xkf;
    /////////////////////////////////////////////////////////////////////////////
    /////  Convergencia de riccati  /////////////////////////////
      //re_sul
//CAMPO1(1,0) = xk1f;
//CAMPO1(2,0) = Pkf;
//CAMPO1(3,0) = Pk1f;

  // LPPr.zeros(nxf,nxf+1);  //nx,nx+1

   Pk1=P_f;


   

   for(int cont_est=0;cont_est<7500;cont_est++){

    LPr_campo= rkf_slsm(Pk1,R_f,Q_f,F_f,G_f,Ef_f,Eg_f,Ec_f,Ed_f,C_f,D_f,B_f,Eb_f,xest,y,u1,M_f,N_f,mu_f,alpha_f,s,prob,s+1);
    Pk1=LPr_campo(3,0);

    }

 

   Beep(440,500); //  hertz (C5) for 500 milliseconds     
   Beep(440,500); //  hertz (C5) for 500 milliseconds     
   Beep(523,1000); //  hertz (C5) for 500 milliseconds     

  // juego(theta_d,theta_d*0.2); //esta se ventana puede mandar por ejemplo 
                                 //antes de calcular los controles  
	                             //incluso con instrucciones del juego

                               //DEBE IR EN OTRO  LA DO PERO AHUN NO SE EN DONE


   //////////////////dados kalman nominal  fc=0.01Hz////////////////////////////////
             
    mat A_f2;
    A_f2.zeros(4,4);

    A_f2(0,0)=0.999920001999973;
    A_f2(1,0)=0.000062497500042;
    A_f2(2,0)=0.000000000976536;
    A_f2(3,0)=0.000000000000003;
    
    A_f2(0,1)=-0.000038398720019;
    A_f2(1,1)=0.999999998800027;
    A_f2(2,1)=0.000031249999988;
    A_f2(3,1)=0.000000000122070;

    A_f2(0,2)= -0.000016383385610;
    A_f2(1,2)=-0.000000000511987;
    A_f2(2,2)=0.999999999999995;
    A_f2(3,2)=0.000007812500000 ;

    A_f2(0,3)=-0.000010485340577;
    A_f2(1,3)=-0.000000000327671;
    A_f2(2,3)= -0.000000000000003;
    A_f2(3,3)=1;

    mat B_ff2;
    B_ff2.zeros(4,1);

    B_ff2(0,0)=0.000124995000083332;
    B_ff2(1,0)=0.000000003906145835;
    B_ff2(2,0)=0.000000000000040689;
    B_ff2(3,0)=0;
    
    

    mat C_ff2;
    C_ff2.zeros(1,4);

    C_ff2(0,0)=0;
    C_ff2(0,1)=0;
    C_ff2(0,2)=0;
    C_ff2(0,3)=0.08388608000000;


    mat L_f2;
    L_f2.zeros(4,1);

    L_f2(0,0)=  7.639229067423566;
    L_f2(1,0)= 10.056132155241448 ;
    L_f2(2,0)=  2.179062351700384;
    L_f2(3,0)=  0.064956631607747;

    mat F_est2k1;
    F_est2k1.zeros(4,1);

    mat F_est2k;
    F_est2k.zeros(4,1);

     mat F_est2k1_Th;
    F_est2k1_Th.zeros(4,1);

    mat F_est2k_Th;
    F_est2k_Th.zeros(4,1);

    mat F_est2k1_emg1;
    F_est2k1_emg1.zeros(4,1);

    mat F_est2k1_emg2;
    F_est2k1_emg2.zeros(4,1);

    mat F_est2k_emg1;
    F_est2k_emg1.zeros(4,1);

    mat F_est2k_emg2;
    F_est2k_emg2.zeros(4,1);


   //////////////////dados kalman nominal  sensor de velocidad////////////////////////////////
             
    mat A_f2b;
    A_f2b.zeros(4,4);

    A_f2b(0,0)=0.4031;
    A_f2b(1,0)=0.3466;
    A_f2b(2,0)=0.0509;
    A_f2b(3,0)=0.0023;
    
    A_f2b(0,1)=-0.3025;
    A_f2b(1,1)=0.9135;
    A_f2b(2,1)=0.2482;
    A_f2b(3,1)=0.0161;

    A_f2b(0,2)=-0.1421;
    A_f2b(1,2)=-0.0413;
    A_f2b(2,2)=0.9963;
    A_f2b(3,2)=0.1279;

    A_f2b(0,3)=-0.0509;
    A_f2b(1,3)=-0.015;
    A_f2b(2,3)=-0.0014;
    A_f2b(3,3)=1;

    mat B_ff2b;
    B_ff2b.zeros(4,1);

    B_ff2b(0,0)=0;
    B_ff2b(1,0)=0;
    B_ff2b(2,0)=0;
    B_ff2b(3,0)=0;
    
    

    mat C_ff2b;
    C_ff2b.zeros(1,4);

    C_ff2b(0,0)=0;
    C_ff2b(0,1)=0;
    C_ff2b(0,2)=0;
    C_ff2b(0,3)=4.7029;


    
  
   
   

    mat L_f2b;
    L_f2b.zeros(4,1);

    L_f2b(0,0)= -0.0008 ;
    L_f2b(1,0)= -0.0073;
    L_f2b(2,0)= 0.0065 ;
    L_f2b(3,0)= 0.0217 ;

    mat omega_est2k1;
    omega_est2k1.zeros(4,1);

    mat omega_est2k;
    omega_est2k.zeros(4,1);



//////////////////////////////////////////////////////////////////////////////////////////////////////////
      /*
       printf("\n");
        Pk1.print();

        int num1juti;
          printf("Please insert any number and enter to finish: ");
          scanf("%d", &num1juti);
       */   

    set_ref = false;


    window.setFramerateLimit(4000);

         ///////////////////////////////////////////////////////////////////////////////////////////
     //-----------------ACA VA EL DO (LOOP) Y LAS RUTINAS DE CONTROL----------------------------
   
    // sf::Clock clock;						 //esto se debe colocar antes del do LOOP DE CONTROL
    //LOOP DE EXECU��O de 1 ms
		do{

        

			//CALCULA O TEMPO M�XIMO DE EXECU��O DO LOOP
			QueryPerformanceCounter(&tick_before);
			final_time = tick_before.QuadPart + 1*ticksSampleTime;

			//Incrementa o loop time
			loopTime += 1;

			eixo_motor.ReadPDO01();
			Im = eixo_motor.PDOgetActualCurrent();

      eixo_motor.ReadPDO02();
			omega_m = eixo_motor.PDOgetActualVelocity();
        
       // definir tiempo de muestreo -- cuando se cambie sample time  tambien hacerlo en los setpoints de matlab
      
      /////////////////////////////////////////////////////////////////////

			if (set_ref == false){
              endwait = clock () + .5 * CLOCKS_PER_SEC;
              while (clock() < endwait) {
              eixo_motor.ReadPDO02();
              refTension = (eixo_motor.PDOgetAnalogValue_01() + eixo_motor.PDOgetAnalogValue_02())/2; // mV
              }

              eixo_motor.ReadPDO02();
              refTension = (eixo_motor.PDOgetAnalogValue_01() + eixo_motor.PDOgetAnalogValue_02())/2; // mV

              eixo_motor.ReadPDO01();
              ZERO_02 = eixo_motor.PDOgetActualPosition();
              refPosition = ( p1*pow(refTension,7) + p2*pow(refTension,6) + p3*pow(refTension,5) + p4*pow(refTension,4) + p5*pow(refTension,3) + p6*pow(refTension,2) + p7*refTension + p8 )/1000;	// m	

              eixo_emg.ReadPDO01();
              ZERO_03 = eixo_emg.PDOgetActualPosition();
            
              set_ref = true;
			}

      // lectura analogia EMG
      eixo_emg.ReadPDO02();
			emg_signal1 = eixo_emg.PDOgetAnalogValue_01();
      emg_signal2 = eixo_emg.PDOgetAnalogValue_02(); // mV
      

      emg_abs1= abs(emg_signal1 -2200)/1000;   //hay que cambiar el potenciometro  y quitar el por 1 2600
      emg_abs2= abs(emg_signal2 -2200)/1000;  //2600

      
      eixo_motor.ReadPDO02();
			analogSamples = (eixo_motor.PDOgetAnalogValue_01() + eixo_motor.PDOgetAnalogValue_02())/2; // mV
      tension[0] = analogSamples;
			//tensionf = (tension[0] + tension[1] + tension[2] + tension[3] + tension[4] + tension[5])/6; // mV
			tensionf1 = tension[0]; // mV


      //---------------------------- FILTRO IIR CHEBIS. TYPE I 3th Or. Fs = 1000 Hz - Fc = 10 Hz E_inf = 0.1dB--------------------------------------//
      
      Af[0] = 1; Af[1] = -2.9213; Af[2] = 2.8497; Af[3] = -0.9282;  Af[4] = 0; Af[5] = 0.0; Af[6] = 0.0;
      Bf[0] = 0.00002537; Bf[1] = 0.00007611; Bf[2] = 0.00007611; Bf[3] = 0.00002537;  Bf[4] = 0;  Bf[5] = 0.0;  Bf[6] = 0.0;
      
      tension_f[0] = - Af[1]*tension_f[1] - Af[2]*tension_f[2] - Af[3]*tension_f[3] - Af[4]*tension_f[4] - Af[5]*tension_f[5] - Af[6]*tension_f[6] +
                     Bf[0]*tension[0] + Bf[1]*tension[1] + Bf[2]*tension[2] + Bf[3]*tension[3] + Bf[4]*tension[4] + Bf[5]*tension[5] + Bf[6]*tension[6];

      //------------------------------------------------------------------------------------------------------------------------------------------//
      
			//position = ( p1*pow(tensionf,7) + p2*pow(tensionf,6) + p3*pow(tensionf,5) + p4*pow(tensionf,4)+ p5*pow(tensionf,3)+ p6*pow(tensionf,2)+ p7*tensionf + p8 )/1000;	// m
			position = ( p1*pow(tension_f[0],7) + p2*pow(tension_f[0],6) + p3*pow(tension_f[0],5) + p4*pow(tension_f[0],4)+ p5*pow(tension_f[0],3)+ p6*pow(tension_f[0],2)+ p7*tension_f[0] + p8 )/1000;	// m
			position1 = ( p1*pow(tensionf1,7) + p2*pow(tensionf1,6) + p3*pow(tensionf1,5) + p4*pow(tensionf1,4)+ p5*pow(tensionf1,3)+ p6*pow(tensionf1,2)+ p7*tensionf1 + p8 )/1000;	// m
			//positionf = ( p1*pow(tension_ff,7) + p2*pow(tension_ff,6) + p3*pow(tension_ff,5) + p4*pow(tension_ff,4) + p5*pow(tension_ff,3) + p6*pow(tension_ff,2) + p7*tension_ff + p8 )/1000;	// m
      
			Fl  = -kmola_aesc * ( refPosition - position ); // N filtrada con media movil
      Fl1 = -kmola_aesc * ( refPosition - position1 ); // N sin filtro
      //Flf = -kmola_aesc * ( refPosition - positionf ); // N con filtro IIR

      printf("\n Fuerza en lk carga: %.4f      Tiempo: %d", Fl1, int(SAMPLE_TIME*double(total_time)));

      ///////
      eixo_motor.ReadPDO01();
			//encoder = eixo_motor.PDOgetActualPosition(); // sin zerar
      encoder = eixo_motor.PDOgetActualPosition()-ZERO_02; // zerando


      theta_m = (double(encoder)/4096)*2*3.1416; // theta_m en rad


      //////
      eixo_emg.ReadPDO01();
			encoder_emg = eixo_emg.PDOgetActualPosition()-ZERO_03; 
      theta_l_emg = -(double(encoder_emg)/2048)*2*3.1416; // theta_m en rad

      eixo_emg.ReadPDO02();
      encoder_emg2=eixo_emg.PDOgetActualVelocity();

			//omega_emg =    -(double(encoder_emg2)/60 )*2*3.1416; //rad




      // calculo del angulo Ver 2.0

      Xll = (passo*(double(encoder)/4096)/2) - ( refPosition - position1 ); // P*theta_m/2*pi*N - Deltax
      
      //Xll_a = (passo*(double(encoder)/4096)/2);
      //Xll_b = ( refPosition - position1 ); 
      //Xll = (passo*(double(encoder)/1024)/(2*3.1416*2)) - ( refPosition - position ); // P*theta_m/2*pi*N - Deltax

      //position1 --> sem filtro ; position --> filtro com media movil; positionf --> filtro IIR
      
      
      //theta = Xll*33.33;
      theta = theta_l_emg;
      
      // Filtrar el real

      force[0] = Fl1; // max(-1000,min(1000,Fl1)); // Fl1 --> sin filtro ; Fl --> filtrada con media movil ;  Flf --> con filtro IIR en la tension
       
      
      //---------------------------- FILTRO IIR CHEBIS. TYPE I 3th Or. Fs = 1000 Hz - Fc = 10 Hz E_inf = 0.1dB--------------------------------------//
      
      //Af[0] = 1; Af[1] = -2.9213; Af[2] = 2.8497; Af[3] = -0.9282;  Af[4] = 0; Af[5] = 0.0; Af[6] = 0.0;
      //Bf[0] = 0.00002537; Bf[1] = 0.00007611; Bf[2] = 0.00007611; Bf[3] = 0.00002537;  Bf[4] = 0;  Bf[5] = 0.0;  Bf[6] = 0.0;
      
      //force_f[0] = - Af[1]*force_f[1] - Af[2]*force_f[2] - Af[3]*force_f[3] - Af[4]*force_f[4] - Af[5]*force_f[5] - Af[6]*force_f[6] +
       //              Bf[0]*force[0] + Bf[1]*force[1] + Bf[2]*force[2] + Bf[3]*force[3] + Bf[4]*force[4] + Bf[5]*force[5] + Bf[6]*force[6];
      //force_f[0] = 1*force_f[0];

      force_f[0] = Fl1; //sin filtro
      //------------------------------------------------------------------------------------------------------------------------------------------//
      
      //---------------------------
      // if para zerar control durante el primer segundo
      if (total_time < 250 ){factor = 1.0;} else {factor = 1.0;}
      //---------------------------
      
      force_f[0] = force_f[0];
      

      
      // ------------------- Controladores ------------------------------------------------------------ //

      //------ Control de impedancia discreto ------------
      Amp = 0.2;
      theta_d = 0 + Amp*setpoints_theta[total_time];  //*0  para activo  setpoint de 0.6 rad apara obtener Bv = 4.3 
      omega_d = 0 + Amp*setpoint_traj_vel[total_time];


      error_theta[0] = theta_d - theta;
      error_th = error_theta[0];

      Kv = 40;// 0  15 15   50   30    40    30   
      Bv = 1; // 0  0  5    1    1     5     10   0.5
      
      // ---------- control de  impedancia  ----------
      angulo_l = theta;
     
     // omega_l = 33.33*( ( (passo*velocity_d)/(2*3.1416*2) ) - (dot_force[0]/kmola_aesc) );
    
           omega_l = 33.33*( ( (passo*velocity_d)/(2*3.1416*2) ) - (dot_F_est/kmola_aesc) ); //esto funciona un poco ruidoso
          // omega_emg = 33.33*( ( (passo*omega_m)/(2*3.1416*2) ) - (dot_F_est/kmola_aesc) )*0;   //esto es de prueba pero no va

            //   juego(theta_d,theta_d*0.2);
    



     // force_d = (Kv*(theta_d - angulo_l) - Bv*(omega_l))/0.03;
     // force_d = (Kv*(theta_d - angulo_l) + Bv*(omega_d - omega_l))/0.03;
     //force_d = (Kv*(theta_d - angulo_l) + Bv*(omega_d - omega_l))/0.03 +  10*sin(theta_d);  //

     
  //kalman nominal velocidad
    omega_est2k1=A_f2b*omega_est2k + L_f2b*(omega_l - as_scalar(C_ff2b*omega_est2k));
    omega_l_est = as_scalar(C_ff2b*omega_est2k)*1.3;
    // update    
    omega_est2k = omega_est2k1;

    omega_l=omega_l_est;


     force_d = (Kv*(theta_d - angulo_l) + Bv*(omega_d - omega_l))/0.03 +  Kv*theta_d;  
     
                                                                                            
     

      angulo_l_ant = angulo_l;

      // Control de fuerza

      force_d = 0*100 + force_d + 0*100*setpoints_force[total_time]; //100
      //force_d = 100;

      //force_d = factor*force_d; //
      
      error_f[0] = force_d - force_f[0];
      //200*disturbio_force[total_time];
      int_force_error[0] = int_force_error[1] + error_f[0]*SAMPLE_TIME;



      error_ff = error_f[0];
      
      factor_de_seguridad = 7000;  
      if (velocity_d >= factor_de_seguridad){velocity_d = factor_de_seguridad;}
      else if (velocity_d <= -factor_de_seguridad){velocity_d = -factor_de_seguridad;}
      
      //printf("\nCorrente EPOS_03: %.2f", velocity_d);
       
      ///----- derivada de la fuerza -----------
      //dot_force[0] = (2/SAMPLE_TIME)*(force_f[0] - force_f[1]) - dot_force[1];
      //dot_force[0] = (force_f[0] - force_f[1])/SAMPLE_TIME;
      
      dot_force[0] =  0.9048*dot_force[1] + 100*(force_f[0] - force_f[1]); //0.369*dot
      filt_dot_force[0] = 0.9048*filt_dot_force[1] + 0.09516*dot_force[1];
      ////------------------------------------------
      
      ///////////////////////

      //modo_s=  y_est_Th;

      modo_s=y_est_emg1;
      

      if( abs(y_est_Th) >100 && abs(theta) < 0.1 &&  omega_l < 0.1){ 
        modo = 1;
        K = K1;
        //modo = 2;
        //K = K2;
      }
          else if (y_est_emg1 >0.05 || y_est_emg2 >0.1) {      //diani 0.3 y 0.52   mao 0.3 0.3 capi 0.3 0.7
        //else if (y_est_emg1 >0.3 ){
            modo = 2;
            K = K2;
          }   else {
                modo = 3;
                K = K3;
              }
       //0.2
      //  modo = 3;
      //  K = K3;
        
    
      mag_omega_l = abs(omega_l);
      mag_error_f = abs(error_f[0]/force_d);
      
      // setpoint frec = 0.5 hz
      //filtro_omega[0] = mag_omega_l_ant*0.0006281 + filtro_omega[1]*0.9994;

      double fc=0.001;
      double gama=2*pi*Ts*fc;
      filtro_omega[0] = mag_omega_l_ant*0.0001257 + filtro_omega[1]*0.9999;

   
    ////////// FIR coefficients ////////////////////////
      Bf[0]  = 0.007327774105318; Bf[1]  = 0.009397343795133; Bf[2]  = 0.015397595086210; Bf[3]  = 0.024748232734088;  
      Bf[4]  = 0.036538282451547; Bf[5]  = 0.049615423001699; Bf[6]  = 0.062699232323360; Bf[7]  = 0.074507182133088;
      Bf[8]  = 0.083880942925848; Bf[9]  = 0.089900520567104; Bf[10] = 0.091974941753211; Bf[11] = 0.089900520567104;  
      Bf[12] = 0.083880942925848; Bf[13] = 0.074507182133088; Bf[14] = 0.062699232323360; Bf[15] = 0.049615423001699;
      Bf[16] = 0.036538282451547; Bf[17] = 0.024748232734088; Bf[18] = 0.015397595086210; Bf[19] = 0.009397343795133;
      Bf[20] = 0.007327774105318;

    ///////////////////////////////////////////////////////////

      filtro_modo[0] = mag_omega_l;

      FILTRO = filtro_modo[0]*Bf[0] + filtro_modo[1]*Bf[1] + filtro_modo[2]*Bf[2] + filtro_modo[3]*Bf[3] + filtro_modo[4]*Bf[4] + filtro_modo[5]*Bf[5] + filtro_modo[6]*Bf[6] + filtro_modo[7]*Bf[7] + filtro_modo[8]*Bf[8] + filtro_modo[9]*Bf[9] + filtro_modo[10]*Bf[10] + filtro_modo[11]*Bf[11]+ filtro_modo[12]*Bf[12] +  filtro_modo[13]*Bf[13] + filtro_modo[14]*Bf[14] + filtro_modo[15]*Bf[15] +filtro_modo[16]*Bf[16] + filtro_modo[17]*Bf[17] +filtro_modo[18]*Bf[18] + filtro_modo[19]*Bf[19] + filtro_modo[20]*Bf[20];

      filtro_Tau_h[0] = abs(Tau_h);

      FILTRO_Tau_h = filtro_Tau_h[0]*Bf[0] + filtro_Tau_h[1]*Bf[1] + filtro_Tau_h[2]*Bf[2] + filtro_Tau_h[3]*Bf[3] + filtro_Tau_h[4]*Bf[4] + filtro_Tau_h[5]*Bf[5] + filtro_Tau_h[6]*Bf[6] + filtro_Tau_h[7]*Bf[7] + filtro_Tau_h[8]*Bf[8] + filtro_Tau_h[9]*Bf[9] + filtro_Tau_h[10]*Bf[10] + filtro_Tau_h[11]*Bf[11]+ filtro_Tau_h[12]*Bf[12] +  filtro_Tau_h[13]*Bf[13] + filtro_Tau_h[14]*Bf[14] + filtro_Tau_h[15]*Bf[15] + filtro_Tau_h[16]*Bf[16] + filtro_Tau_h[17]*Bf[17] +filtro_Tau_h[18]*Bf[18] + filtro_Tau_h[19]*Bf[19] + filtro_Tau_h[20]*Bf[20];
                      


        

  //kalman nominal
    F_est2k1=A_f2*F_est2k + L_f2*(filtro_modo[0] - as_scalar(C_ff2*F_est2k));
    y_est = as_scalar(C_ff2*F_est2k);
    // update    
    F_est2k = F_est2k1;
    
    
    //filtro_Tau_h[0]
      //kalman nominal Tau_h
    F_est2k1_Th = A_f2*F_est2k_Th + L_f2*(filtro_Tau_h[0] - as_scalar(C_ff2*F_est2k_Th));
    y_est_Th = as_scalar(C_ff2*F_est2k_Th);
    // update    

    F_est2k_Th = F_est2k1_Th;

      //kalman nominal emg1
    filtro_emg1[0] = emg_abs1;
    F_est2k1_emg1 = A_f2*F_est2k_emg1 + L_f2*(filtro_emg1[0] - as_scalar(C_ff2*F_est2k_emg1));
    y_est_emg1 = as_scalar(C_ff2*F_est2k_emg1);
    // update    
    F_est2k_emg1 = F_est2k1_emg1;

      //kalman nominal emg2
    filtro_emg2[0] = emg_abs2;
    F_est2k1_emg2 = A_f2*F_est2k_emg2 + L_f2*(filtro_emg2[0] - as_scalar(C_ff2*F_est2k_emg2));
    y_est_emg2 = as_scalar(C_ff2*F_est2k_emg2);
    // update    
    F_est2k_emg2 = F_est2k1_emg2;


    // setpoint frec = 0.25 hz
      //filtro_omega[0] = mag_omega_l_ant*6.283e-5 + filtro_omega[1]*0.9999;

     // filtro_mag_error_f[0] = mag_error_f_ant*0.0006281 + filtro_mag_error_f[1]*0.9994;
      
       modov = modo;
     
      
      // force control open loop
      //velocity_d = KX;
      
      //modo_s = force_f[0];
      //modo_s = abs(omega_l);
      modo_s = filtro_omega[0];

      /////////////////////////




      ////////////////////////  RLQR ////////////////////
      
      X(0,0) = dot_force[0];
      X(1,0) = force_f[0];
      //X(2,0) = theta_m;
      X(2,0) = theta;
      X(3,0) = int_force_error[0];

      KX = as_scalar(K*X);
       
      K_1 = as_scalar(K(0,0));
      K_2 = as_scalar(K(0,1));
      K_3 = as_scalar(K(0,2));
      K_4 = as_scalar(K(0,3));
     

     
      ///////////////////kalman/////////////////////////////
      //falta realimentar el kalman
      y=force_f[0];
      //u1=K*X;
      //u1=[K_1 k_2]*xest + K_3*X(2,0)+K_4*X(3,0);

      u1 = K(0,0)*xest(0,0) + K(0,1)*xest(1,0) + K(0,2)*X(2,0) + K(0,3)*X(3,0);
      cube x_cube(2,1,1);
      
      mat xest_act = xest;

      LPr_campo= rkf_slsm(Pk1,R_f,Q_f,F_f,G_f,Ef_f,Eg_f,Ec_f,Ed_f,C_f,D_f,B_f,Eb_f,xest,y,u1,M_f,N_f,mu_f,alpha_f,s,prob,modo);
      x_cube = LPr_campo(1,0);
      xest = x_cube.slice(0);
   
      ///////////////////////////////////////////////////////////////////////////////////
      
      dot_F_est = as_scalar(xest(0,0));
      F_est = as_scalar(xest(1,0));
      
      ///////// Torque humano ///////////////////////////
      mat Gfmat = G_f.slice(modo-1);
      //X.submat( first_row, first_col, last_row, last_col )

      mat Tau_h_mat = xest - F_f.slice(modo-1)*xest_act - B_f.slice(modo-1)*u1 - Gfmat.submat(0,1,1,1)*theta_m;
      
      Tau_h = (Tau_h_mat(0,0))/Gfmat(0,0);
      Tau_dist=Tau_h_mat(0,0);

      //velocity_d = KX;
      velocity_d = as_scalar(u1);

      //envia o controle ao motor // modo de velocidade
				eixo_motor.PDOsetVelocitySetpoint(int(velocity_d));
				eixo_motor.WritePDO02();
      
      //// crear buffer de valores anteriores de fuerza, control y error.

        // 0 es el actual... 1 es k-1... 2 es k-2...
        force[6] = force[5];
        force[5] = force[4];
	  		force[4] = force[3];
	  		force[3] = force[2];
	  		force[2] = force[1];
  			force[1] = force[0];

        force_f[6] = force_f[5];
        force_f[5] = force_f[4];
	  		force_f[4] = force_f[3];
	  		force_f[3] = force_f[2];
	  		force_f[2] = force_f[1];
  			force_f[1] = force_f[0];

        tension[6] = tension[5];
        tension[5] = tension[4];
	  		tension[4] = tension[3];
	  		tension[3] = tension[2];
	  		tension[2] = tension[1];
  			tension[1] = tension[0];

        tension_f[6] = tension_f[5];
        tension_f[5] = tension_f[4];
	  		tension_f[4] = tension_f[3];
	  		tension_f[3] = tension_f[2];
	  		tension_f[2] = tension_f[1];
  			tension_f[1] = tension_f[0];

        error_f[6] = error_f[5];
        error_f[5] = error_f[4];
	  		error_f[4] = error_f[3];
	  		error_f[3] = error_f[2];
	  		error_f[2] = error_f[1];
  			error_f[1] = error_f[0];

        error_theta[2] = error_theta[1];
        error_theta[1] = error_theta[0];

        filtro_modo[21] = filtro_modo[20];
        filtro_modo[20] = filtro_modo[19];
        filtro_modo[19] = filtro_modo[18];
        filtro_modo[18] = filtro_modo[17];
        filtro_modo[17] = filtro_modo[16];
        filtro_modo[16] = filtro_modo[15];
        filtro_modo[15] = filtro_modo[14];
        filtro_modo[14] = filtro_modo[13];
        filtro_modo[13] = filtro_modo[12];
        filtro_modo[12] = filtro_modo[11];
        filtro_modo[11] = filtro_modo[10];
        filtro_modo[10] = filtro_modo[9];
        filtro_modo[9]  = filtro_modo[8];
        filtro_modo[8]  = filtro_modo[7];
        filtro_modo[7]  = filtro_modo[6];
        filtro_modo[6]  = filtro_modo[5];
        filtro_modo[5]  = filtro_modo[4];
        filtro_modo[4]  = filtro_modo[3];
        filtro_modo[3]  = filtro_modo[2];
        filtro_modo[2]  = filtro_modo[1];
        filtro_modo[1]  = FILTRO;

        filtro_Tau_h[21] = filtro_Tau_h[20];
        filtro_Tau_h[20] = filtro_Tau_h[19];
        filtro_Tau_h[19] = filtro_Tau_h[18];
        filtro_Tau_h[18] = filtro_Tau_h[17];
        filtro_Tau_h[17] = filtro_Tau_h[16];
        filtro_Tau_h[16] = filtro_Tau_h[15];
        filtro_Tau_h[15] = filtro_Tau_h[14];
        filtro_Tau_h[14] = filtro_Tau_h[13];
        filtro_Tau_h[13] = filtro_Tau_h[12];
        filtro_Tau_h[12] = filtro_Tau_h[11];
        filtro_Tau_h[11] = filtro_Tau_h[10];
        filtro_Tau_h[10] = filtro_Tau_h[9];
        filtro_Tau_h[9]  = filtro_Tau_h[8];
        filtro_Tau_h[8]  = filtro_Tau_h[7];
        filtro_Tau_h[7]  = filtro_Tau_h[6];
        filtro_Tau_h[6]  = filtro_Tau_h[5];
        filtro_Tau_h[5]  = filtro_Tau_h[4];
        filtro_Tau_h[4]  = filtro_Tau_h[3];
        filtro_Tau_h[3]  = filtro_Tau_h[2];
        filtro_Tau_h[2]  = filtro_Tau_h[1];
        filtro_Tau_h[1]  = FILTRO_Tau_h;

        


        dot_force[1] = dot_force[0];
        filt_dot_force[1] = filt_dot_force[0];

        int_force_error[1] = int_force_error[0];

        mag_omega_l_ant = mag_omega_l;
        mag_error_f_ant = mag_error_f;
        filtro_mag_error_f[1] = filtro_mag_error_f[0];


			//incrementa contador de tempo
			total_time = total_time+1;



      //AGUARDA FIM DE TEMPO DE EXECU��O DE TAREFA
			QueryPerformanceCounter(&tick_after);
      while (final_time > tick_after.QuadPart){ 
        
        //printf("\n");
        //printf("alguna cosa");
        QueryPerformanceCounter(&tick_after);}


           
 //////////////////////// LLAMAR EL JUEGO   CADA 16ms ///////////////////////////////////////////////////////////
	    cont_pant=cont_pant+1;   
	    if (cont_pant>16){
  
    //ref_juego= juego_pasivo(theta_d,theta,total_time ,T);

    //   ref_juego=juego_resistivo(theta_d,theta,total_time ,T);

    //  ref_juego=juego_resistivo_centro(theta_d,theta,total_time ,T);


     ref_juego= juego_pasivo_resistivo(theta_d,theta,total_time ,T);

    // ref_juego= juego_pasivo_resistivo_resultados(theta_d,theta,total_time ,T);  //pra resultados de compracion entre algoritmos
        
	           cont_pant=0;
		 }
      ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
         
      
   	}while (total_time < T); // Continua por at� a ocorr�ncia de erros total_time = 2
				
		//Zera o comando do motor
	  eixo_motor.PDOsetVelocitySetpoint(0);
		eixo_motor.WritePDO02();
 

		//SALVA OS DATALOGGERS
		//Grava o log de posi��o para arquivo
		pFile = fopen ("Im.dat","w");
		for (i_dt=0;i_dt<60000*vet_adjust;i_dt++)
			{
				fprintf(pFile, "\n%.5f", datalog01[i_dt]);
			}
		fclose (pFile);

		pFile = fopen ("position.dat","w");
		for (i_dt=0;i_dt<60000*vet_adjust;i_dt++)
			{
				fprintf(pFile, "\n%.5f", datalog02[i_dt]);
			}
		fclose (pFile);
		
		pFile = fopen ("Fl.dat","w");
		for (i_dt=0;i_dt<60000*vet_adjust;i_dt++)
			{
				fprintf(pFile, "\n%.5f", datalog03[i_dt]);
			}
		fclose (pFile);

		pFile = fopen ("current_d.dat","w");
		for (i_dt=0;i_dt<60000*vet_adjust;i_dt++)
			{
				fprintf(pFile, "\n%.5f", datalog04[i_dt]);
			}
		fclose (pFile);

		pFile = fopen ("total_time.dat","w");
		for (i_dt=0;i_dt<60000*vet_adjust;i_dt++)
			{
				fprintf(pFile, "\n%.5f", datalog05[i_dt]);
			}
		fclose (pFile);

		pFile = fopen ("force.dat","w");
		for (i_dt=0;i_dt<60000*vet_adjust;i_dt++)
			{
				fprintf(pFile, "\n%.5f", datalog06[i_dt]);
			}
		fclose (pFile);

		pFile = fopen ("theta.dat","w");
		for (i_dt=0;i_dt<60000*vet_adjust;i_dt++)
			{
				fprintf(pFile, "\n%.5f", datalog07[i_dt]);
			}
		fclose (pFile);

		pFile = fopen ("theta_l.dat","w");
		for (i_dt=0;i_dt<60000*vet_adjust;i_dt++)
			{
				fprintf(pFile, "\n%.5f", datalog08[i_dt]);
			}
		fclose (pFile);

		pFile = fopen ("Fl1.dat","w");
		for (i_dt=0;i_dt<60000*vet_adjust;i_dt++)
			{
				fprintf(pFile, "\n%.5f", datalog09[i_dt]);
			}
		fclose (pFile);

		pFile = fopen ("Flf.dat","w");
		for (i_dt=0;i_dt<60000*vet_adjust;i_dt++)
			{
				fprintf(pFile, "\n%.5f", datalog10[i_dt]);
			}
		fclose (pFile);

		pFile = fopen ("force_d.dat","w");
		for (i_dt=0;i_dt<60000*vet_adjust;i_dt++)
			{
				fprintf(pFile, "\n%.5f", datalog11[i_dt]);
			}
		fclose (pFile);

		pFile = fopen ("force_f.dat","w");
		for (i_dt=0;i_dt<60000*vet_adjust;i_dt++)
			{
				fprintf(pFile, "\n%.5f", datalog12[i_dt]);
			}
		fclose (pFile);

		pFile = fopen ("error_f.dat","w");
		for (i_dt=0;i_dt<60000*vet_adjust;i_dt++)
			{
				fprintf(pFile, "\n%.5f", datalog14[i_dt]);
			}
		fclose (pFile);

    pFile = fopen ("error_ff.dat","w");
		for (i_dt=0;i_dt<60000*vet_adjust;i_dt++)
			{
				fprintf(pFile, "\n%.5f", datalog15[i_dt]);
			}
		fclose (pFile);

    pFile = fopen ("theta_d.dat","w");
		for (i_dt=0;i_dt<60000*vet_adjust;i_dt++)
			{
				fprintf(pFile, "\n%.5f", datalog16[i_dt]);
			}
		fclose (pFile);

     pFile = fopen ("error_th.dat","w");
		for (i_dt=0;i_dt<60000*vet_adjust;i_dt++)
			{
				fprintf(pFile, "\n%.5f", datalog17[i_dt]);
			}
		fclose (pFile);

    pFile = fopen ("Xll.dat","w");
		for (i_dt=0;i_dt<60000*vet_adjust;i_dt++)
			{
				fprintf(pFile, "\n%.5f", datalog18[i_dt]);
			}
		fclose (pFile);
    
    
    pFile = fopen ("omega_m_rad.dat","w");
		for (i_dt=0;i_dt<60000*vet_adjust;i_dt++)
			{
				fprintf(pFile, "\n%.5f", datalog19[i_dt]);
			}
		fclose (pFile);
    
    pFile = fopen ("theta_m.dat","w");
		for (i_dt=0;i_dt<60000*vet_adjust;i_dt++)
			{
				fprintf(pFile, "\n%.5f", datalog20[i_dt]);
			}
		fclose (pFile);

     pFile = fopen ("velocity_d_rad.dat","w");
		for (i_dt=0;i_dt<60000*vet_adjust;i_dt++)
			{
				fprintf(pFile, "\n%.5f", datalog21[i_dt]);
			}
		fclose (pFile);
    
     pFile = fopen ("omega_l.dat","w");
		for (i_dt=0;i_dt<60000*vet_adjust;i_dt++)
			{
				fprintf(pFile, "\n%.5f", datalog22[i_dt]);
			}
		fclose (pFile);
    
    pFile = fopen ("filt_dot_force.dat","w");
		for (i_dt=0;i_dt<60000*vet_adjust;i_dt++)
			{
				fprintf(pFile, "\n%.5f", datalog24[i_dt]);
			}
		fclose (pFile);

    pFile = fopen ("K_1.dat","w");
		for (i_dt=0;i_dt<60000*vet_adjust;i_dt++)
			{
				fprintf(pFile, "\n%.5f", datalog25[i_dt]);
			}
		fclose (pFile);

    pFile = fopen ("K_2.dat","w");
		for (i_dt=0;i_dt<60000*vet_adjust;i_dt++)
			{
				fprintf(pFile, "\n%.5f", datalog26[i_dt]);
			}
		fclose (pFile);

     pFile = fopen ("K_3.dat","w");
		for (i_dt=0;i_dt<60000*vet_adjust;i_dt++)
			{
				fprintf(pFile, "\n%.5f", datalog27[i_dt]);
			}
		fclose (pFile);

     pFile = fopen ("dot_force.dat","w");
		for (i_dt=0;i_dt<60000*vet_adjust;i_dt++)
			{
				fprintf(pFile, "\n%.5f", datalog29[i_dt]);
			}
		fclose (pFile);

    pFile = fopen ("normaP.dat","w");
		for (i_dt=0;i_dt<60000*vet_adjust;i_dt++)
			{
				fprintf(pFile, "\n%.5f", datalog30[i_dt]);
			}
		fclose (pFile);


    pFile = fopen ("dot_force_est.dat","w");
		for (i_dt=0;i_dt<60000*vet_adjust;i_dt++)
			{
				fprintf(pFile, "\n%.5f", datalog31[i_dt]);
			}
		fclose (pFile);

    pFile = fopen ("velocity_d_rpm.dat","w");
		for (i_dt=0;i_dt<60000*vet_adjust;i_dt++)
			{
				fprintf(pFile, "\n%.5f", datalog32[i_dt]);
			}
		fclose (pFile);

    pFile = fopen ("omega_m_rpm.dat","w");
		for (i_dt=0;i_dt<60000*vet_adjust;i_dt++)
			{
				fprintf(pFile, "\n%.5f", datalog33[i_dt]);
			}
		fclose (pFile);

    pFile = fopen ("omega_d.dat","w");
		for (i_dt=0;i_dt<60000*vet_adjust;i_dt++)
			{
				fprintf(pFile, "\n%.5f", datalog34[i_dt]);
			}
		fclose (pFile);

    pFile = fopen ("K_4.dat","w");
		for (i_dt=0;i_dt<60000*vet_adjust;i_dt++)
			{
				fprintf(pFile, "\n%.5f", datalog35[i_dt]);
			}
		fclose (pFile);

    pFile = fopen ("integral_error_fuerza.dat","w");
		for (i_dt=0;i_dt<60000*vet_adjust;i_dt++)
			{
				fprintf(pFile, "\n%.5f", datalog36[i_dt]);
			}
		fclose (pFile);

    pFile = fopen ("aceleracion.dat","w");
		for (i_dt=0;i_dt<60000*vet_adjust;i_dt++)
			{
				fprintf(pFile, "\n%.5f", datalog38[i_dt]);
			}
		fclose (pFile);

           pFile = fopen ("F_est.dat","w");
		for (i_dt=0;i_dt<60000*vet_adjust;i_dt++)
			{
				fprintf(pFile, "\n%.5f", datalog41[i_dt]);
			}
		fclose (pFile);

       pFile = fopen ("dot_F_est.dat","w");
		for (i_dt=0;i_dt<60000*vet_adjust;i_dt++)
			{
				fprintf(pFile, "\n%.5f", datalog42[i_dt]);
			}
		fclose (pFile);

    pFile = fopen ("Tau_h.dat","w");
		for (i_dt=0;i_dt<60000*vet_adjust;i_dt++)
			{
				fprintf(pFile, "\n%.5f", datalog43[i_dt]);
			}

		fclose (pFile);
    
      pFile = fopen ("filtro_omega.dat","w");
		for (i_dt=0;i_dt<60000*vet_adjust;i_dt++)
			{
				fprintf(pFile, "\n%.5f", datalog44[i_dt]);
			}

		fclose (pFile);

    pFile = fopen ("y_est.dat","w");
		for (i_dt=0;i_dt<60000*vet_adjust;i_dt++)
			{
				fprintf(pFile, "\n%.5f", datalog45[i_dt]);
			}

		fclose (pFile);

    pFile = fopen ("y_est_Th.dat","w");
		for (i_dt=0;i_dt<60000*vet_adjust;i_dt++)
			{
				fprintf(pFile, "\n%.5f", datalog46[i_dt]);
			}

		fclose (pFile);

     pFile = fopen ("FIR_Th.dat","w");
		for (i_dt=0;i_dt<60000*vet_adjust;i_dt++)
			{
				fprintf(pFile, "\n%.5f", datalog47[i_dt]);
			}

		fclose (pFile);

      pFile = fopen ("modo.dat","w");
		for (i_dt=0;i_dt<60000*vet_adjust;i_dt++)
			{
				fprintf(pFile, "\n%.5f", datalog48[i_dt]);
			}

		fclose (pFile);

    
    pFile = fopen ("emg_signal1.dat","w");
		for (i_dt=0;i_dt<60000*vet_adjust;i_dt++)
			{
				fprintf(pFile, "\n%.5f", datalog49[i_dt]);
			}

		fclose (pFile);

       pFile = fopen ("emg_signal2.dat","w");
		for (i_dt=0;i_dt<60000*vet_adjust;i_dt++)
			{
				fprintf(pFile, "\n%.5f", datalog50[i_dt]);
			}

		fclose (pFile);


       pFile = fopen ("emg_abs1.dat","w");
		for (i_dt=0;i_dt<60000*vet_adjust;i_dt++)
			{
				fprintf(pFile, "\n%.5f", datalog51[i_dt]);
			}

		fclose (pFile);


       pFile = fopen ("emg_abs2.dat","w");
		for (i_dt=0;i_dt<60000*vet_adjust;i_dt++)
			{
				fprintf(pFile, "\n%.5f", datalog52[i_dt]);
			}

		fclose (pFile);



         pFile = fopen ("y_est_emg1.dat","w");
		for (i_dt=0;i_dt<60000*vet_adjust;i_dt++)
			{
				fprintf(pFile, "\n%.5f", datalog53[i_dt]);
			}

		fclose (pFile);

    
         pFile = fopen ("y_est_emg2.dat","w");
		for (i_dt=0;i_dt<60000*vet_adjust;i_dt++)
			{
				fprintf(pFile, "\n%.5f", datalog54[i_dt]);
			}

		fclose (pFile);


    
         pFile = fopen ("theta_l_emg.dat","w");
		for (i_dt=0;i_dt<60000*vet_adjust;i_dt++)
			{
				fprintf(pFile, "\n%.5f", datalog55[i_dt]);
			}

		fclose (pFile);




         pFile = fopen ("omega_emg.dat","w");
		for (i_dt=0;i_dt<60000*vet_adjust;i_dt++)
			{
				fprintf(pFile, "\n%.5f", datalog56[i_dt]);
			}

		fclose (pFile);


      pFile = fopen ("Tau_dist.dat","w");
		for (i_dt=0;i_dt<60000*vet_adjust;i_dt++)
			{
				fprintf(pFile, "\n%.5f", datalog57[i_dt]);
			}

		fclose (pFile);

    
      pFile = fopen ("ref_juego.dat","w"); //ojo esta muestreado  32ms
		for (i_dt=0;i_dt<60000*vet_adjust;i_dt++)
			{
				fprintf(pFile, "\n%.5f", datalog58[i_dt]);
			}

		fclose (pFile);


    loopTime = 0;

}
