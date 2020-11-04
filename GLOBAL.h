field<cube>  rlqr_slsm(cube F, cube Ef, cube G, cube Eg, cube H, cube P, cube Q, cube R, cube M, int s, mat prob, int N){
      //
      
      int n,m,i,j;
      
      double alpha = 1e-12;
      mat SIGMA,SIGMA_fila1,SIGMA_fila2,SIGMA_columna1,SIGMA_columna2,beta;
      
      mat I_N, I_M, Z_N, Z_N_1, Z_1_N, Z_N_M, Z_M_N;
      mat Z_2NpM_Np1, Z_Np1_2NpM, Z_NpM_NpM, Z_MpN_N, Z_4NpMp1_M, Z_3NpMp1_N;
      
     mat PP,PP_sub,AUX;
     mat P_cal, P_cal_fila1, P_cal_fila2, P_cal_fila3;
     mat W0, W0_fila1, W0_fila2;
     mat W, W_fila1, W_fila2;
     mat R_mat,M_mat,Q_mat,Eg_mat,F_mat,Ef_mat,G_mat;
     mat A_cal, A_cal_fila1, A_cal_fila2, A_cal_fila3, A_cal_fila4,A_cal_fila5;
     mat U,V,Z;
     mat UW,VU,ZW;
     mat P_modo,K_modo,L_modo;
     mat PP_resh;
     mat P_modos, P_modo1, P_modo2, P_modo3;
     mat K_modos,K_modo1, K_modo2, K_modo3;
     mat L_modos;
     
      n = F.slice(0).n_rows;
      m = G.slice(0).n_cols;

     cube L(n*n,N,s);
     cube K(n,N,s);
     

     K_modo.zeros(n,N);

      beta.zeros(1,1);
      beta(0,0) = 1e-17;

      
      SIGMA.zeros((n+1),(n+1));
      
      I_N.eye(n,n);
      Z_N.zeros(n,n);
      I_M.eye(m,m);

      Z_N_1.zeros(n,1);
      Z_1_N.zeros(1,n);
      Z_N_M.zeros(n,m);
      Z_M_N.zeros(m,n);

      Z_2NpM_Np1.zeros(2*n+m,n+1);
      Z_Np1_2NpM.zeros(n+1,2*n+m);
      Z_NpM_NpM.zeros(n+m,n+m);
      Z_MpN_N.zeros(m+n,n);
      Z_4NpMp1_M.zeros(n+m+n+n+1+n,m);
      Z_3NpMp1_N.zeros(n+m+n+n+1,n);

      
     SIGMA_fila1 = join_rows(alpha*I_N,Z_N_1);
     SIGMA_fila2 = join_rows(Z_1_N,beta);
     SIGMA = join_cols(SIGMA_fila1,SIGMA_fila2);
     
      
     P_cal.zeros((n+m+n),(n+m+n));
     A_cal.zeros((n+m+n+1),(n+m));
     R_mat.zeros(m,m);
     M_mat.zeros(m,n);
     Eg_mat.zeros(m,m);
     Ef_mat.zeros(1,m);
     F_mat.zeros(n,n);
     PP_resh.zeros(n*n,1);

     UW.zeros(n,n);
     
     PP.zeros(n*n,N);
     
     
     for(int k=0;k<=N-2;k++){ //N
          
          for(int i=0;i<=(s-1);i++){

            AUX.zeros(n,n);

            for(int j=0;j<=(s-1);j++){
                
                PP = P.slice(j);
                PP_resh = PP.submat(0,k,(n*n)-1,k);
                PP_resh.reshape(n,n);
                AUX = AUX + prob(i,j)*PP_resh;
            }
            
            R_mat = R.slice(i);
            M_mat = M.slice(i);
            Q_mat = Q.slice(i);
            Eg_mat = Eg.slice(i);
            Ef_mat = Ef.slice(i);
            F_mat = F.slice(i);
            G_mat = G.slice(i);

            P_cal_fila1 = join_rows(join_rows( AUX,   Z_N_M), Z_N);
            P_cal_fila2 = join_rows(join_rows( Z_M_N, R_mat), M_mat);
            P_cal_fila3 = join_rows(join_rows( Z_N,   M_mat.t()), Q_mat);

            P_cal = join_cols(join_cols(P_cal_fila1,P_cal_fila2),P_cal_fila3);
            
            A_cal_fila1 = join_rows( I_N,   Z_N_M);
            A_cal_fila2 = join_rows( Z_M_N, I_M );
            A_cal_fila3 = join_rows( Z_N,   Z_N_M);
            A_cal_fila4 = join_rows( I_N, -G_mat);
            A_cal_fila5 = join_rows( Z_1_N, -Eg_mat);

            A_cal = join_cols(join_cols(join_cols(join_cols(A_cal_fila1,A_cal_fila2),A_cal_fila3),A_cal_fila4),A_cal_fila5);

            
            W0_fila1 = join_rows( inv(P_cal), Z_2NpM_Np1);
            W0_fila2 = join_rows( Z_Np1_2NpM, SIGMA);
            
            W0 = join_cols(W0_fila1,W0_fila2);
            
            W_fila1 = join_rows(W0, A_cal);
            W_fila2 = join_rows(A_cal.t(),Z_NpM_NpM);

            W = join_cols(W_fila1,W_fila2);
            
            
            U = join_cols( join_cols( join_cols (join_cols (join_cols (Z_N, Z_M_N), -I_N), F_mat), Ef_mat), Z_MpN_N);
            
            V = join_cols(Z_4NpMp1_M, I_M);
            
            Z = join_cols(join_cols(Z_3NpMp1_N, I_N), Z_M_N);

            // reshape(mat, n_rows, n_cols, dim=0)
            //reshape(cube, n_rows, n_cols, n_slices, dim=0)

            //X.submat( first_row, first_col, last_row, last_col )
            
            UW = U.t()*inv(W)*U;

            P_modo = P.slice(i); 
            P_modo.submat(0, k+1,(n*n-1),k+1) = reshape(UW,n*n,1); 
            P.slice(i) = P_modo;
            
            VU = V.t()*inv(W)*U;
            
            K_modo = K.slice(i); 
            K_modo.submat(0,k,(n*m)-1,k) = reshape(VU,n*m,1); 
            //reshape(cube, n_rows, n_cols, n_slices, dim=0)
            K.slice(i) = K_modo;
            
            ZW = Z.t()*inv(W)*U;
            
            L_modo = L.slice(i); 
            L_modo.submat(0, k, (n*n)-1, k) = reshape(ZW,n*n,1); 
            L.slice(i) = L_modo;
            
           
            
          }
     }
     
            

field<cube> CAMPO(3,1);
CAMPO(0,0) = P;
CAMPO(1,0) = K; 
CAMPO(2,0) = L; 


     return CAMPO;
  
}
mat RKF(mat P_f, mat R_f, mat Q_f, mat F_f, mat G_f, mat Ef_f, mat Eg_f, mat Ec_f, mat Ed_f, mat C_f, mat D_f, mat B_f, mat Eb_f, mat xest, mat y, mat u, mat M_f, mat N_f, double mu_f, double alpha_f){
   
   double SEL = 1;
   int np, mk, nx, mu, nr;
   double lambda_h;
   mat SIGMA1, SIGMA2;
   mat I_NX, I_NR, I_NP,I_MU;
   mat Z_NX_NR, Z_NR_NX, Z_NR_NP,Z_NP_NR,Z_NX_NX,Z_NX_MU,Z_NX_MK,Z_MU_NX,Z_MU_MK,Z_MK_NX,Z_MK_MU,Z_MU_MU,Z_MK_MK;
   mat Z_NR_1,Z_NX_1,Z_MU_1,Z_MK_1;
   mat Z_NX_NXpNR,Z_NX_NPpNR,Z_MU_NXpNR,Z_MU_NPpNR,Z_MK_NXpNR,Z_MK_NPpNR;
   mat Z_NXpNR_NX,Z_NXpNR_MU,Z_NXpNR_MK;
   mat Z_NXpNR_NPpNR;
   mat Z_NPpNR_NX,Z_NPpNR_MU,Z_NPpNR_MK,Z_NPpNR_NXpNR;
   mat I_k,I_MK;

   mat SIGMA1_row1, SIGMA1_row2,SIGMA2_row1, SIGMA2_row2;
   mat G_k, F_k, D_k, C_k, B_k,y_k;
   mat Xf1,Xf2,Xf3,Xf4,Xf5,Xf6,Xf7,Xf8,Xf9,Xf10,Xf11,X;

   
   np = D_f.n_rows;
   mk = D_f.n_cols;
   nx = G_f.n_rows;
   mu = G_f.n_cols;
   nr = Eg_f.n_rows;

   
   I_NX.eye(nx,nx);
   I_NR.eye(nr,nr);
   I_NP.eye(np,np);
   I_MU.eye(mu,mu);
   I_MK.eye(mk,mk);
   Z_NX_NR.zeros(nx,nr);
   Z_NR_NX.zeros(nr,nx);
   Z_NR_NP.zeros(nr,np);
   Z_NP_NR.zeros(np,nr);
   Z_NX_NX.zeros(nx,nx);

   Z_NR_1.zeros(nr,1);
   Z_NX_1.zeros(nx,1);
   Z_MU_1.zeros(mu,1);
   Z_MK_1.zeros(mk,1);

   Z_NX_MU.zeros(nx,mu);
   Z_NX_MK.zeros(nx,mk);
   Z_MU_MK.zeros(mu,mk);
   Z_MU_NX.zeros(mu,nx);
   Z_MK_NX.zeros(mk,nx);
   Z_MK_MU.zeros(mk,mu);
   Z_MU_MU.zeros(mu,mu);
   Z_MK_MK.zeros(mk,mk);

   Z_NX_NXpNR.zeros(nx,(nx+nr));
   Z_NX_NPpNR.zeros(nx,(np+nr));
   Z_MU_NXpNR.zeros(mu,(nx+nr));
   Z_MU_NPpNR.zeros(mu,(np+nr));
   Z_MK_NXpNR.zeros(mk,(nx+nr));
   Z_MK_NPpNR.zeros(mk,(np+nr));

   Z_NXpNR_NX.zeros((nx+nr),nx);
   Z_NXpNR_MU.zeros((nx+nr),mu);
   Z_NXpNR_MK.zeros((nx+nr),mk);

   Z_NXpNR_NPpNR.zeros((nx+nr),(np+nr));

   Z_NPpNR_NX.zeros((np+nr),nx);
   Z_NPpNR_MU.zeros((np+nr),mu);
   Z_NPpNR_MK.zeros((np+nr),mk);
   Z_NPpNR_NXpNR.zeros((np+nr),(nx+nr));

  //   LARGE_INTEGER tick_after_filtro_1;
  //LARGE_INTEGER tick_after_filtro_2;

  //QueryPerformanceCounter(&tick_after_filtro_1);


   mat mat_norm; 
   mat_norm.zeros(2,2);
   mat_norm(0,0) = as_scalar(M_f.t()*M_f);
   mat_norm(1,1) = as_scalar(N_f.t()*N_f);

   lambda_h =(1+alpha_f)*norm(mu_f*mat_norm,2);

   SIGMA1_row1 = join_rows(pow(mu_f,-1)*I_NX - pow(lambda_h,-1)*M_f*M_f.t(),Z_NX_NR);
   SIGMA1_row2 = join_rows(Z_NR_NX,pow(lambda_h,-1)*I_NR);
   
   SIGMA2_row1 = join_rows(pow(mu_f,-1)*I_NP - pow(lambda_h,-1)*N_f*N_f.t(),Z_NP_NR);
   SIGMA2_row2 = join_rows(Z_NR_NP,pow(lambda_h,-1)*I_NR);

   SIGMA1 = join_cols(SIGMA1_row1,SIGMA1_row2);
   SIGMA2 = join_cols(SIGMA2_row1,SIGMA2_row2);
   
   I_k.zeros((nx+nr),nx);
   I_k = join_cols(I_NX,Z_NR_NX);
      
   G_k = join_cols(G_f,Eg_f);
   F_k = join_cols(F_f,Ef_f);
   D_k = join_cols(D_f,Ed_f);
   C_k = join_cols(C_f,Ec_f);
   B_k = join_cols(B_f,Eb_f);

   y_k = join_cols(y,Z_NR_1);

   ///////np = 1, mk = 1, nx = 2, mu = 2, nr = 1 
   Xf1 =  join_rows(join_rows(join_rows(join_rows(join_rows(join_rows(join_rows(join_rows(join_rows(join_rows(P_f,           Z_NX_MU),    Z_NX_MK),    Z_NX_NX),                 Z_NX_NXpNR),     Z_NX_NPpNR),     I_NX),       Z_NX_MU),    Z_NX_MK),    Z_NX_NX),  Z_NX_NX);
   Xf2 =  join_rows(join_rows(join_rows(join_rows(join_rows(join_rows(join_rows(join_rows(join_rows(join_rows(Z_MU_NX,       Q_f),        Z_MU_MK),    Z_MU_NX),                 Z_MU_NXpNR),     Z_MU_NPpNR),     Z_MU_NX),    I_MU),       Z_MU_MK),    Z_MU_NX),  Z_MU_NX);
   Xf3 =  join_rows(join_rows(join_rows(join_rows(join_rows(join_rows(join_rows(join_rows(join_rows(join_rows(Z_MK_NX,       Z_MK_MU),    R_f),        Z_MK_NX),                 Z_MK_NXpNR),     Z_MK_NPpNR),     Z_MK_NX),    Z_MK_MU),    I_MK),       Z_MK_NX),  Z_MK_NX);
   Xf4 =  join_rows(join_rows(join_rows(join_rows(join_rows(join_rows(join_rows(join_rows(join_rows(join_rows(Z_NX_NX,       Z_NX_MU),    Z_NX_MK),    (SEL*pow(mu_f,-1)*I_NX)), Z_NX_NXpNR),     Z_NX_NPpNR),     I_NX),       Z_NX_MU),    Z_NX_MK),    -1*I_NX),  Z_NX_NX);
   Xf5 =  join_rows(join_rows(join_rows(join_rows(join_rows(join_rows(join_rows(join_rows(join_rows(join_rows(Z_NXpNR_NX,    Z_NXpNR_MU), Z_NXpNR_MK), Z_NXpNR_NX),              (SEL*SIGMA1)),   Z_NXpNR_NPpNR),  Z_NXpNR_NX), G_k),        Z_NXpNR_MK), F_k),      (-1*I_k));
   Xf6 =  join_rows(join_rows(join_rows(join_rows(join_rows(join_rows(join_rows(join_rows(join_rows(join_rows(Z_NPpNR_NX,    Z_NPpNR_MU), Z_NPpNR_MK), Z_NPpNR_NX),              Z_NPpNR_NXpNR),  SEL*SIGMA2),     Z_NPpNR_NX), Z_NPpNR_MU), D_k),        C_k),      Z_NPpNR_NX);
   Xf7 =  join_rows(join_rows(join_rows(join_rows(join_rows(join_rows(join_rows(join_rows(join_rows(join_rows(I_NX,          Z_NX_MU),    Z_NX_MK),    I_NX),                    Z_NX_NXpNR),     Z_NX_NPpNR),     Z_NX_NX),    Z_NX_MU),    Z_NX_MK),    Z_NX_NX),  Z_NX_NX);
   Xf8 =  join_rows(join_rows(join_rows(join_rows(join_rows(join_rows(join_rows(join_rows(join_rows(join_rows(Z_MU_NX,       I_MU),       Z_MU_MK),    Z_MU_NX),                 G_k.t()),        Z_MU_NPpNR),     Z_MU_NX),    Z_MU_MU),    Z_MU_MK),    Z_MU_NX),  Z_MU_NX);
   Xf9 =  join_rows(join_rows(join_rows(join_rows(join_rows(join_rows(join_rows(join_rows(join_rows(join_rows(Z_MK_NX,       Z_MK_MU),    I_MK),       Z_MK_NX),                 Z_MK_NXpNR),     D_k.t()),        Z_MK_NX),    Z_MK_MU),    Z_MK_MK),    Z_MK_NX),  Z_MK_NX);
   Xf10 = join_rows(join_rows(join_rows(join_rows(join_rows(join_rows(join_rows(join_rows(join_rows(join_rows(Z_NX_NX,       Z_NX_MU),    Z_NX_MK),    -1*I_NX),                 F_k.t()),        C_k.t()),        Z_NX_NX),    Z_NX_MU),    Z_NX_MK),    Z_NX_NX),  Z_NX_NX);
   Xf11 = join_rows(join_rows(join_rows(join_rows(join_rows(join_rows(join_rows(join_rows(join_rows(join_rows(Z_NX_NX,       Z_NX_MU),    Z_NX_MK),    Z_NX_NX),                 -1*I_k.t()),         Z_NX_NPpNR),     Z_NX_NX),    Z_NX_MU),    Z_NX_MK),    Z_NX_NX),  Z_NX_NX);

   X = join_cols(join_cols(join_cols(join_cols(join_cols(join_cols(join_cols(join_cols(join_cols(join_cols(Xf1,Xf2),Xf3),Xf4),Xf5),Xf6),Xf7),Xf8),Xf9),Xf10),Xf11);

   mat Xif1  = join_rows(join_rows(Z_NX_1, Z_NX_NX),    Z_NX_NX);
   mat Xif2  = join_rows(join_rows(Z_MU_1, Z_MU_NX),    Z_MU_NX);
   mat Xif3  = join_rows(join_rows(Z_MK_1, Z_MK_NX),    Z_MK_NX);
   mat Xif4  = join_rows(join_rows(-xest,  Z_NX_NX),    Z_NX_NX);
   mat Xif5  = join_rows(join_rows(-B_k*u, Z_NXpNR_NX), Z_NXpNR_NX);
   mat Xif6  = join_rows(join_rows(y_k,    Z_NPpNR_NX), Z_NPpNR_NX);
   mat Xif7  = join_rows(join_rows(Z_NX_1, Z_NX_NX),    Z_NX_NX);
   mat Xif8  = join_rows(join_rows(Z_MU_1, Z_MU_NX),    Z_MU_NX);
   mat Xif9  = join_rows(join_rows(Z_MK_1, Z_MK_NX),    Z_MK_NX);
   mat Xif10 = join_rows(join_rows(Z_NX_1, -I_NX),      Z_NX_NX);
   mat Xif11 = join_rows(join_rows(Z_NX_1, Z_NX_NX),    -I_NX);


  mat Xi = join_cols(join_cols(join_cols(join_cols(join_cols(join_cols(join_cols(join_cols(join_cols(join_cols(Xif1,Xif2),Xif3),Xif4),Xif5),Xif6),Xif7),Xif8),Xif9),Xif10),Xif11);
   
  mat Zeta_f1  = join_rows(Z_NX_NX,Z_NX_NX);
  mat Zeta_f2  = join_rows(Z_MU_NX,Z_MU_NX);
  mat Zeta_f3  = join_rows(Z_MK_NX,Z_MK_NX);
  mat Zeta_f4  = join_rows(Z_NX_NX,Z_NX_NX);
  mat Zeta_f5  = join_rows(Z_NXpNR_NX,Z_NXpNR_NX);
  mat Zeta_f6  = join_rows(Z_NPpNR_NX,Z_NPpNR_NX);
  mat Zeta_f7  = join_rows(Z_NX_NX,Z_NX_NX);
  mat Zeta_f8  = join_rows(Z_MU_NX,Z_MU_NX);
  mat Zeta_f9  = join_rows(Z_MK_NX,Z_MK_NX);
  mat Zeta_f10 = join_rows(I_NX,Z_NX_NX);
  mat Zeta_f11 = join_rows(Z_NX_NX,I_NX);

  mat Zeta = join_cols(join_cols(join_cols(join_cols(join_cols(join_cols(join_cols(join_cols(join_cols(join_cols(Zeta_f1,Zeta_f2),Zeta_f3),Zeta_f4),Zeta_f5),Zeta_f6),Zeta_f7),Zeta_f8),Zeta_f9),Zeta_f10),Zeta_f11);
  
  
  mat LPP = Zeta.t()*inv(X)*Xi;

  //QueryPerformanceCounter(&tick_after_filtro_2);
  //double t_filtro_2 = ( (double) ( tick_after_filtro_2.QuadPart - tick_after_filtro_1.QuadPart ) ) / TICKS_PER_SECOND.QuadPart;
   
  //printf( "demora2: %g\n", t_filtro_2 );


  // mat X_dim;
 // X_dim.zeros(2,1);
  
   //X_dim(0,0) = np;
   //X_dim(1,0) = mk;
   //X_dim(2,0) = nx;
   //X_dim(3,0) = mu;
   //X_dim(4,0) = nr;
   
  // X_dim(0,0) = xk.n_rows; 
  // X_dim(1,0) = xk.n_cols;

   //re_sul
   //return X_dim;
   return LPP;
}
field<cube>  rkf_slsm(cube Pk1,mat R_f,mat Q_f,cube F_f,cube G_f,cube Ef_f,cube Eg_f,cube Ec_f,cube Ed_f,cube C_f,cube D_f,cube B_f,cube Eb_f,mat xest,mat y,mat u1,cube M_f,cube N_f,double mu_f,double alpha_f,double s,mat prob ,double modo){
    
   int nt = F_f.slice(0).n_rows;
     
   
   int npf = D_f.slice(0).n_rows;
   int mkf = D_f.slice(0).n_cols;
   int nxf = G_f.slice(0).n_rows;
   int muf = G_f.slice(0).n_cols;
   int nrf = Eg_f.slice(0).n_rows;
   mat LPPrf;
   cube xkf(nxf,1,1);
   cube xk1f(nxf,1,1);
   cube Pkf(nxf,nxf,5);
   cube Pk1f(nxf,nxf,5);



if(modo <= s){

         mat AUX_f;
         int it;

         it=modo-1;
          AUX_f.zeros(nt,nt);
          for(int jt=0;jt < s; jt++){

            AUX_f= AUX_f+ prob(it,jt)*Pk1.slice(it);


          }

          
       LPPrf= RKF(AUX_f, R_f, Q_f, F_f.slice(it), G_f.slice(it), Ef_f.slice(it), Eg_f.slice(it), Ec_f.slice(it), Ed_f.slice(it), C_f.slice(it), D_f.slice(it), B_f.slice(it), Eb_f.slice(it), xest, y,u1 ,M_f.slice(it) ,N_f.slice(it) , mu_f, alpha_f);  

          
          xkf.slice(0) =  LPPrf.submat(0,0,(nxf-1),0);                     // first_row, first_col, last_row, last_col
          xk1f.slice(0) = LPPrf.submat((nxf),0,(2*nxf-1),0);               // first_row, first_col, last_row, last_col
          Pkf.slice(it) =  LPPrf.submat(0,1,(nxf-1),(nxf));                // first_row, first_col, last_row, last_col
          Pk1f.slice(it) = LPPrf.submat((nxf),(nxf+1),(2*nxf-1),(2*nxf));  // first_row, first_col, last_row, last_col
   


}
else{

   for(int it=0;it < s; it++){


          mat AUX_f;
          AUX_f.zeros(nt,nt);
          for(int jt=0;jt < s; jt++){

            AUX_f= AUX_f+ prob(it,jt)*Pk1.slice(it);


          }

          
       LPPrf= RKF(AUX_f, R_f, Q_f, F_f.slice(it), G_f.slice(it), Ef_f.slice(it), Eg_f.slice(it), Ec_f.slice(it), Ed_f.slice(it), C_f.slice(it), D_f.slice(it), B_f.slice(it), Eb_f.slice(it), xest, y,u1 ,M_f.slice(it) ,N_f.slice(it) , mu_f, alpha_f);  

          
          xkf.slice(0) =  LPPrf.submat(0,0,(nxf-1),0);                     // first_row, first_col, last_row, last_col
          xk1f.slice(0) = LPPrf.submat((nxf),0,(2*nxf-1),0);               // first_row, first_col, last_row, last_col
          Pkf.slice(it) =  LPPrf.submat(0,1,(nxf-1),(nxf));                // first_row, first_col, last_row, last_col
          Pk1f.slice(it) = LPPrf.submat((nxf),(nxf+1),(2*nxf-1),(2*nxf));  // first_row, first_col, last_row, last_col
      
     
   }


}
    
field<cube> CAMPO1(4,1);
CAMPO1(0,0) = xkf;
CAMPO1(1,0) = xk1f;
CAMPO1(2,0) = Pkf;
CAMPO1(3,0) = Pk1f;

   return CAMPO1;
  }
mat robust_control_full(mat P, mat R, mat Q, mat F, mat G, mat Ef, mat Eg, mat M, double alpha, double mu ){ 
     int nx, nu, nr;
      double lambda_h;
      mat H,SIGMA, SIGMA_fila1,SIGMA_fila2,SIGMA_columna1,SIGMA_columna2;
      mat I_NX, I_NU,I_NR;
      mat Z_NX,Z_NU;
      mat Z_NX_NR, Z_NR_NX, Z_NX_NU, Z_NU_NX;
      mat Z_NX_NRpNX, Z_NU_NRpNX,Z_NRpNX_NX,Z_NRpNX_NU,Z_NXpNR_NX,Z_NXpNR_NU;
      mat I_r,G_r,F_r;
      mat X,X_fila1,X_fila2,X_fila3,X_fila4,X_fila5,X_fila6;
      mat Zeta,Zeta_fila1,Zeta_fila2,Zeta_fila3,Zeta_fila4,Zeta_fila5,Zeta_fila6;
      mat Xi;
      mat LKP;
      mat L;

      nx = G.n_rows;
      nu = G.n_cols;
      nr = Eg.n_rows;

      lambda_h = (1+alpha)*norm((mu*M.t()*M),2);

      H.eye(nx,nx);

      I_NX.eye(nx,nx);
      I_NR.eye(nr,nr);
      I_NU.eye(nu,nu);
      
      Z_NX.zeros(nx,nx);
      Z_NU.zeros(nu,nu);

      Z_NX_NR.zeros(nx,nr);
      Z_NR_NX.zeros(nr,nx);
      Z_NX_NU.zeros(nx,nu);
      Z_NU_NX.zeros(nu,nx);
      
      Z_NX_NRpNX.zeros(nx,(nr+nx));
      Z_NU_NRpNX.zeros(nu,(nr+nx));
      Z_NXpNR_NX.zeros((nx+nr),nx);
      Z_NXpNR_NU.zeros((nx+nr),nu);
      Z_NRpNX_NX.zeros((nr+nx),nx);
      Z_NRpNX_NU.zeros((nr+nx),nu);

      SIGMA.zeros((nr+nx),(nr+nx));
      
      SIGMA_fila1 = join_rows( ( (pow(mu,-1)*I_NX)- pow(lambda_h,-1)*M*M.t() ) , (Z_NX_NR) );
      SIGMA_fila2 = join_rows( Z_NR_NX , (pow(lambda_h,-1)* I_NR) );
      
      SIGMA = join_cols(SIGMA_fila1,SIGMA_fila2);

      I_r.zeros((nr+nx),nx);
      I_r = join_cols(I_NX,Z_NR_NX);
      
      G_r.zeros((nr+nx),nu);
      G_r = join_cols(G,Eg);
      
      F_r.zeros((nr+nx),nx);
      F_r = join_cols(F,Ef);
      
      X.zeros((nx+nu+nx+nr+nx+nx+nu),(nx+nu+nx+nr+nx+nx+nu));
      X_fila1 = join_rows(join_rows(join_rows(join_rows(join_rows( inv(P),     Z_NX_NU),    Z_NX),       Z_NX_NRpNX), I_NX),    Z_NX_NU);
      X_fila2 = join_rows(join_rows(join_rows(join_rows(join_rows( Z_NU_NX,    inv(R)),     Z_NU_NX),    Z_NU_NRpNX), Z_NU_NX), I_NU); 
      X_fila3 = join_rows(join_rows(join_rows(join_rows(join_rows( Z_NX,       Z_NX_NU),    inv(Q)),     Z_NX_NRpNX), Z_NX),    Z_NX_NU);
      X_fila4 = join_rows(join_rows(join_rows(join_rows(join_rows( Z_NRpNX_NX, Z_NRpNX_NU), Z_NRpNX_NX), SIGMA),      I_r),    -G_r);
      X_fila5 = join_rows(join_rows(join_rows(join_rows(join_rows( I_NX,       Z_NX_NU),    Z_NX),       I_r.t()),    Z_NX),    Z_NX_NU);
      X_fila6 = join_rows(join_rows(join_rows(join_rows(join_rows( Z_NU_NX,    I_NU),       Z_NU_NX),   -G_r.t()),    Z_NU_NX), Z_NU);

      
      X = join_vert(join_vert(join_vert(join_vert(join_vert(X_fila1,X_fila2),X_fila3),X_fila4),X_fila5),X_fila6);
      
      Zeta.zeros((nx+nu+nx+nx+nr+nx+nu),(nx+nu+nx));
      Zeta_fila1 = join_rows(join_rows( Z_NX,       Z_NX_NU),    Z_NX);
      Zeta_fila2 = join_rows(join_rows( Z_NU_NX,    Z_NU),       Z_NU_NX);
      Zeta_fila3 = join_rows(join_rows( Z_NX,       Z_NX_NU),   -I_NX);
      Zeta_fila4 = join_rows(join_rows( Z_NXpNR_NX, Z_NXpNR_NU), F_r);
      Zeta_fila5 = join_rows(join_rows( I_NX,       Z_NX_NU),    Z_NX);
      Zeta_fila6 = join_rows(join_rows( Z_NU_NX,    I_NU),       Z_NU_NX);

      Zeta = join_cols(join_cols(join_cols(join_cols(join_cols(Zeta_fila1,Zeta_fila2),Zeta_fila3),Zeta_fila4),Zeta_fila5),Zeta_fila6);
      
      
      Xi.zeros((nx+nu+nx+nx+nr+nx+nu),nx);
      Xi = join_cols(join_cols(join_cols(join_cols(join_cols(Z_NX,Z_NU_NX),-I_NX),F_r),Z_NX),Z_NU_NX);
      
      LKP.zeros(Zeta.n_cols, Xi.n_cols);
      
      LKP = Zeta.t()*inv(X)*Xi;

      //L.zeros((nx-1),LKP.n_cols);
 
      return LKP;
}
