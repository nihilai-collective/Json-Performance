
----
### Github Events Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1802.06 | 0.118029 | 841.789ms | 2158 | 2560 | 4651.39 | 1142.04 | 0.103437 | 2.96198 | 10.6659 | 1.943 | 0.000471176 | 0.000118382 | 4.2719e-05 | 1(Win) | true |
| simdjson (ondemand) | 1773.36 | 0.18198 | 843.474ms | 2158 | 40 | 178.41 | 1160.53 | 0.0954116 | 3.00916 | 10.8948 | 1.9481 | 0.000463392 | 0.000173772 | 0.000104263 | 2(Loss) | true |
