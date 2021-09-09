// Função Controle Robusto RLQR


    mat robust_control_full (mat P, mat R, mat Q, mat F, mat G, mat Ef, mat Eg, mat M, double alpha, double mu ){
      
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