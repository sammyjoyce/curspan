# Changelog

All notable changes to this template are documented here.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/), and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

### Changed

- TUI support is compiled in by default; pass `-Denable-tui=false` to build a
  headless-only binary.
- Bare `myapp` on a TTY now opens the interactive TUI menu, while command
  invocations continue to use the CLI command table.
- Command output defaults to versioned JSON when stdout is not a terminal;
  pass `--plain` to preserve human text under pipes or redirection.
- Failing to open an explicit `--config` file now reports the specific public
  exit code — `NOT_FOUND` (17) for a missing path or `PERMISSION` (12) for an
  unreadable one — instead of a blanket I/O error (11).
- The interactive TUI now responds to `Esc` promptly (ESCDELAY tuned to 25 ms)
  rather than pausing up to a second on every Esc affordance.

### Added

- Experimental bare non-TTY headless protocol: read a JSON request from stdin
  and dispatch it through the existing command table.
- Unknown-command errors suggest the closest command ("Did you mean ...?"),
  computed over the visible command table.
- Color output honours the de-facto `FORCE_COLOR`, `CLICOLOR_FORCE`, and
  `CLICOLOR` environment variables, documented in `--help` and the OpenCLI
  contract.
- The TUI Commands browser now lists each command's example invocations
  alongside its summary.

### Fixed

- Headless JSON requests accept RFC 8259 `\uXXXX` escapes (including UTF-16
  surrogate pairs), matching what standard JSON serializers emit.
- A config file with an unknown key whose value is a nested object or array no
  longer fails the whole load; the value is skipped and known sibling keys
  still apply.
- `FORCE_COLOR=0` now disables color instead of (as before) enabling it.
- The TUI Commands browser hides commands marked hidden from `--help`, so it no
  longer lists the internal `menu` command.

## [0.1.0]

### Added

- Initial template: C23 sources under `src/`, Zig 0.16 build system, opt-in ncurses/PDCurses TUI behind `-Denable-tui=true`.
- Live OpenCLI contract. `myapp opencli` prints the spec, and `zig build test` fails if it drifts from `opencli.json`.
- Reusable `tui-menu-lib` static library target with installed headers.
- Three test layers: in-process unit tests (`zig build unit-test`), CLI contract tests, and Ghostty-VT-backed PTY/TUI scenarios.
- GitHub Actions CI on Linux, macOS, and Windows, plus `clang-tidy`, `cppcheck`, Gitleaks, OpenSSF Scorecard, SBOM generation, and pinned action versions.
- Template cleanup workflow and setup scripts for customizing a generated project.
- Nix dev shell, devcontainer, pre-commit configuration (clang-format, markdownlint, conventional-commit), and Dependabot.

[Unreleased]: https://github.com/yourusername/yourproject/compare/v0.1.0...HEAD
[0.1.0]: https://github.com/yourusername/yourproject/releases/tag/v0.1.0
