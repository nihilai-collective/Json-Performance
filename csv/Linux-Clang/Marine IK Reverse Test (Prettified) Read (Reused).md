
----
### Marine IK Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1416.08 | 0.245476 | 7818.35ms | 7351818 | 30 | 4.43154e+09 | 4.95117e+06 | 0.118635 | 3.59021 | 16.3057 | 3.22128 | 0.0100694 | 0.181159 | 0.00347038 | 1(Win) | true |
| simdjson (ondemand) | 921.077 | 0.281808 | 5550.21ms | 7351818 | 40 | 1.84062e+10 | 7.612e+06 | 2.05119 | 5.55472 | 26.4489 | 5.15787 | 0.0117924 | 0.430494 | 0.00561963 | 2(Loss) | true |
