# Open-XY machine template

Start an [Open-XY](https://github.com/etcetc000/open-xy) machine in a repository of
your own. A machine is portable C++ against the Open-XY SDK: a synth, with its
own sound and screen, or a send effect. Your machines live here, you release
them by tagging, and the Open-XY catalog pins the version it ships.

| Folder | Kind |
| --- | --- |
| [machines/mysynth](machines/mysynth) | Synth: voices, a 64-sample render and a drawing display |
| [machines/myeffect](machines/myeffect) | Send effect: in-place stereo processing on the FX page |

Each folder is one machine: `definition.json` (controls, presets, resources),
`machine.json` (kind, SDK version, identity), its C++ and, for a synth, its
artwork. Instruments also include `presets/default.json`, their device starting
sound. `tests/` holds the machine's own checks.

## Start

1. Use this template on GitHub, and clone the Open-XY SDK next to it:
   `git clone https://github.com/etcetc000/open-xy`. Follow its
   [first machine](https://github.com/etcetc000/open-xy/blob/staging/docs/first-machine.md)
   guide to install Python, Node and Clang.
2. Replace the examples with your own machines, each with an ID of its own:

   ```sh
   python ../open-xy/sdk.py new --kind synth --id <id> --name "<Name>" --out machines/<id>
   python ../open-xy/sdk.py new --kind effect --id <id> --name "<Name>" --out machines/<id>
   ```

   Keep one machine, or several. A single machine may also sit at the
   repository root.
3. Hear and see a synth while you work on it:

   ```sh
   python ../open-xy/sdk.py preview --machine machines/<id> --out ../previews/<id>-001
   python ../open-xy/tools/serve_harness.py --preview ../previews/<id>-001
   ```

4. Edit the generated `presets/default.json` to choose your instrument's
   starting sound. Keep its `type` equal to your machine ID. Submissions must
   include it in the release; see the SDK's
   [default preset contract](https://github.com/etcetc000/open-xy/blob/staging/docs/api.md#default-preset).
   Send effects use definition defaults and need no instrument preset.

   Check everything as CI does: records, defaults, sources, previews and your tests.

   ```sh
   python ../open-xy/sdk.py test --machine machines/<id> --cxx clang++ --host-cxx g++
   ```

   Add `--firmware` once the pinned Blackfin tools are installed
   (`python ../open-xy/sdk.py toolchain fetch`) to compile the firmware module
   with your machines.
5. Build firmware for your own OP-XY with
   `python ../open-xy/sdk.py build --machine machines/<id> --stock-os ... --stock-content ... --out ...`
   ([building firmware](https://github.com/etcetc000/open-xy/blob/staging/docs/build.md)).

Keep build and preview output outside this repository: the SDK refuses output
inside a machine folder.

## CI

[.github/workflows/machines.yml](.github/workflows/machines.yml) checks every
machine against the SDK named by `OPEN_XY_REF`: the machine checks on Linux,
and a firmware compile with the bundled machines on Windows. Point
`OPEN_XY_REF` at the SDK release your machines' `"sdk"` targets.

## Sharing your machine

To have a machine in the Open-XY builder, follow [SUBMITTING.md](SUBMITTING.md).
