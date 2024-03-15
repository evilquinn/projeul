#include <iostream>
#include <chrono>
#include <format>
#include <string_view>
#include <cstdlib>
#include <filesystem>
#include <algorithm>
#include <fstream>

const auto& tzdb = std::chrono::get_tzdb();

const std::chrono::time_zone*
    do_locate_zone(const std::vector<std::chrono::time_zone>& zones,
		   const std::vector<std::chrono::time_zone_link>& links,
		   std::string_view tz_name) noexcept
    {
      // Lambda mangling changed between -fabi-version=2 and -fabi-version=18
      auto search = []<class Vec>(const Vec& v, std::string_view name) {
	auto pos = std::ranges::lower_bound(v, name, {}, &Vec::value_type::name);
	auto ptr = pos.base();
	if (pos == v.end() || pos->name() != name)
	  ptr = nullptr;
	return ptr;
      };

      if (auto tz = search(zones, tz_name))
	return tz;

      if (auto tz_l = search(links, tz_name))
	return search(zones, tz_l->target());

      return nullptr;
    }

  // Implementation of std::chrono::tzdb::current_zone().
  const std::chrono::time_zone*
  current_zone()
  {
    // TODO cache this function's result?

#ifndef _AIX
    // Repeat the preprocessor condition used by filesystem::read_symlink,
    // to avoid a dependency on src/c++17/fs_ops.o if it won't work anyway.
#if defined(_GLIBCXX_HAVE_READLINK) && defined(_GLIBCXX_HAVE_SYS_STAT_H)
    std::error_code ec;
    // This should be a symlink to e.g. /usr/share/zoneinfo/Europe/London
    auto path = std::filesystem::read_symlink("/etc/localtime", ec);
    if (!ec)
      {
	auto first = path.begin(), last = path.end();
	if (std::distance(first, last) > 2)
	  {
	    --last;
	    std::string name = last->string();
	    if (auto tz = do_locate_zone(tzdb.zones, tzdb.links, name))
	      return tz;
	    --last;
	    name = last->string() + '/' + name;
	    if (auto tz = do_locate_zone(tzdb.zones, tzdb.links, name))
	      return tz;
	  }
      }
#endif
    // Otherwise, look for a file naming the time zone.
    std::string_view files[] {
      "/etc/timezone",    // Debian derivates
      "/var/db/zoneinfo", // FreeBSD
    };
    for (auto f : files)
      {
	std::ifstream tzf{std::string{f}};
	if (std::string name; std::getline(tzf, name))
	  if (auto tz = do_locate_zone(tzdb.zones, tzdb.links, name))
	    return tz;
      }

    if (std::ifstream tzf{"/etc/sysconfig/clock"})
      {
	std::string line;
	// Old versions of Suse use TIMEZONE. Old versions of RHEL use ZONE.
	const std::string_view keys[] = { "TIMEZONE=" , "ZONE=" };
	while (std::getline(tzf, line))
	  for (std::string_view key : keys)
	    if (line.starts_with(key))
	      {
		std::string_view name = line;
		name.remove_prefix(key.size());
		if (name.size() != 0 && name.front() == '"')
		  {
		    name.remove_prefix(1);
		    if (auto pos = name.find('"'); pos != name.npos)
		      name = name.substr(0, pos);
		  }
		if (auto tz = do_locate_zone(tzdb.zones, tzdb.links, name))
		  return tz;
	      }
      }
#else
    // AIX stores current zone in $TZ in /etc/environment but the value
    // is typically a POSIX time zone name, not IANA zone.
    // https://developer.ibm.com/articles/au-aix-posix/
    // https://www.ibm.com/support/pages/managing-time-zone-variable-posix
    if (const char* env = std::getenv("TZ"))
      {
	// This will fail unless TZ contains an IANA time zone name.
	if (auto tz = do_locate_zone(this->zones, this->links, env))
	  return tz;
      }
#endif

    // Default to UTC.
    if (auto tz = do_locate_zone(tzdb.zones, tzdb.links, "UTC"))
      return tz;

    throw std::runtime_error("tzdb: cannot determine current zone");
  }


int main()
{
    auto p1 = std::chrono::system_clock::time_point(std::chrono::seconds(1729989000));
    std::cout << std::format("{:%FT%T%z} {}", p1, p1.time_since_epoch()) << std::endl;

    auto tzp = current_zone();
    auto p2 = tzp->to_local(p1);
    std::cout << std::format("{:%FT%T} {}", p2, p2.time_since_epoch()) << std::endl;

    auto p3 = tzp->to_sys(p2);
    std::cout << std::format("{:%FT%T%z} {}", p3, p3.time_since_epoch()) << std::endl;

    return 0;
}
