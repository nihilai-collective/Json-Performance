
----
### Random Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 15935.1 | 0.0328267 | 5815.05ms | 837491 | 2560 | 693019 | 50121.6 | 0.000749744 | 0.317569 | 1.35544 | 0.257602 | 0.00046231 | 0.0163356 | 1.73295e-05 | 1(Win) | true |
| Glaze | 4493.39 | 0.0862794 | 9540.03ms | 837491 | 1280 | 3.01048e+07 | 177748 | 0.114019 | 1.12437 | 4.56028 | 0.768648 | 0.00620543 | 0.0163803 | 2.76682e-05 | 2(Loss) | true |
