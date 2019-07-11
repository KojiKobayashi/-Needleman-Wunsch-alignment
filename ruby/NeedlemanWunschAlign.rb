# https://en.wikipedia.org/wiki/Needleman%E2%80%93Wunsch_algorithm

def main(a, b)

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

    # derive only 1 candidate
    r = a.length
    c = b.length
    aling_a = ""
    aling_b = ""

    while r > 0 or c > 0 do
        s = a[r-1] == b[c-1] ? 1 : -1

        if r > 0 and c > 0 and table[r][c] == table[r-1][c-1] + s
            aling_a+=(a[r-1])
            aling_b+=(b[c-1])
            r -= 1
            c -= 1
            next
        end

        if r > 0 and table[r][c] == table[r-1][c] - 1
            aling_a+=(a[r-1])
            aling_b+=("_")
            r -= 1
            next
        end

        aling_b+=(b[c-1])
        aling_a+=("_")
        c -= 1
    end

    return [aling_a.reverse, aling_b.reverse, table[a.length][b.length]]
end

if $0 == __FILE__
    p("start")
    p main("GATTACA","GCATGCU")
    p main("abdce", "abdce")
end