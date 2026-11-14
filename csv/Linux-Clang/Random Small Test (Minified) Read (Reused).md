
----
### Random Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1535.87 | 0.0727786 | 1067.95ms | 4926 | 1280 | 6343.03 | 3058.72 | 0.200101 | 3.39804 | 14.4533 | 2.75822 | 0.00411703 | 4.29799e-05 | 1.04674e-05 | 1(Win) | true |
| simdjson (ondemand) | 1234.63 | 0.0498565 | 1138.17ms | 4926 | 1280 | 4606.47 | 3805.03 | 0.000615966 | 4.21742 | 16.9503 | 2.84024 | 0.00517535 | 3.74289e-05 | 3.96493e-06 | 2(Loss) | true |
