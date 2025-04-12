{
  description = "X11 Audio Visualizer for ALSA";

  outputs = {
    self,
    nixpkgs,
  }: let
    systems = ["x86_64-linux" "aarch64-linux"];
    # Need to validate before pushing "x86_64-darwin" "aarch64-darwin"

    forAllSystems = f: nixpkgs.lib.genAttrs systems (system: f system);

    nixpkgsFor = forAllSystems (system:
      import nixpkgs {
        inherit system;
        overlays = [self.overlay];
      });
  in rec {
    overlay = final: prev: {
      kiss-mpris-properties = final.stdenv.mkDerivation {
        name = "kiss-mpris-properties";
        version = "unstable";
        description = "Obtain information about the current tracks being played";

        src = self;

        cmakeFlags = [
          (final.lib.cmakeBool "CMAKE_SKIP_BUILD_RPATH" true)
        ];

        nativeBuildInputs = with final; [
          # Compiling and fetching dependencies
          gcc
          cmake
          pkg-config
        ];

        buildInputs = with final; [
          dbus
        ];
      };
    };

    packages =
      forAllSystems (system: {inherit (nixpkgsFor.${system}) kiss-mpris-properties;});

    devShell = forAllSystems (system:
      nixpkgs.legacyPackages.${system}.mkShell {
        inputsFrom = builtins.attrValues (packages.${system});
      });
  };
}
