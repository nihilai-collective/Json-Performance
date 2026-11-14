
----
### Marine IK Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1244.66 | 0.122927 | 2212.7ms | 18245 | 80 | 23625.2 | 13979.6 | 0.0149347 | 4.14793 | 16.9354 | 3.54059 | 0.00559057 | 4.17923e-05 | 1.50726e-05 | 1(Win) | true |
| simdjson (ondemand) | 966.294 | 0.0440555 | 2608.66ms | 18245 | 1280 | 80552.4 | 18006.7 | 0.00934635 | 5.33465 | 26.4975 | 5.35577 | 0.00650555 | 0.000105423 | 6.47866e-05 | 2(Loss) | true |
