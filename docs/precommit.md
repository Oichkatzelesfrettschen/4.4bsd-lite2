# Using pre-commit

This repository provides a `.pre-commit-config.yaml` with hooks for
`clang-format`, `clang-tidy`, `shellcheck` and `codespell`. After cloning the
repository run `pre-commit install --install-hooks` to set up the local git
hooks. Running `setup.sh` installs the `pre-commit` tool via both `apt` and
`pip`, installs `codespell`, and Codex automation calls `.codex/setup.sh` to
ensure these tools are present in CI.
The wrapper also installs additional theorem provers such as Agda and Isabelle/HOL to
support formal verification tasks and automatically configures the git hooks.
The script also installs `shellcheck` using `apt_pin_install` with a fallback to `pip`. Additional Python
tools such as `configuredb`, `pytest`, `pyyaml`, `pylint` and `pyfuzz` are
installed through `pip` as well. After executing
the script no manual steps are needed, but you can re-install the hooks any
time:

```sh
pre-commit install --install-hooks
```

The hooks rely on the configuration files `.clang-format` and
`.clang-tidy` at the repository root.  A helper script
`tools/run_clang_tidy.sh` selects the appropriate language standard
(C2x for C or C++17) when invoking `clang-tidy`.

Shell scripts (`*.sh`) are linted with `shellcheck`.
Use `tools/generate_compiledb.sh` to create a `compile_commands.json` file for
`clang-tidy`.
A `.gitignore` file at the repository root prevents common build artifacts from
being committed. Patterns include `*/obj/`, `*.o`, `*.a`, `*.log` and the
`compile/` directory.
