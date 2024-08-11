import shutil
import subprocess
import webbrowser
import os
import argparse

parser = argparse.ArgumentParser()
parser.add_argument(
    '--exhaustive',
    action='store_true',
    help='Enable exhaustive check level in cppcheck'
)
args = parser.parse_args()
SOURCE_DIR_PATH: str = 'very_simple_kernel/src'
CPPCHECK_ARTIFACTS_DIR_PATH: str = 'cppcheck-artifacts'
CPPCHECK_XML_REPORT_FILE_PATH: str = os.path.join(
    CPPCHECK_ARTIFACTS_DIR_PATH,
    'cppcheck-report.xml'
)
CPPCHECK_HTML_REPORT_DIR_PATH: str = os.path.join(
    CPPCHECK_ARTIFACTS_DIR_PATH,
    'cppcheck-htmlreport'
)
CPPCHECK_HTML_REPORT_INDEX_FILE_PATH: str = os.path.join(
    CPPCHECK_HTML_REPORT_DIR_PATH,
    'index.html'
)
if os.path.exists(CPPCHECK_ARTIFACTS_DIR_PATH):
    shutil.rmtree(CPPCHECK_ARTIFACTS_DIR_PATH)
os.mkdir(CPPCHECK_ARTIFACTS_DIR_PATH)
CPPCHECK_COMMAND: list[str] = [
    'cppcheck',
    SOURCE_DIR_PATH,
    '--enable=all',
    '--language=c',
    '--std=c11',
    f'--output-file={CPPCHECK_XML_REPORT_FILE_PATH}',
    '--suppress=checkersReport',
    '--suppress=unmatchedSuppression',
    '--suppress=normalCheckLevelMaxBranches',
    '--suppress=checkLevelNormal',
    '--suppress=missingIncludeSystem',
    '--xml-version=2',
    '--inline-suppr',
    # Defines {
    # '-Ddefine',
    # } Defines
    # Includes {
    # '-Ipath/',
    # } Includes
    # Excludes {
    # '-ipath/',
    # } Excludes
    # Ignore 3rd party {
    # '--suppress=*:path/*.h',
    # } Ignore 3rd party
]
if args.exhaustive:
    CPPCHECK_COMMAND.append('--check-level=exhaustive')
subprocess.run(CPPCHECK_COMMAND)
CPPCHECK_HTMLREPORT_COMMAND: list[str] = [
    'python',
    '/usr/share/cppcheck/htmlreport/cppcheck-htmlreport',
    '--source-dir=.',
    '--title="Very Simple Kernel"',
    f'--file={CPPCHECK_XML_REPORT_FILE_PATH}',
    f'--report-dir={CPPCHECK_HTML_REPORT_DIR_PATH}'
]
subprocess.run(CPPCHECK_HTMLREPORT_COMMAND)
webbrowser.open(f"file://{os.path.abspath(CPPCHECK_HTML_REPORT_INDEX_FILE_PATH)}")
