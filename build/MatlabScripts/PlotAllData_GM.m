global Persona VERBOSE FIGURES TestFilesFormat K testValues

for p_n = 2%1:numel([Persona{:}])
    
    p = Persona{p_n};
    
    if VERBOSE >= 5
        disp(['Graficando los datos de : ' p.Name ' '  p.Lastname])
    end
    
    FIGURES.(p.Name).fig.Visible = 'on';
    drawnow
    
%     pause(.2) % Resolvedo o problema da fome mundial
    
    set(0,'CurrentFigure',FIGURES.(p.Name).fig)
    gcf_ = FIGURES.(p.Name).fig;
    drawnow
            
    for TypeT = 1:numel(TestFilesFormat)       
            
        for i = 1:13
                        
            try
                if(numel(p.DATA{TypeT}{i}) > 0)
                    for ntest_n = 1:numel(p.DATA{TypeT}{i})
                        
%                         fig = FIGURES.(p.Name).(TestFilesFormat{TypeT}.TypeFile).(['T' num2str(i)]).( ['R' num2str(ntest_n)]);
                        fig2 = FIGURES.(p.Name).(TestFilesFormat{TypeT}.TypeFile).(['T' num2str(i)  '_R' num2str(ntest_n) 'f']);
%                         clf(fig2)

                        drawnow
                        delete(findall(fig2,'type','uitabgroup'))
                                          
                        data = p.DATA{TypeT}{i}{ntest_n};                       
                        namesLog = fieldnames(data);                   
                     
                        if(VERBOSE>=10)
                            disp(['DONE' num2str(i) ' -> ' TestFilesFormat{TypeT}.TypeFile ' - ' [namesLog{:}] ' T ' num2str(ntest_n) ])
                        end
                        
                        infoTest = ["Kv: " num2str(p.Kv_RA  (testValues(i,2)+1)) "      " ...
                                    "Bv: " num2str(p.Bv_RA  (testValues(i,3)+1)) "      "...
                                    "mA: " num2str(p.mA_FES (testValues(i,1)+1))] ; 
                        
                        strnamesLog = [namesLog{:}];
                        switch(TestFilesFormat{TypeT}.TypeFile)
                            case "GM_RA"
                                
                                all_ax = FIGURES.(p.Name).(TestFilesFormat{TypeT}.TypeFile).('ALL').pos_ax;
                                
                                if contains(strnamesLog,"R") && contains(strnamesLog,"L")
                                    
                                    tg = uitabgroup(fig2,'Position',[0 0 1 1],'TabLocation','bottom');
                                    tabPos = uitab(tg,'Title','Position');

                                    axx = axes(tabPos);
                                    set(gcf,'CurrentAxes',axx);
                                    cla(axx)
                                                                    
                                    ax_vP = [];
                                    ax_vP(1) = subplot(1,1,1);
                                                                       
                                    for ax_v_i = 1:1:length(ax_vP)
                                        set(gcf,'CurrentAxes',ax_vP(ax_v_i));
                                        hold on
                                        cla(ax_vP(ax_v_i))
                                        set(ax_vP(ax_v_i),'xminorgrid','on','yminorgrid','on')
                                        set(ax_vP(ax_v_i),'xgrid','on','ygrid','on')
                                        drawnow
                                    end
                                    
%                                     {'Robot'    'Time' 'Pos' 'Fore'}, ...
%                                     {'Logs'     'Time' 'Fes' 'D_ref' 'ref'}, ...
%                                     {'EMG'      'Time' 'EMG2' 'EMG3' 'EMG10' 'EMG11'}
                                     
                                    time  = data.R(:,1)';
                                    pos   = data.R(:,2)';
                                    force = data.R(:,3)';
                                    fes   = data.L(:,2)';
                                    D_ref = data.L(:,3)';
                                    ref   = data.L(:,4)';
                                    
                                    maxY = gather(max([pos,ref]));
                                    minY = gather(min([pos,ref]));
                                    
                                    fes_norm = fes/max(fes);
                                    fes01 = strfind( gather(fes_norm),[0,1]);
                                    fes10 = strfind( gather(fes_norm),[1,0]);
                                    
                                    for tBox = [fes01 ; fes10]
                                        rectangle('Position',gather([ time(tBox(1)) minY  time(tBox(2)-tBox(1)) (maxY - minY)]),...
                                                  'Parent',ax_vP(1),...
                                                  'LineStyle','none',...
                                                  'FaceColor',[0 0 0 .15]);
                                    end
                                    K.STYLE.ref1 = {'LineStyle','--','linewidth',2,'Color',[0.4660 0.6740 0.1880 .8]};
                                    K.STYLE.pos1 = {'LineStyle','-','linewidth',1,'Color',[0.9290 0.6940 0.1250]};
                                    K.STYLE.pos_f1 = {'LineStyle','-','linewidth',2,'Color',[0 0.4470 0.7410 0.3]};
                                    K.STYLE.pos_f2 = {'LineStyle','-','linewidth',2,'Color',[0.9290 0.6940 0.1250 0.3]};
                                    K.STYLE.pos_f3 = {'LineStyle','-','linewidth',2,'Color',[0.4660 0.6740 0.1880 0.3]};
                                    K.STYLE.fes1 = {'LineStyle','-','linewidth',1,'Color',[0 0 0 .15]};
                                    
                                    plot(time(1:10:end),ref(1:10:end),'Parent',ax_vP(1),K.STYLE.ref1{:})
                                    plot(time,pos,'Parent',ax_vP(1),K.STYLE.pos1{:})
                                    plot(time,fes_norm*(maxY - minY) - abs(minY), 'Parent',ax_vP(1), K.STYLE.fes1{:})   
                                    
                                    
                                    
                                    plot(time,pos,'Parent',all_ax,K.STYLE.(['pos_f' num2str(testValues(i,1)+1)]){:})
                                    
                                    drawnow
                                    
                                    set(gcf_,'CurrentAxes',ax_vP(1))
                                    title('Postition');
                                    xlabel('Time [s]');
                                    ylabel('Position [rad]');
                                    ylim( [minY maxY] )
                                    lcn = legend({'Ref','Pos','FES'});
                                    lcn.Location = 'south';
                                    lcn.Orientation = 'horizontal';
                                    drawnow
                                    
%                                     set(gcf_,'CurrentAxes',ax_vP(2));
%                                     title('Logs');
%                                     drawnow
                                    
                                    for ax_v_i = 1:1:length(ax_vP)
                                        set(gcf,'CurrentAxes',ax_vP(ax_v_i));
                                        xlim(gather([0 data.R(end,1)]))
                                        hold off
                                        drawnow
                                    end
                                    
                                    
                                    
                                end
                                
                            case "GM_RS"
%                                 switch(namesLog{TypeLog})
%                                     case "L"
% 
%                                         set(gcf,'CurrentAxes',ax_v(1));
%                                         hold on
%                                         plot(sd(:,1)',sd(:,7),'Parent',ax_v(1))
%                                         plot(sd(:,1)',sd(:,10),'Parent',ax_v(1))
% %                                             plot(sd(:,1)',sd(:,11),'Parent',ax_v(1))
%                                         hold off
%                                         grid minor
%                                     case "E"
%                                 end    
                        end
                            
                        
                        if(VERBOSE>=10)
                            disp(['DONE -> ' TestFilesFormat{TypeT}.TypeFile ' - ' [namesLog{:}] ])
                        end
                                                
                    end
                else
            
                end
                
            catch
%               disp ("Hubo Un Error" )
            end
        end
        
    end
    
    
    
end