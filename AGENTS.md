# Instructions for agents

This repository holds the user's own Open-XY machines (instruments and send
effects). It is not the SDK.

- **Set up the SDK beside this repository:** `git clone
  https://github.com/etcetc000/open-xy ../open-xy`. That gives its default branch,
  `staging`; do not switch it to `main`. Run SDK commands from here through it,
  for example `python ../open-xy/sdk.py test --machine machines/<id>`.
- **Do not edit the SDK to make a machine work.** Machine code uses only the
  public `<opxy/...>` headers: no assembly, platform conditionals, OS headers or
  raw addresses. Audio callbacks never allocate, block, log or do I/O. If the
  SDK lacks something a machine needs, tell the user. It becomes a separate
  pull request to the SDK's `staging` branch, not part of the machine.
- **Read the examples first:** `machines/mysynth` and `machines/myeffect` here,
  then Open-XY's [core machines](https://github.com/etcetc000/open-xy-core-machines), especially
  [Karplus](https://github.com/etcetc000/open-xy-core-machines/tree/main/machines/karplus) (a synth with an animated screen) and
  [Ping Pong](https://github.com/etcetc000/open-xy-core-machines/tree/main/machines/pingpong) (a send effect with delay memory). The SDK's
  [first machine](https://github.com/etcetc000/open-xy/blob/staging/docs/first-machine.md)
  guide and [machine API](https://github.com/etcetc000/open-xy/blob/staging/docs/api.md)
  are the reference.
- **Each machine keeps its own folder,** ID and `tests/`. Keep build and preview
  output outside this repository.
- **Submitting to the builder** follows [SUBMITTING.md](SUBMITTING.md): tag a
  release here, then open a pull request against the SDK's `main` branch
  that changes **only** `catalog/machines.json`, with this machine's one entry.
  A machine that needs SDK changes only on `staging` targets `staging` instead.
  The SDK's CI refuses a submission that changes anything else.
- **Measure CPU on a device before submitting.** A catalog entry needs a
  hardware `cpu` record from the SDK's [hardware profiling](https://github.com/etcetc000/open-xy/blob/staging/docs/profiling.md):
  build with profiling (a synth's controls are swept by default), have the user
  install it, then collect three runs and run `profile report`. A synth's record
  is its heaviest swept setting. If the readout is above the **recommended 3.5%**
  of the block budget, tell the user which setting is heaviest and suggest making
  that path lighter before submitting; a heavier machine is still accepted, with
  a warning. Never put a host estimate in the record.
- **Device operations,** such as copying firmware to an OP-XY, need the user's
  explicit instruction each time. Host checks do not measure device CPU.
