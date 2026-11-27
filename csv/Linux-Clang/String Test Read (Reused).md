
----
### String Test Read (Reused) Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1826.56 | 0.0597563 | 994.701ms | 4215 | 4890 | 8456.78 | 2200.72 | 0.20965 | 2.86441 | 13.0396 | 2.03749 | 0.000620629 | 6.68564e-05 | 1.89216e-05 | 1(Win) | true |
| simdjson (ondemand) STATISTICAL TIE | 1220.73 | 0.097864 | 1100.84ms | 4215 | 2560 | 26585.5 | 3292.91 | 0.149966 | 4.19183 | 19.6527 | 3.27806 | 0.00234662 | 7.08037e-05 | 1.8535e-05 | 2(Tie) | true |
| Glaze STATISTICAL TIE | 1219.85 | 0.240994 | 1106.08ms | 4215 | 320 | 20181.1 | 3295.27 | 0.177938 | 4.3058 | 20.013 | 3.89585 | 0.00224718 | 5.48636e-05 | 1.18624e-05 | 2(Tie) | true |
