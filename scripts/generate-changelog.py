import git
import argparse
import re

parser = argparse.ArgumentParser()
parser.add_argument('previousVersion', type=str)
parser.add_argument('newVersion', type=str)
previousVersion = parser.parse_args().previousVersion
newVersion = parser.parse_args().newVersion
repo = git.Repo(".")
commits = list(
    repo.iter_commits(
        f'{previousVersion}..release/{newVersion}', first_parent=True
    )
)
pullRequestCommits = [
    commit
    for commit in commits if "pull request" in commit.message.lower()  # type: ignore
]
pullRequestPattern = re.compile(r"pull request #\d+: ", re.IGNORECASE)
with open('../build/artifacts/changelog.txt', 'w') as file:
    file.write(f"CHANGELOG {previousVersion}..{newVersion}:\n")
    for commit in pullRequestCommits:
        summary = pullRequestPattern.sub('', commit.summary).strip()  # type: ignore
        file.write(f"* {summary} ({commit.authored_datetime})\n")
