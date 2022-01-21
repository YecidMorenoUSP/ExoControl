% clear all
% clear F__INIT__
f__init__()

global VERBOSE FNC K Persona TestFilesFormat

if(VERBOSE>=5)
    disp("R: Robot & L: Log & E: Electromyography")
end


vecNtests = 1:13;

for idx_p = 1:size(Persona,2)
    
    p = Persona{idx_p};
       
    test_file_date_time = {};
    for nTest = vecNtests
        for nformatFiles = 1 : length([TestFilesFormat{:}])
            formatFiles = TestFilesFormat{nformatFiles};
            to_search = [K.SAVE_DIR '' formatFiles.TypeFile '_' p.Name '_Test_' num2str(nTest) '_' '*_Log_' formatFiles.Headers{1}{1}(1) '_' '' '' '*.dat'];
%             to_search
            files = ls(to_search);
            for nfile = 1:size(files,1)
                test_file_date_time{nTest}{nformatFiles}{nfile} = split(files(nfile,:),'__');
            end
        end
    end
    
    Persona{idx_p}.('test_file_date_time') = test_file_date_time;
    
    names_type_test_Nt_letter = {};
    DATA = {};
    
    for nformatFiles = 1 : length([TestFilesFormat{:}])
        formatFiles = TestFilesFormat{nformatFiles};
        
        for nTest = vecNtests
            for nletterFile = 1:size(formatFiles.Headers,1)
                letterFile = formatFiles.Headers{nletterFile}{1}(1);
                if(VERBOSE>=10)
                    fprintf("\n%s %s: T%d LOG: %s",p.Name,formatFiles.TypeFile,nTest,letterFile)
                end
                try
                    datas = test_file_date_time{nTest}{nformatFiles};
                    for nTestN = 1:size(datas,2)
                        nnname = [K.SAVE_DIR '*_Log_' letterFile '__' datas{nTestN}{2} '__' datas{nTestN}{3}];
                        files = ls(nnname);
                        if(files)
                            names_type_test_Nt_letter{nformatFiles}{nTest}{nTestN}.(letterFile) = files;
                            
                            if K.GPU
                                DATA{nformatFiles}{nTest}{nTestN}.(letterFile) = gpuArray(load([K.SAVE_DIR files]));
                            else
                                DATA{nformatFiles}{nTest}{nTestN}.(letterFile) = load([K.SAVE_DIR files]);
                            end
%                             DATA{nformatFiles}{nTest}{nTestN}.(letterFile) = load([K.SAVE_DIR files]);
                            DATA{nformatFiles}{nTest}{nTestN}.(letterFile) = DATA{nformatFiles}{nTest}{nTestN}.(letterFile)(K.Tignore:end - K.Tignore,:);
                            DATA{nformatFiles}{nTest}{nTestN}.(letterFile)(:,1)  =  DATA{nformatFiles}{nTest}{nTestN}.(letterFile)(:,1) - DATA{nformatFiles}{nTest}{nTestN}.(letterFile)(1,1) ;
                            if(VERBOSE>=10)
                                fprintf('\n -> %s',files)
                            end
                        end
                    end
                    
                catch
                    if(VERBOSE>=10)
                        fprintf(' -> ERROR \n')
                    end
                end
                
            end
        end
    end
    Persona{idx_p}.('names_type_test_Nt_letter') = names_type_test_Nt_letter;
    Persona{idx_p}.('DATA') = DATA;
    
    if(VERBOSE>=5)
        fprintf('');FNC.line();
        fprintf('');fprintf(" %7s   : %s %s\n",'Name',p.Name,p.Lastname)   
        fprintf('');fprintf(" %7s   :",'')
        for aux0 = vecNtests
           fprintf("%8s",['T' num2str(aux0)]);
        end
        
        for nformatFiles = 1 : length([TestFilesFormat{:}])
            formatFiles = TestFilesFormat{nformatFiles};
%             fprintf('');fprintf("\n %7s   :",formatFiles.TypeFile)
            for nTest = vecNtests
               toShow = 'X';           
               try
                  testFiles = names_type_test_Nt_letter{nformatFiles}{nTest};
                  if isempty(testFiles)
                      error 'dd'
                  else
                      for NNNNTEST = 1:length(testFiles)
                        fprintf('');fprintf("\n %7s%2d :",formatFiles.TypeFile,NNNNTEST)
                        
                        for aux0 = vecNtests
                           try
                           tf = names_type_test_Nt_letter{nformatFiles}{aux0}{NNNNTEST};
                           names = fieldnames(tf);
                           fprintf("%8s",['' [names{:}]]);
                           catch
                               fprintf("%8s",['-']);
                           end
                        end
                      end
%                       toShow = num2str(length(testFiles));
                  end
               catch
                  
               end
               
%                fprintf("%8s",[toShow]);
            end
        end
        
        fprintf('\n')
    end
    
    if(VERBOSE>=5)
        fprintf('');FNC.line();
    end
    
end