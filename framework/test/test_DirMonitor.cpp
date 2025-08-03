/***********************************************
*     __	@author Idan Kideckel
* ___( o)>	@date 2025-03-22
* \ <_. )	@Ex 
*  `---' 	@reviewer Liad		 	 				
************************************************/

#include "DllLoader.hpp"
#include "DirMonitor.hpp"

int main()
{
	ilrd::DirMonitor moniter("/home/idan/Desktop/git/projects/final_project/framework/plugins/");
	ilrd::DllLoader loader;

	ilrd::Callback<ilrd::DllLoader, const std::string&>callback(loader,  &ilrd::DllLoader::Load, nullptr);
	moniter.Register(reinterpret_cast<ilrd::ACallback<const std::string&>*>(&callback));

	moniter.Run();

	char to_close = '0';
	while(true)
    {
		to_close = getc(stdin);
		if(to_close == 'q')
		{
			break;
		}
	}

	return 0;
}
