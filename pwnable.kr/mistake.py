
def unhash(pw):
    result = ""
    for b in pw:
        result += chr(ord(b) ^ 1)
    return result

print "Enter this command:"

hashed_pw = "0123456789"
print "echo -e \"{0}\\n{1}\" | ./mistake".format(hashed_pw, unhash(hashed_pw))
