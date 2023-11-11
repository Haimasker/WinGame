$ASTYLE_BRACE_OPTIONS =
	"--style=stroustrup",
	"--attach-namespaces",
	"--attach-classes",
	"--attach-inlines",
	"--attach-closing-while",
	"--break-closing-braces",
	"--break-one-line-headers",
	"--remove-braces"

$ASTYLE_INDENT_OPTIONS =
	"--indent=force-tab=4",
	"--indent-switches",
	"--indent-namespaces",
	"--indent-preproc-block",
	"--indent-preproc-cond",
	"--indent-col1-comments",
	"--min-conditional-indent=0"

$ASTYLE_PADDING_OPTIONS =
	"--break-blocks",
	"--pad-oper",
	"--pad-header",
	"--unpad-brackets",
	"--squeeze-lines=2",
	"--squeeze-ws"

$ASTYLE_FORMAT_OPTIONS =
	"--align-pointer=type",
	"--align-reference=type",
	"--attach-return-type",
	"--attach-return-type-decl",
	"--close-templates",
	"--remove-comment-prefix",
	"--break-after-logical",
	"--max-code-length=80"

$ASTYLE_GENERAL_OPTIONS =
	"--suffix=none",
	"--quiet"

Get-ChildItem -Recurse -Include *.cpp,*.h | ForEach-Object {
	& .\astyle.exe `
	$ASTYLE_BRACE_OPTIONS `
	$ASTYLE_INDENT_OPTIONS `
	$ASTYLE_PADDING_OPTIONS `
	$ASTYLE_FORMAT_OPTIONS `
	$ASTYLE_GENERAL_OPTIONS `
	$_.FullName
}