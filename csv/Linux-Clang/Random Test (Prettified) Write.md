
----
### Random Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 16985 | 0.350647 | 4688.11ms | 837491 | 40 | 1.0875e+06 | 47023.4 | 0.0486223 | 0.145662 | 1(Win) | true |
| Glaze | 3578.94 | 0.297706 | 5701.01ms | 837491 | 40 | 1.76558e+07 | 223165 | 0.343513 | 0.691639 | 2(Loss) | true |
