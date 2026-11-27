
----
### Canada Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2144.84 | 0.0573268 | 1349.26ms | 11579 | 2560 | 22300.2 | 5148.45 | 0.142694 | 2.38312 | 11.0491 | 2.07937 | 0.00290305 | 1.85883e-05 | 3.20489e-06 | 1(Win) | true |
| Jsonifier | 2124.32 | 0.0815929 | 1351.93ms | 11579 | 1280 | 23025.9 | 5198.18 | 0.058625 | 2.39902 | 11.3792 | 2.38527 | 0.00357544 | 2.72584e-05 | 7.2869e-06 | 2(Loss) | true |
| simdjson (ondemand) | 2094.64 | 0.0583265 | 1361.89ms | 11579 | 4890 | 46234.2 | 5271.83 | 0.165918 | 2.43488 | 11.9424 | 1.91588 | 0.000497728 | 2.82226e-05 | 9.04253e-06 | 3(Loss) | true |
| Glaze | 1824.63 | 0.081451 | 1437.39ms | 11579 | 2560 | 62204.7 | 6051.95 | 0.0408792 | 2.79085 | 13.3379 | 2.51611 | 0.00415903 | 4.08539e-05 | 1.66317e-05 | 4(Loss) | true |
