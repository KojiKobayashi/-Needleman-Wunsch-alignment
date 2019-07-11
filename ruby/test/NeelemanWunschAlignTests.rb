require 'test/unit'
require "../NeedlemanWunschAlign"


class NeedlemanWunschAlignTest < Test::Unit::TestCase
    def test_normal
        assert_equal NeedlemanWunschAlign.new("GATTACA","GCATGCU").align[2], 0
        assert_equal NeedlemanWunschAlign.new("abcde","abcde").align, ["abcde", "abcde", 5]
    end

    def test_multiple_results
        arr = NeedlemanWunschAlign.new("GATTACA","GCATGCU").map{|i| i}
        assert_equal arr[0], ["G_ATTACA", "GCA_TGCU", 0]
        assert_equal arr[1], ["G_ATTACA", "GCAT_GCU", 0]
        assert_equal arr[2], ["G_ATTACA", "GCATG_CU", 0]
    end

    def test_separator
        assert_equal NeedlemanWunschAlign.new("abcd","abcde").align[0..1], ["abcd_", "abcde"]
        assert_equal NeedlemanWunschAlign.new("abcd","abcde", '@').align[0..1], ["abcd@", "abcde"]
        assert_equal NeedlemanWunschAlign.new("abcde","bcde", '@').align[0..1], ["abcde", "@bcde"]

        assert_raise{p NeedlemanWunschAlign.new("a_b","a").align}
        assert_raise{p NeedlemanWunschAlign.new("a","_b").align}
        assert_raise{p NeedlemanWunschAlign.new("a@b","a", '@').align}
        assert_raise{p NeedlemanWunschAlign.new("a","@b", '@').align}
    end
end