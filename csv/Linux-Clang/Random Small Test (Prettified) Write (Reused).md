
----
### Random Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 17125 | 0.14104 | 786.395ms | 9255 | 4890 | 2583.94 | 515.402 | 0.0260171 | 0.319237 | 1.40249 | 0.265478 | 0.000280045 | 1.46276e-05 | 4.90532e-06 | 1(Win) | true |
| Glaze | 4578.43 | 0.103766 | 928.9ms | 9255 | 4890 | 19567.5 | 1927.79 | 0.0690303 | 1.12692 | 4.61632 | 0.778498 | 0.000281239 | 3.14427e-05 | 1.01421e-05 | 2(Loss) | true |
