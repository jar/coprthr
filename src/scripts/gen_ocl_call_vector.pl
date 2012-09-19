#!/usr/bin/perl
#
# usage:
#    perl ./gen_ocl_call_vector.pl [call-vector-sym [call-sym-prefix] ]

if ($#ARGV > -1) {
	$CALL_VECTOR_SYM = $ARGV[0];
} else {
	$CALL_VECTOR_SYM = "__ocl_call_vector";
}

if ($#ARGV > 0) {
	$CALL_SYM_PREFIX = $ARGV[1];
} else {
	$CALL_SYM_PREFIX = "";
}

#$master = '../libocl/oclcall.master';
#open(MASTER, $master);
#@lines = <MASTER>;
#close(MASTER);
@lines = <STDIN>;

#open($out, ">libclrpc_call_vector.c");
$out = *STDOUT;

### 
### generate libclrpc_call_vector.c
###

printf $out "/* libclrpc_call_vector.c\n";
printf $out " * This file was auto-generated by gen_ocl_call_vector.pl\n";
printf $out " */\n\n";

printf $out "/* $CALL_VECTOR_SYM $CALL_SYM_PREFIX */\n\n";

printf $out "#include \"CL/cl.h\"\n\n";
printf $out "#include \"CL/cl_gl.h\"\n\n";

printf $out "\ntypedef void (*cl_pfn_notify_t)(const char*, const void*, size_t, void*);\n";
printf $out "typedef void (*cl_pfn_notify2_t)(cl_program , void* );\n";
printf $out "typedef void (*cl_user_func_t)(void*);\n\n";

#######################################
#
foreach $l (@lines) {
	if (!($l =~ /^[ \t]*#.*/)) {
		@fields = split(' ', $l);
		$name = $fields[0];
		if ($name =~ /^[a-zA-Z].*/) {
			$type = $fields[1];
			$retype = $fields[2];
			$tlist = $fields[3];
			$tlist =~ s/~/ /g;
			@args = split(',',$tlist);
			$atlist = "";
			$alist = "";
			$j=0;
			foreach $a (@args) {
				if ($j > 0) { $atlist .=",$a a$j"; }
				else { $atlist .= "$a a$j"; }
				if ($j > 0) { $alist .=",a$j"; }
				else { $alist .= "a$j"; }
				$j += 1;
			}
			if (!($name =~ /^reserved/)) { 
				printf $out "\t$retype $CALL_SYM_PREFIX$name($tlist);\n\n";
			}
		}
	}
}
printf $out "\n";

#printf $out "\nvoid* $CALL_VECTOR_SYM"."[] = { \\\n";
printf $out "\nstatic void* _cvec[] = { \\\n";
$i=0;
foreach $l (@lines) {
	if (!($l =~ /^[ \t]*#.*/)) {
		@fields = split(' ', $l);
		$name = $fields[0];
		if ($name =~ /^[a-zA-Z].*/) {
			unless ($name =~ /reserved/) {
				$tlist = $fields[3];
				@args = split(',',$tlist);
				if ($tlist =~ /^void$/) { $narg = 0; }
				else { $narg = $#args+1; }
				printf $out "\t$CALL_SYM_PREFIX$name, \\\n";
			}
		}
	$i = $i + 1;
	}
}
printf $out "\t};\n";

printf $out "\nvoid** $CALL_VECTOR_SYM = (void**)_cvec;\n";


#close($out);

