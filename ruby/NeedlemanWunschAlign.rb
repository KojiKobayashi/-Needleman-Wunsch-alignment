# https://en.wikipedia.org/wiki/Needleman%E2%80%93Wunsch_algorithm

class NeedlemanWunschAlign
    # Aling 2-strings by Needleman Wunsch algorithm.

    def initialize(a, b, sep='_')
        raise ArgumentError.new("#{a} contains #{sep}") if a.include?(sep)
        raise ArgumentError.new("#{b} contains #{sep}") if b.include?(sep)

        @a = a
        @b = b
        @sep = sep
        @table = NeedlemanWunschAlign.create_table(@a, @b)
    end

    def align
        # @return [Array] best alignments and best score.
        return each(&Proc.new{|i| return i}).first
    end

    include Enumerable
    def each(&block)
        iterate(@a.length, @b.length, "", "", &block)
    end

    private

        def iterate(r, c, aling_a, aling_b, &block)
            if r == 0 and c == 0
                yield [aling_a.reverse, aling_b.reverse, @table[@a.length][@b.length]]
                return
            end

            s = @a[r-1] == @b[c-1] ? 1 : -1

            if r > 0 and c > 0 and @table[r][c] == @table[r-1][c-1] + s
                iterate(r-1, c-1, aling_a+@a[r-1], aling_b+@b[c-1], &block)
            end

            if r > 0 and @table[r][c] == @table[r-1][c] - 1
                iterate(r-1, c, aling_a+@a[r-1], aling_b+@sep, &block)
            end

            if c > 0 and @table[r][c] == @table[r][c-1] - 1
                iterate(r,c-1, aling_a+@sep, aling_b+@b[c-1], &block)
            end

            return
        end

        def self.create_table(a, b)
            table = Array.new(a.length + 1).map{ Array.new(b.length + 1, 0) }

            # set upper row and left coloum
            table.each_with_index do |row, i|
                row[0] = -i
            end
            table[0].length.times do |i|
                table[0][i] = -i
            end

            a.length.times do |j|
                b.length.times do |i|

                    score_to_bottom = table[j][i + 1] - 1
                    score_to_right = table[j + 1][i] - 1
                    score_to_diagonal = table[j][i] - 1
                    score_to_diagonal += 2 if a[j] == b[i]

                    score = [score_to_bottom, score_to_right, score_to_diagonal].max
                    table[j + 1][i + 1] = score
                end
            end

            return table
        end
end

if $0 == __FILE__
    p("start")
    p NeedlemanWunschAlign.new("GATTACA","GCATGCU").align
    p NeedlemanWunschAlign.new("GATTACA","GCATGCU").map {|i| p i}
    p NeedlemanWunschAlign.new("ab", "abc", '@').align
end