
----
### Random Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2334.51 | 0.0377552 | 8465.86ms | 676745 | 160 | 1.74314e+06 | 276458 | 0.049847 | 2.16468 | 10.1038 | 1.84459 | 0.00467508 | 0.016229 | 6.36318e-06 | 1(Win) | true |
| simdjson (ondemand) | 1813.34 | 0.104889 | 5206.99ms | 676745 | 160 | 2.22986e+07 | 355915 | 0.1179 | 2.79919 | 11.4927 | 1.90578 | 0.00887907 | 0.0238034 | 2.89252e-05 | 2(Loss) | true |
