﻿#pragma once
#define WAWL_CONSOLE_HPP

#include "ConsoleBaseType.hpp"
#include "BaseUtility.hpp"

namespace wawl {
	namespace fs {
		namespace console {

			inline bool allocConsole() {
				return AllocConsole() != 0;
			}
			inline bool freeConsole() {
				return FreeConsole() != 0;
			}

			inline FileHandle getStdInput() {
				return ::GetStdHandle(STD_INPUT_HANDLE);
			}
			inline FileHandle getStdOutput() {
				return ::GetStdHandle(STD_OUTPUT_HANDLE);
			}
			inline FileHandle getStdError() {
				return ::GetStdHandle(STD_ERROR_HANDLE);
			}

			// write to console
			// return written size
			inline std::uint32_t writeConsole(
				FileHandle consoleOutput,
				const Tstring& str
				) {
				::DWORD writtenSize;

				bool isSuccess = ::WriteConsole(
					consoleOutput,
					str.c_str(),
					static_cast<std::uint32_t>(str.size() + 1),
					&writtenSize,
					nullptr
					) != 0;

				return (isSuccess ? writtenSize : 0);
			}

			inline std::uint32_t readConsole(
				FileHandle consoleInput,
				Tstring& buffer,
				std::uint32_t size
				) {
				::DWORD readSize;

				buffer.resize(size);

				bool isSuccess = ::ReadConsole(
					consoleInput,
					&buffer[0],
					size,
					&readSize,
					nullptr
					) != 0;

				return (isSuccess ? readSize : 0);
			}

			inline bool setConsoleStrColor(
				FileHandle consoleOutput,
				StrColor color
				) {
				return ::SetConsoleTextAttribute(consoleOutput, unpackEnum(color)) != 0;
			}

		} // ::wawl::fs::console
	} // ::wawl::fs
} // ::wawl