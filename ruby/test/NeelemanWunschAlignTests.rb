require 'test/unit'
require "../NeedlemanWunschAlign"


class NeedlemanWunschAlignTest < Test::Unit::TestCase
    def test_normal
        assert_equal NeedlemanWunschAlign.align("GATTACA","GCATGCU")[2], 0
        assert_equal NeedlemanWunschAlign.align("abcde","abcde"), ["abcde", "abcde", 5]
    end
end