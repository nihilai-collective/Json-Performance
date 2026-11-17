
----
### Canada Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1966.79 | 0.071763 | 6445.78ms | 2090234 | 160 | 8.46436e+07 | 1.01353e+06 | 0.0379931 | 2.56259 | 7.73281 | 0.405653 | 0.000246109 | 0.0504478 | 0.000503356 | 1(Win) | true |
| Glaze | 996.161 | 0.0783827 | 6229.9ms | 2090234 | 160 | 3.93632e+08 | 2.00108e+06 | 0.028675 | 5.07415 | 9.33809 | 0.533136 | 0.000234095 | 0.0431842 | 0.000197547 | 2(Loss) | true |
