
----
### Github Events Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 12299.1 | 0.357022 | 754.362ms | 2866 | 4890 | 3078.25 | 222.23 | 0.0893135 | 0.487539 | 1.32275 | 0.220168 | 0.000349703 | 2.38321e-05 | 1.92654e-06 | 1(Win) | true |
| Glaze | 3981.04 | 0.222625 | 803.521ms | 2866 | 4890 | 11423.9 | 686.561 | 0.155399 | 1.32705 | 3.57397 | 0.584439 | 0.000354912 | 2.85414e-05 | 3.71038e-06 | 2(Loss) | true |
