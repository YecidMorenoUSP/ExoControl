
FIGURES.f_GM_RA_Global = figure('Name','GM_RA_Global','Visible','off');
FIGURES.f_GM_RS_Global = figure('Name','GM_RS_Global','Visible','off');



for p_n = 1:numel([Persona{:}])
    
    p = Persona{p_n};
    FIGURES.(p.Name).fig = figure('Name',p.Name,'Visible','off','Units','normalized');
    tg = uitabgroup(FIGURES.(p.Name).fig,'Position',[0 0 1 1]);
        
    for TypeT = 1:numel(TestFilesFormat)       
        
        FIGURES.(p.Name).(TestFilesFormat{TypeT}.TypeFile).fig = uitab(tg,...
                                'Title',(TestFilesFormat{TypeT}.Name));
        tg0 = uitabgroup(FIGURES.(p.Name).(TestFilesFormat{TypeT}.TypeFile).fig,'Position',[0 0 1 1]);
        
        for i = 1:13
            FIGURES.(p.Name).(TestFilesFormat{TypeT}.TypeFile).(['T' num2str(i) 'f']) = uitab(tg0,'Title',['T' num2str(i)]);
            
            try
                if(numel(p.DATA{TypeT}{i}) > 0)
                    tg2 = uitabgroup(FIGURES.(p.Name).(TestFilesFormat{TypeT}.TypeFile).(['T' num2str(i) 'f']),...
                        'Position',[0 0.1 1 .9],'TabLocation','top');
                                    
                    infoTest = ["Kv: " num2str(p.Kv_RA  (testValues(i,2)+1)) "      " ...
                                "Bv: " num2str(p.Bv_RA  (testValues(i,3)+1)) "      "...
                                "mA: " num2str(p.mA_FES (testValues(i,1)+1))] ; 
%                     uipanel()
                    rsss = annotation(FIGURES.(p.Name).(TestFilesFormat{TypeT}.TypeFile).(['T' num2str(i) 'f']),'textbox',[0 0 1 .1],...
                            'String',[infoTest{:}],...
                            'LineStyle','none','Visible','on','Interpreter','none','HorizontalAlignment','center','VerticalAlignment','middle');
                    for ntest_n = 1:numel(p.DATA{TypeT}{i})
                        trr = uitab(tg2,'Title',['R' num2str(ntest_n)]);
%                         ax = axes(trr,'Position',[.1 .1 .8 .8]);
                        FIGURES.(p.Name).(TestFilesFormat{TypeT}.TypeFile).(['T' num2str(i) '_R' num2str(ntest_n) 'f']) = trr;
%                         FIGURES.(p.Name).(TestFilesFormat{TypeT}.TypeFile).(['T' num2str(i)]).(['R' num2str(ntest_n)]) = ax;
                    end
                else
                    error 'buuu'
                end
                
            catch
                auxxxx = FIGURES.(p.Name).(TestFilesFormat{TypeT}.TypeFile).(['T' num2str(i) 'f']);
                ax = axes(auxxxx,'Position',[0 0 1 1],'Visible','off');
                text(0.5,0.6,"No data yet :(",'HorizontalAlignment','center','FontUnits','normalized',...
                            'fontsize',.1);
            end
        end
        
        FIGURES.(p.Name).(TestFilesFormat{TypeT}.TypeFile).('ALL_f') = uitab(tg0,'Title','ALL');
        tgpos = uitabgroup(FIGURES.(p.Name).(TestFilesFormat{TypeT}.TypeFile).('ALL_f'),'Position',[0 0 1 1],'TabLocation','bottom');
        FIGURES.(p.Name).(TestFilesFormat{TypeT}.TypeFile).('ALL').Position_tab = uitab(tgpos,'Title','Position');
        pos_ax = axes(FIGURES.(p.Name).(TestFilesFormat{TypeT}.TypeFile).('ALL').Position_tab);
        
        set(pos_ax,'xminorgrid','on','yminorgrid','on')
        set(pos_ax,'xgrid','on','ygrid','on')
        hold on 
        
        FIGURES.(p.Name).(TestFilesFormat{TypeT}.TypeFile).('ALL').pos_ax = pos_ax;
    end
end


% FIGURES.(Persona{1}.Name).fig.Visible = 'on';
% FIGURES.(Persona{2}.Name).fig.Visible = 'on';
