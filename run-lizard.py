import shutil
import subprocess
import webbrowser
import os

SOURCE_DIR_PATH: str = 'very-simple-kernel/src'
LIZARD_ARTIFACTS_DIR_PATH: str = 'lizard-artifacts'
LIZARD_HTML_REPORT_FILE_PATH: str = os.path.join(
    LIZARD_ARTIFACTS_DIR_PATH,
    'lizard-report.html'
)
if os.path.exists(LIZARD_ARTIFACTS_DIR_PATH):
    shutil.rmtree(LIZARD_ARTIFACTS_DIR_PATH)
os.mkdir(LIZARD_ARTIFACTS_DIR_PATH)
LIZARD_COMMAND: list[str] = [
    'lizard',
    SOURCE_DIR_PATH,
    '-Tcyclomatic_complexity=10',
    '-Tparameter_count=5',
    '-Tnloc=50',
    '-m',
    '-lc',
    f'-o{LIZARD_HTML_REPORT_FILE_PATH}'
]
subprocess.run(LIZARD_COMMAND)
webbrowser.open(f"file://{os.path.abspath(LIZARD_HTML_REPORT_FILE_PATH)}")
