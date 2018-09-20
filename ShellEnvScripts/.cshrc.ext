# begin .cshrc.ext

echo "sourcing .cshrc.ext"

if (-e $HOME/.dbgdot) then
 echo "entering .cshrc.ext"
endif
#
# User additions to .cshrc go in this file
#
#setenv SETUP_MJSW201610PROD true
#setenv SETUP_MJSW201705PROD true
#setenv SETUP_MJSW201706PROD true
setenv SETUP_MJSW201802PROD true
#source /common/majorana/scripts/setupMajorana.csh
#source /project/projectdirs/majorana/setupMajorana.csh
source /project/projectdirs/majorana/software/sl64/setupMajoranaSL64.csh
setenv ROOT_INCLUDE_PATH {$ROOT_INCLUDE_PATH}:$GATDIR
alias emacsr emacs -cr white -ms white  -fg white -bg \#101820
alias xt xterm -bg \#101820 -fg LightBlue
alias root root -l
setenv BBDECAY /global/projecta/projectdirs/majorana/users/jrager/LowE/QCPlotsDS6/gatified/BBdecay/
#alias test /global/projecta/projectdirs/majorana/users/jrager/LowE/QCPlotsDS6/gatified/test/
#alias 228Th /global/projecta/projectdirs/majorana/users/jrager/LowE/QCPlotsDS6/gatified/228Th/
setenv LOWE /global/u1/j/jrager/LowE/

setenv NERSC_HOST `/usr/common/usg/bin/nersc_host`

if ($NERSC_HOST == "davinci") then
#  Replace the following line with personal settings for davinci
 touch /dev/null
endif

if ($NERSC_HOST == "datatran") then
#  Replace the following line with personal settings for datatran
 touch /dev/null
endif

if (-e $HOME/.dbgdot) then
 echo "exiting .cshrc.ext"
endif

# end .cshrc.ext