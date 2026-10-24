# Submitting a machine to Open-XY

The Open-XY builder ships the machines listed in its catalog,
[`catalog/machines.json`](https://github.com/etcetc000/open-xy/blob/staging/catalog/machines.json)
in the Open-XY repository. Your machine stays in your repository; the catalog
pins one tagged commit of it. You never copy code into Open-XY.

## 1. Reserve the identity

A machine's ID, its engine or effect ID and its page are saved in every preset
and project made with it, so they never change once published. Reserve them
before you share anything:

- **ID**: your `definition.json` `id`. A lowercase letter, then up to 14
  lowercase letters, digits or underscores, unused in the catalog.
- **Synth**: a free engine ID and page. **Effect**: a free effect ID. Effect
  IDs are scarce, so reserve one only for an effect you intend to publish.

Open a pull request against the catalog that adds your machine with
`"status": "reserved"`, then put the same identity in your `machine.json`.
Until then, `sdk.py new` picks IDs that are free in the SDK, which is enough for
your own builds.

## 2. Meet the requirements

| Requirement | How it is checked |
| --- | --- |
| The machine targets a released SDK (`"sdk"` in `machine.json`) | `sdk.py test` |
| C++ uses only the public headers (`<opxy/...>`): no assembly, platform conditionals or OS headers | `sdk.py test`, then review |
| Audio callbacks never allocate, block, log or do I/O | Review |
| Your own checks in `tests/*.cpp` pass: sound bounds, tuning, decay, whatever the machine promises | `sdk.py test` |
| CI is green, including the firmware compile | Your repository's CI |
| It fits beside the bundled machines in the shared 2044 KiB module | The firmware compile prints each machine's share |
| A licence that allows redistribution in firmware: `LICENSE` at the root, and `vendor/LICENSE` for vendored code | Review |
| A short `description` in `machine.json`; a builder `icon` is optional | `sdk.py test` |

## 3. Release and submit

1. Tag the commit to publish, for example `v1.0.0`, and push the tag.
2. Open a pull request against the catalog that changes your entry to:

   ```json
   {"id": "<id>", "repository": "https://github.com/<you>/<repo>", "tag": "v1.0.0",
    "commit": "<the tag's full commit SHA>", "path": "machines/<id>",
    "identity": {"engine": 12, "page": 90}, "maintainer": "<your GitHub user>",
    "status": "published"}
   ```

   `path` is the machine's folder in your repository (`"."` at the root).
3. The catalog's CI fetches exactly that commit and runs the same checks as your
   CI. A maintainer then reviews the code once, in full, and listens to it.

Merged machines reach the beta site (beta.open-xy.com) with the next catalog
release, then the main site with the next Open-XY release.

## 4. Updates

Tag a new version and open a pull request that moves your entry's `tag` and
`commit`. It is checked the same way and reviewed as a diff. A change of ID or
identity is refused: release a new machine instead.

## Removal

A maintainer can remove a machine that is abandoned or harmful, or you can ask
for removal. Its entry stays as `"status": "retired"`, so its identity is never
reused and old projects never load a different machine.
