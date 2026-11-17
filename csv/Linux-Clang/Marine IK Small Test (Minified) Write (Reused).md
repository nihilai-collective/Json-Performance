
----
### Marine IK Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1511.52 | 0.117135 | 1034.11ms | 4604 | 2560 | 29638.3 | 2904.83 | 0.083157 | 3.38295 | 9.22415 | 0.631625 | 0.000519504 | 6.95727e-05 | 2.42656e-05 | 1(Win) | true |
| Glaze | 854.675 | 0.0574044 | 1255.76ms | 4604 | 4890 | 42527.4 | 5137.29 | 0.126834 | 5.953 | 12.437 | 0.970896 | 0.000990559 | 9.02123e-05 | 3.87766e-05 | 2(Loss) | true |
