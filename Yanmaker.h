#pragma once
#include <filesystem>
#include <regex>
#include <string>


using namespace std;
namespace fs = std::experimental::filesystem;

namespace Yan
{
	void Yan_execute();
};

void Yan::Yan_execute()
{
	regex file(R"((.*)([а-€ј-я]+)(ова?|ина?|ева?|ий|ой|ич|а€|ко|их)(.*\.\w+))");
	regex directory(R"((.*)([а-€ј-я]+)(ова?|ина?|ева?|ий|ой|ич|а€|ко|их)(.*))");
	smatch cm;
	string str;
	fs::path p(fs::current_path());

	if (!fs::exists(p))
		return;
	
	if (fs::is_directory(p))
	{
		fs::directory_iterator end_iter;
		for (fs::directory_iterator dir_itr(p);
			dir_itr != end_iter;
			++dir_itr)
		{
			try
			{
				if (fs::is_regular_file(dir_itr->status()))
				{
					str = dir_itr->path().filename().string();
					if (regex_match(str, cm, file))
					{
						str = regex_replace(str, file, "$1$2€н$4");
						fs::path newpath(p / str);
						fs::rename(dir_itr->path(), newpath);
					}

				}
				else if (fs::is_directory(dir_itr->status()))
				{
					str = dir_itr->path().filename().string();
					if (regex_match(str, cm, directory))
					{

						str = regex_replace(str, directory, "$1$2€н$4");
						fs::path newpath(p / str);
						fs::rename(dir_itr->path(), newpath);
					}
				}
			}
			catch (const std::exception&)
			{
				return;
			}
		}
	}
}


