
----
### Random Test (Minified) Write Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 13915.1 | 0.110692 | 3931.95ms | 461466 | 640 | 784360 | 31626.6 | 0.0137573 | 0.362945 | 1.61357 | 0.233608 | 0.000599056 | 0.00860184 | 6.7719e-06 | 1(Win) | true |
| Glaze | 3600.25 | 0.141819 | 6690.93ms | 461466 | 1280 | 3.84675e+07 | 122238 | 0.410594 | 1.39322 | 5.36925 | 0.79156 | 0.00990043 | 0.0417635 | 3.40119e-05 | 2(Loss) | true |
