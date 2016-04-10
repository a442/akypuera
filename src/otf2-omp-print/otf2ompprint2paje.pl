#!/usr/bin/perl

sub main {
    my($arg);

    $arg = shift(@ARGV);
    if (!defined($arg)){
	print "Provide the traces.otf2 file within a scorep directory.";
	exit(1);
    }

    open(OTF2PRINT,"/home/schnorr/install/stow/bin/otf2-print $arg | ") || die "Failed: $!\n";

    my $resolution = 1000000;
    my $first_timestamp;

    header($arg);

    # thread zero is created in the beginning
    print "6 0.0 zero T 0 zero\n";
    
    while ($line =  <OTF2PRINT> )
    {
        if(($line =~ /^ENTER/) || ($line =~ /^LEAVE/)) {
	    chomp $line;
	    my($region) = $line;
	    $region =~ s/^[^"]*"//;
	    $region =~ s/"[^"]*$//;
	    
	    $line =~ s/:([1234567890])/_\1/g;
	    $line =~ s/://g;
	    $line =~ s/"/#/g;
	    $line =~ s/#.*#//;
	    $line =~ s/ +/:/g;
	    my($event,$thread,$time,$kind) = split(/:/, $line);

	    if (!defined($first_timestamp)){
		$first_timestamp = $time;
	    }
	    $time -= $first_timestamp;
	    $time /= $resolution;
	    if ($thread == "0") {$thread = "zero";}

	    if ($event =~ /^ENTER/) {
		print "12 $time $thread S \"$region\"\n";
	    }elsif ($event =~ /^LEAVE/) {
		print "14 $time $thread S\n";
	    }
	}elsif(($line =~ /^THREAD_TEAM_BEGIN/)){ # || ($line =~ /^THREAD_TEAM_END/)){ # Destroy container is disable for now
	    chomp $line;
	    $line =~ s/ +/:/g;
	    my($event,$thread,$time) = split(/:/, $line);
	    if (!defined($first_timestamp)){
		$first_timestamp = $time;
	    }
	    $time -= $first_timestamp;
	    $time /= $resolution;
	    if (!($thread == "0")) {
		print "6 $time $thread T 0 $thread\n";
	    }
	}
    }
    return;
}

main();

sub header(){
    my $file = @_[0];
print "#This trace was generated with: otf2ompprint2paje.pl $file
#otf2ompprint2paje.pl is available at https://github.com/schnorr/akypuera/
#The script relies on the availability of otf2-print executable (ScoreP)
%EventDef PajeDefineContainerType 0
%       Alias string
%       Type string
%       Name string
%EndEventDef
%EventDef PajeDefineStateType 2
%       Alias string
%       Type string
%       Name string
%EndEventDef
%EventDef PajeCreateContainer 6
%       Time date
%       Alias string
%       Type string
%       Container string
%       Name string
%EndEventDef
%EventDef PajeDestroyContainer 7
%       Time date
%       Type string
%       Name string
%EndEventDef
%EventDef PajePushState 12
%       Time date
%       Container string
%       Type string
%       Value string
%EndEventDef
%EventDef PajePopState 14
%       Time date
%       Container string
%       Type string
%EndEventDef
";

# print type hierarchy

print "0 T 0 T
2 S T S
"
    }
