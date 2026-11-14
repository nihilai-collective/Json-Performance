
----
### Twitter Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 10727.6 | 0.102615 | 772.12ms | 4300 | 30 | 4.61609 | 382.267 | 0.0348675 | 0.522605 | 1.2686 | 0.212326 | 0.000232558 | 0 | 0 | 1(Win) | true |
| Glaze | 3793.69 | 0.275788 | 842.442ms | 4300 | 2560 | 22751.2 | 1080.95 | 0.14483 | 1.38349 | 3.20907 | 0.507209 | 0.00023601 | 1.53525e-05 | 3.99709e-06 | 2(Loss) | true |
