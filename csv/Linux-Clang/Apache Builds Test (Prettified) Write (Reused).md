
----
### Apache Builds Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 17309.8 | 0.109577 | 1491.33ms | 136037 | 640 | 43166.8 | 7494.87 | 0.0196632 | 0.298821 | 1.2901 | 0.214251 | 0.000209272 | 5.50172e-06 | 3.8133e-06 | 1(Win) | true |
| Glaze | 5860.09 | 0.110942 | 2937.68ms | 136076 | 320 | 193149 | 22145.1 | 0.00917331 | 0.864331 | 4.06236 | 0.682685 | 0.00161045 | 3.46773e-06 | 1.79128e-06 | 2(Loss) | true |
