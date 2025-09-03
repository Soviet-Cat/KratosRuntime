import os
import re
import datetime

extensions = ['.py', '.txt', '.c', '.cpp', '.h', '.hpp', '.md']

def updateCopyright(year=None):
    pattern = re.compile(r"(?i)^(.*Copyright\s*\(c\)\s*)(\d{4})(.*Soviet-Cat.*)$", re.MULTILINE)

    if not year:
        year = datetime.datetime.today().year

    for dir, _, files in os.walk(os.getcwd()):
        for file in files:
            if not any(file.endswith(ext) for ext in extensions):
                continue

            path = os.path.join(dir, file)
            try:
                with open(path, "r", encoding="utf-8") as f:
                    content = f.read()
                print(f'Successfully read "{file}".')
            except (UnicodeDecodeError, PermissionError):
                print(f'Failed to read "{file}".')
                continue
        
            match = pattern.search(content)
            if match:
                print(f'Successfully found regex pattern in "{file}".')
                newContent = pattern.sub(match.group(1) + str(year) + match.group(3), content)

                try:
                    with open(path, "w", encoding="utf-8") as f:
                        f.write(newContent)
                    print(f'Successfully wrote "{file}".')
                except (UnicodeEncodeError, PermissionError):
                    print(f'Failed to write "{file}".')
                    continue
                
if __name__ == "__main__":
    year = input(f"Enter new copyright year (defaults to {datetime.datetime.today().year}): ")
    updateCopyright(year)