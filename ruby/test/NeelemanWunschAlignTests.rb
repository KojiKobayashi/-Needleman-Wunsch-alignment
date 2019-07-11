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
end