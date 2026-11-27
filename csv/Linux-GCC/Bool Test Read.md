
----
### Bool Test Read Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 2140.51 | 0.0608121 | 743.925ms | 905 | 640 | 38.4788 | 403.209 | 0.015503 | 2.6469 | 11.589 | 2.71492 | 0.0040953 | 0.000138122 | 3.45304e-06 | 1(Win) | true |
| simdjson (stage-1) | 1073.84 | 0.111923 | 789.45ms | 905 | 640 | 517.883 | 803.727 | 0.0149716 | 5.03651 | 28.1934 | 6.00552 | 0.00110843 | 5.87017e-05 | 3.45304e-06 | 2(Loss) | true |
