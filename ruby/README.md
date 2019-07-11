## Example

```ruby
aligner = NeedlemanWunschAlign.new("GATTACA","GCATGCU")

# return alignments and score.
alinger.align #=> ["G_ATTACA", "GCA_TGCU", 0]
alinger.map {|result| result} #=> [["G_ATTACA", "GCA_TGCU", 0], ["G_ATTACA", "GCAT_GCU", 0], ["G_ATTACA", "GCATG_CU", 0]]

# set separator
aligner = NeedlemanWunschAlign.new("ab","abc", '@')
alinger.align #=> ["ab@", "abc", 1]
```