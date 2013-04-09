% rapport.cls
% Copyright 2010 Morten Engelhardt Olsen

% TODO
% fancyhead

% Identification
\NeedsTeXFormat{LaTeX2e}
\ProvidesClass{ntnurapport}[2010/11/26]

% Init
\RequirePackage{ifthen}
\RequirePackage{amsmath,amsfonts,amssymb}
\RequirePackage{calc}
\RequirePackage{float}
\RequirePackage{tabularx}
\RequirePackage{graphicx}
\RequirePackage{ifpdf}
	\ifpdf
  		\RequirePackage{ae}
  		\PackageInfo{ntnurapport}{PDF output detected, loading ae}
  	\else
  		%\PackageWarning{ntnurapport}{Package only tested using pdfTeX. Strange results may occur.}
\fi

% Declaration
\provideboolean{UseNorwegianLanguage}
\provideboolean{UseKYBImageFooter}
\provideboolean{UseFooterImage}
\DeclareOption{norsk}{
    \setboolean{UseNorwegianLanguage}{true}
    \setboolean{UseKYBImageFooter}{false}
    \PassOptionsToClass{\CurrentOption}{article}
}
\DeclareOption{norwegian}{
    \setboolean{UseNorwegianLanguage}{true}
    \setboolean{UseKYBImageFooter}{false}
    \PassOptionsToClass{\CurrentOption}{article}
}
\DeclareOption{titlepage}{
    \relax
}

\DeclareOption{kybimage}{
	\setboolean{UseKYBImageFooter}{true}
}
\DeclareOption{footerfig}{
    \setboolean{UseFooterImage}{true}
}
\DeclareOption*{
    \PackageInfo{ntnurapport}{Unknown option `\CurrentOption`, 
        Passing option to baseclass.}
    \PassOptionsToClass{\CurrentOption}{article}
}

% Execute declarations
\ProcessOptions \relax

% Load basepackage
\LoadClass[titlepage]{article}

% Definiitions
\numberwithin{equation}{section}
\numberwithin{figure}{section}
\numberwithin{table}{section}
\restylefloat{figure}
\DeclareGraphicsExtensions{.pdf, .png}
\DeclareGraphicsRule{.tif}{png}{.png}{`convert #1 `basename #1 .tif`.png}
\DeclareGraphicsRule{.eps}{pdf}{.eps}{`epstopdf #1 `}
\renewcommand{\@author}{}
\newcommand{\@supervisor}{}
\newcommand{\@subsupervisor}{}
\newcommand{\@course}{}
\renewcommand{\@title}{}
\newcommand{\@group}{}
\renewcommand{\@date}{}
\newcommand{\@tpfigure}{}
\newcommand{\@overtitle}{}

% Language definitons
\newcommand{\ntrap@byNO}{}
\newcommand{\ntrap@byEN}{}
\newcommand{\ntrap@reportNO}{Rapport}
\newcommand{\ntrap@reportEN}{Report}
\newcommand{\ntrap@groupNO}{Gruppe}
\newcommand{\ntrap@groupEN}{Group}

% Interface
\renewcommand{\author}[1]{\renewcommand{\@author}{#1}}
\newcommand{\supervisor}[1]{\renewcommand{\@supervisor}{#1}}
\newcommand{\subsupervisor}[1]{\renewcommand{\@subsupervisor}{#1}}
\renewcommand{\date}[1]{\renewcommand{\@date}{#1}}
\renewcommand{\title}[1]{\renewcommand{\@title}{#1}}
\newcommand{\course}[1]{\renewcommand{\@course}{#1}}
\newcommand{\group}[1]{\renewcommand{\@group}{#1}}
\newcommand{\titlepagefigure}[1]{\renewcommand{\@tpfigure}{#1}}
\newcommand{\overtitle}[1]{\renewcommand{\@overtitle}{#1}}

% Helpfunctions
\newcommand{\HRule}{\noindent\rule{\linewidth}{1mm}}

% Titlepage
\renewcommand{\maketitle}{{%
\vspace{-20ex}
\begin{titlepage}
    \begin{center}
    	
        \large
        \@course \par
        \vspace{0.0ex}
        \HRule \par 
%        \huge
%        \ifthenelse{\equal{\@overtitle}{}}{ %
%            \ifthenelse{\boolean{UseNorwegianLanguage}}{ %
%                \textbf{\ntrap@reportNO} }{
%                \textbf{\ntrap@reportEN} }
%        }{
%        \textbf{\@overtitle} \
%        }
%        
%        \vspace{5mm}
        \huge \textit{\@title} \par
        \HRule 
        \vspace{0.3ex}

        \ifthenelse{\boolean{UseNorwegianLanguage}}{ %
            \large\ntrap@byNO \par}{
            \large\ntrap@byEN \par}%
        \vspace{0.3ex}    
        \begin{tabular}[t]{c}%
            \@author
        \end{tabular}\par %
        \ifthenelse{\equal{\@tpfigure}{}}{%
            }{
            \vspace{0.3ex}%
            \begin{figure}[H]
                \centering
                \includegraphics[width = 0.8\textwidth ]{\@tpfigure}
            \end{figure}
            \vfill
        }
        \vfill
        Veileder: \par
        \begin{tabular}[t]{c}%
                    \@supervisor
                \end{tabular}\par %
        \vspace{0.3ex}
        %Biveileder:\par      
        \begin{tabular}[t]{c}%
                    \@subsupervisor
                \end{tabular}\par %    
                        \vspace{0.3ex}    
        \ifthenelse{\equal{\@group}{}}{ %
            }{
            \ifthenelse{\boolean{UseNorwegianLanguage}}{ %
                \ntrap@groupNO \space \@group \par}{
                \ntrap@groupEN \space \@group \par}
            }%
        %\vfill
        \ifthenelse{\equal{\@date}{}}{ %
            }{
            \@date \par 
        }     
        \vspace{0.3ex}
        \textsc{Institutt for Teknisk Kybernetikk}\par
        \textsc{Fakultet for Informasjonsteknologi, \\ Matematikk og Elektroteknikk} \par
        \textsc{Norges Teknisk-Naturvitenskapelige Universitet} \par
        \ifthenelse{\boolean{UseFooterImage}}{ %
            \ifthenelse{\boolean{UseNorwegianLanguage}}{
                \ifthenelse{\boolean{UseKYBImageFooter}}{
                    \begin{figure}[H]
                        \centering
                        \includegraphics[width = 0.4\textwidth ]{img/kyb_logo_no}
                    \end{figure}
                }{
                    \begin{figure}[H]
                        \centering
                        \includegraphics[width = 0.4\textwidth ]{img/ntnu_logo_no}
                    \end{figure}
            }}{
                \ifthenelse{\boolean{UseKYBImageFooter}}{
                    \begin{figure}[H]
                        \centering
                        \includegraphics[width = 0.4\textwidth ]{img/kyb_logo_en}
                    \end{figure}
                }{
                    \begin{figure}[H]
                        \centering
                        \includegraphics[width = 0.4\textwidth ]{img/ntnu_logo_en}
                    \end{figure}
            }}
        }{}
        \vspace{0.3ex}
    \end{center}
    \normalsize
\end{titlepage}
}}
