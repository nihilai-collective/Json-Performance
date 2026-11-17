
----
### Marine IK Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2384.94 | 0.182563 | 9868.85ms | 7351818 | 30 | 8.64131e+08 | 2.9398e+06 | 0.15545 | 2.12277 | 8.91025 | 1.71096 | 0.0100143 | 0.0536115 | 0.00575517 | 1(Win) | true |
| simdjson (ondemand) | 2269.33 | 0.0735162 | 10302.2ms | 7351818 | 80 | 4.12714e+08 | 3.08956e+06 | 0.0537118 | 2.23115 | 9.45533 | 1.45242 | 0.0107245 | 0.0536475 | 0.000923622 | 2(Loss) | true |
