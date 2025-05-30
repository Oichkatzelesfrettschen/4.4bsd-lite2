#!/bin/sh
set -e
# build library and tests
make -C .. >/dev/null
make >/dev/null

TMPDIR=/tmp/pathtrans_test
rm -rf "$TMPDIR"
mkdir -p "$TMPDIR/orig" "$TMPDIR/new"

echo "data" > "$TMPDIR/new/file.txt"
echo "#!/bin/sh" > "$TMPDIR/new/prog.sh"
echo "exit 0" >> "$TMPDIR/new/prog.sh"
chmod +x "$TMPDIR/new/prog.sh"
DB="$TMPDIR/db.txt"
export PATHTRANS_DB="$DB"
../tools/pathtrans_db -a "$TMPDIR/orig" "$TMPDIR/new"
export LD_LIBRARY_PATH=..:$LD_LIBRARY_PATH
export LD_PRELOAD=../libpathtrans.so

set +e
ret=0
./test_translation || ret=1
./test_path_database || ret=1
PATHTRANS_DISABLE=1 ./test_disable_env || ret=1
./test_link_unlink || ret=1
./test_chdir_getcwd || ret=1
./test_execve || ret=1
set -e

rm -rf "$TMPDIR"
exit $ret
