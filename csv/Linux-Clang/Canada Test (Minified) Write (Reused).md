
----
### Canada Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1908.02 | 0.0794247 | 6635.38ms | 2090326 | 80 | 5.50886e+07 | 1.04479e+06 | 0.135522 | 2.65465 | 7.91827 | 0.405635 | 0.0002408 | 0.0505487 | 2.45536e-05 | 1(Win) | true |
| Glaze | 994.655 | 0.117167 | 6236.72ms | 2090234 | 160 | 8.82219e+08 | 2.00411e+06 | 0.523626 | 5.07905 | 9.33809 | 0.533136 | 0.000234681 | 0.0433358 | 0.000133011 | 2(Loss) | true |
