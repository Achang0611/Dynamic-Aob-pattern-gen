from functools import reduce
from sys import argv
import re


def different(str1: str, str2: str):
    ans = ""
    for i, j in zip(str1, str2):
        if i != j:
            ans += "?"
            continue
        ans += i

    return ans


def errorLog(msg: str):
    with open("error.log", "w") as error:
        error.write(msg)


def main():
    if len(argv) <= 1:
        errorLog("把字節數組檔案拖曳到程式上")
        return

    with open(argv[1]) as f:
        with open("pattern.txt", "w") as aob:
            temp = f.readline()
            read = [temp.replace("\n", "").replace(" ", "")]
            preLen = len(read[0])

            aob.write("原始字節數組:\n")
            aob.write("    " + temp)
            for i in f.readlines():
                tmp = i.replace("\n", "").replace(" ", "")
                if preLen != len(tmp):
                    errorLog("字節數組長度都需相同")
                    return

                read.append(tmp)
                aob.write("    " + i)
            aob.write("\n總共" + str(len(read)) + "組\n")

            if len(read) <= 1:
                aob.write("變動: 0\n")
                aob.write("模板:\n")
                aob.write("    " + temp)
                return

            result = " ".join(re.compile('.{2}').findall(reduce(different, read)))

            aob.write("變動: " + str(result.count("?")) + "\n")
            aob.write("模板:\n")
            aob.write("    " + result)


if __name__ == "__main__":
    main()
