
----
### Canada Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1909.47 | 0.277389 | 6600.33ms | 2090234 | 320 | 2.68345e+09 | 1.04396e+06 | 0.270519 | 2.63182 | 7.8911 | 0.405653 | 0.000234343 | 0.0511386 | 4.25012e-05 | 1(Win) | true |
| Glaze | 998.514 | 0.0657672 | 6222.87ms | 2090234 | 40 | 6.8954e+07 | 1.99637e+06 | 0.0444763 | 5.05777 | 9.33809 | 0.533136 | 0.000234101 | 0.0432797 | 0.00023721 | 2(Loss) | true |
