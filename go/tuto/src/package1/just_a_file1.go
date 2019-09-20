/*
there must be a single package name that will be used for every go file inside
a folder, in this example both just_a_file1.go and just_a_file2.go have package
name file1, if they had different names an error like the following would
happen:

file.go:44:2: found packages file1 (just_a_file1.go) and file2 (just_a_file2.go)
in /home/bruno/git/Programming-Studies/go/tuto/src/package1

Although the package name is file1 when imported the directory name must be
used, an example can be found on src/file.go where is written "import package1"
package1 is the name of the folder but the files inside it use the package name
file1, in this case inside "src/file.go" when accessing some resource from one
of the files of this package use: "file1.ReturnString()"
*/
package file1

//Only names that start with capital letter are exported, in this case
//ReturnString is exported and can be accessed by other go files
func ReturnString() string {
	return "a string"
}

//This function is not exported because it does not start with capital letter
func returnString() string {
	return "a string"
}

/*
The function below is commented because it also exists on just_a_file2.go, in
this case when package1 is imported the following error will be raised, this
error will occur even when the function is not called:

# package1
package1/just_a_file2.go:25:22: returnString2 redeclared in this block
        previous declaration at package1/just_a_file1.go:29:22

func returnString2() string {
	return "a string 2"
}
*/
