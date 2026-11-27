
----
### Canada Test (Minified) Read Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 884.147 | 0.075324 | 7544.02ms | 2251027 | 160 | 5.35179e+08 | 2.42804e+06 | 0.0434659 | 5.70886 | 29.7611 | 5.98378 | 0.00730876 | 0.0644085 | 3.65222e-05 | 1(Win) | true |
| Glaze STATISTICAL TIE | 857.823 | 0.0898907 | 7782.76ms | 2251027 | 80 | 4.04842e+08 | 2.50255e+06 | 0.0931592 | 5.87097 | 31.7381 | 5.89909 | 0.0101789 | 0.0628076 | 0.000187631 | 2(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 857.143 | 0.119438 | 7773.26ms | 2251027 | 30 | 2.68449e+08 | 2.50454e+06 | 0.0324692 | 5.88919 | 32.2565 | 6.40511 | 0.0112501 | 0.102465 | 0.000100502 | 2(Tie) | true |
| simdjson (ondemand) | 803.007 | 0.0752757 | 8311.55ms | 2251027 | 80 | 3.23983e+08 | 2.67338e+06 | 0.0284173 | 6.28424 | 31.2861 | 5.42041 | 0.0145509 | 0.107727 | 8.48002e-05 | 4(Loss) | true |
