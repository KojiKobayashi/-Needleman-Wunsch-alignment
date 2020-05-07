# Example

```c++
{
    auto ret = NeedlemanWunschAlignment::Align("GATTACA", "GCATGCU");
    auto score = ret.GetScore(); // => 0
    auto count = ret.GetCandidateCount(); // => 3
    auto alignedStrings = ret.GetStrings(0); // =>{"G_ATTACA", "GCA_TGCU");
}
{
    // set separator ' '.
    auto ret = NeedlemanWunschAlignment::Align("GATTACA", "GCATGCU", ' ');
    auto alignedStrings = ret.GetStrings(0); // =>{"G ATTACA", "GCA TGCU");
}
```