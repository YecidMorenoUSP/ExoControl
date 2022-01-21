if(exist('F__INIT__','var'))
    return
else
    clc
%     clear global
%     clearvars
    close all
%     addpath('../SAVE');
end

global Persona testValues F__INIT__ VERBOSE FNC K FIGURES TestFilesFormat

F__INIT__ = 1;
VERBOSE = 5;
K.SAVE_DIR = '../SAVE/';

K.Ts = 1/200;
K.Tignore = 1/K.Ts;

K.GPU = 1;

K.Colors.FES = [1 1 1]*.8;
K.Colors.FESArea = [1 1 0 .5]*.8;

FIGURES = {};


testValues = [[0 0 0 1 1 1 0 0 0 2 2 2 0]    % FES
              [0 1 2 2 1 0 0 1 2 2 1 0 0]    % Kv
              [0 0 0 1 1 1 0 0 0 2 2 2 0]]'; % Bv
          
Persona = {};
Persona{1} = struct(...
    'Name'      ,          'Yecid' ,...
    'Lastname'  ,         'Moreno' ,...
    'mA_FES'    ,  [  0, 80, 110]  ,...
    'fq_FES'    ,         30       ,...
    'Kv_RA'     ,  [  0,  20,  40] ,...
    'Bv_RA'     ,  [  0,   1,   2] ,...
    'Kv_RS'     ,  [  0,  10,  20] ,...
    'Bv_RS'     ,  [  0,   2,  4 ] ...
);

Persona{2} = struct(...
    'Name'      ,       'Mauricio' ,...
    'Lastname'  ,      'Escalante' ,...
    'mA_FES'    ,  [  0, 80, 110] ,...
    'fq_FES'    ,         30       ,...
    'Kv_RA'     ,  [  0,  20,  40] ,...
    'Bv_RA'     ,  [  0,   1,   2] ,...
    'Kv_RS'     ,  [  0,  10,  20] ,...
    'Bv_RS'     ,  [  0,   2,  4 ] ...
);   


% arma::fvec __KV__Values_RA  = {0,    20,  40};
% arma::fvec __BV__Values_RA  = {0,   0.5f,  1.5f};
% 
% arma::fvec __KV__Values_RS  = {0,  20, 40};
% arma::fvec __BV__Values_RS  = {0,   2,  4};


TestFilesFormat = {};

TestFilesFormat{1}.TypeFile = 'GM_RA';
TestFilesFormat{1}.Name = 'Game Marcian AnkleBot';
TestFilesFormat{1}.Headers = {{'Robot'    'Time' 'Pos' 'Fore'}, ...
                              {'Logs'     'Time' 'Fes' 'D_ref' 'ref'}, ...
                              {'EMG'      'Time' 'EMG2' 'EMG3' 'EMG10' 'EMG11'}}';
TestFilesFormat{1}.Names.R = 'Robot Data';
TestFilesFormat{1}.Names.L = 'Logs';
TestFilesFormat{1}.Names.E = 'EMG';

TestFilesFormat{2}.TypeFile = 'GM_RS';
TestFilesFormat{2}.Name = 'Game Marcian SPAR';
TestFilesFormat{2}.Headers = {{'Logs'     'Time' 'S1' 'S2' 'S3' 'S4' 'S5' 'S6' 'S7' 'S8' 'S9' 'S10' }, ...
                              {'EMG'      'Time' 'EMG2' 'EMG3' 'EMG10' 'EMG11'}}';
TestFilesFormat{2}.Names.L = 'Logs';
TestFilesFormat{2}.Names.E = 'EMG';

FNC.line = @()disp('------------------------------------------------------------------------------------------------------------------------------------------------------');

Nfiles = size(ls([K.SAVE_DIR '*.dat']),1);

if(VERBOSE>=1)
    FNC.line();
    disp '[OK] Personas Cargadas'
    disp '[OK] Funciones Creadas'
    fprintf('[OK] %d .dat encontrados\n',Nfiles)
    disp '[OK] Iniciado'
    FNC.line();
end   

getFilesNames

createFigures


















