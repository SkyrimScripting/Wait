#include "Windows.h"

void InitializeLog() {
	auto path = logger::log_directory();
	if (!path) stl::report_and_fail("Failed to find standard logging directory"sv);
	*path /= fmt::format("{}.log", SKSE::PluginDeclaration::GetSingleton()->GetName());
	auto sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(path->string(), true);
	const auto level = spdlog::level::trace;
	auto log = std::make_shared<spdlog::logger>("global log"s, std::move(sink));
	log->set_level(level);
	log->flush_on(level);
	spdlog::set_default_logger(std::move(log));
	spdlog::set_pattern("%g(%#): [%^%l%$] %v"s);
}

SKSEPluginLoad(const SKSE::LoadInterface* skse) {
    InitializeLog();
    logger::info("Let's wait!");
    MessageBoxA(NULL, "Press OK when you're ready!", "Skyrim", MB_OK | MB_ICONQUESTION);
    logger::info("Done waiting.");
    SKSE::Init(skse);
    return true;
}
