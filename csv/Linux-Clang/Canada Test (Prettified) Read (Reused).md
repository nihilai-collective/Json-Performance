
----
### Canada Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2168.9 | 0.159041 | 8633.44ms | 5373214 | 40 | 5.64765e+08 | 2.36262e+06 | 0.425969 | 2.30498 | 12.2774 | 2.2067 | 0.00424294 | 0.0522987 | 0.000569571 | 1(Win) | true |
| simdjson (ondemand) | 2124.16 | 0.162701 | 8738.46ms | 5373214 | 160 | 2.46486e+09 | 2.41238e+06 | 0.0244141 | 2.37169 | 11.7271 | 1.80434 | 0.00491651 | 0.0509396 | 0.000746404 | 2(Loss) | true |
| Jsonifier | 2036.59 | 0.180336 | 9044.78ms | 5373214 | 80 | 1.64707e+09 | 2.51611e+06 | 0.00628291 | 2.47873 | 13.2081 | 2.75286 | 0.00293708 | 0.0279726 | 0.00108571 | 3(Loss) | true |
| Glaze | 1845.15 | 0.138932 | 9916.92ms | 5373214 | 40 | 5.95477e+08 | 2.77716e+06 | 0.166602 | 2.73571 | 13.9468 | 2.50129 | 0.00447688 | 0.029671 | 0.00654851 | 4(Loss) | true |
