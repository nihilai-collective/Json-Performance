
----
### Canada Test (Minified) Write Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1904.71 | 0.0609945 | 6639.34ms | 2090326 | 320 | 1.30408e+08 | 1.04661e+06 | 0.089163 | 2.65656 | 7.91866 | 0.405668 | 0.000244811 | 0.0507323 | 3.92388e-05 | 1(Win) | true |
| Glaze | 961.68 | 0.111679 | 6469.87ms | 2090234 | 160 | 8.5742e+08 | 2.07283e+06 | 0.0542625 | 5.24974 | 9.34212 | 0.534077 | 0.000241863 | 0.0694212 | 0.000764242 | 2(Loss) | true |
