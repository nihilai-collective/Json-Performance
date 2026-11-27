
----
### String Test Write Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1615.73 | 0.0941504 | 971.57ms | 4215 | 2560 | 14045.7 | 2487.88 | 0.151725 | 3.21816 | 13.5466 | 2.77438 | 0.00151375 | 8.30368e-05 | 2.53929e-05 | 1(Win) | true |
| Glaze | 879.796 | 0.0552716 | 1190.43ms | 4215 | 4890 | 31184.9 | 4568.94 | 0.572189 | 5.85162 | 29.5718 | 5.81329 | 0.00295653 | 7.25329e-05 | 2.22693e-05 | 2(Loss) | true |
