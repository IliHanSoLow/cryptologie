let
pkgs = import <nixpkgs>{};

# This is the Python version that will be used.
myPython = pkgs.python312;

pythonWithPkgs = myPython.withPackages (pythonPkgs: with pythonPkgs; [
	build
	ipython
	pip
	setuptools
	virtualenvwrapper
	wheel
]);

lib-path = with pkgs; lib.makeLibraryPath [
    libffi
    openssl
    stdenv.cc.cc
];

shell = pkgs.mkShellNoCC {
    buildInputs = [
	pythonWithPkgs

# other packages needed for compiling python libs
	    pkgs.readline
	    pkgs.libffi
	    pkgs.openssl

# unfortunately needed because of messing with LD_LIBRARY_PATH below
	    pkgs.git
	    pkgs.openssh
	    pkgs.rsync
    ];

    venvDir = ".venv";
    src = null;
    postVenv = ''
	unset SOURCE_DATE_EPOCH
	'';
    postShellHook = ''
	unset SOURCE_DATE_EPOCH
	unset LD_PRELOAD

	PYTHONPATH=$PWD/$venvDir/${myPython.sitePackages}:$PYTHONPATH
	'';
};
in

shell
