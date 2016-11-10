
import hist
import sys

def main():
    ab_hist = hist.Hist(0,100000,bucket_int=100)
    aa_hist = hist.Hist(0,100000,bucket_int=100)
    errors = 0
    count = 0
    with open(sys.argv[1], "r") as datafile:
        for line in datafile:
            line_fields = line.strip().split()
            a_to_b = int(line_fields[1])
            a_to_a = int(line_fields[5])
            if a_to_b < 0 or a_to_b > a_to_a:
                errors += 1
            else:
                aa_hist.add_value(a_to_a)
                ab_hist.add_value(a_to_b)
            count += 1

    print "# Total: {0}".format(count)
    print "# Errors: {0} ({1}%)".format(errors, float(errors)/count * 100)
    aa_hist.pprint()
#    ab_hist.pprint()


if __name__ == "__main__":
    main()
