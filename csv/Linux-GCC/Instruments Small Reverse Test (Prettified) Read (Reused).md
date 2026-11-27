
----
### Instruments Small Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 975.844 | 0.101171 | 1507.16ms | 7932 | 40 | 2460.22 | 7751.8 | 0.129694 | 5.30765 | 22.9647 | 4.49054 | 0.0050996 | 4.72769e-05 | 2.20625e-05 | 1(Win) | true |
| simdjson (ondemand) | 410.246 | 0.0497526 | 2569.65ms | 7932 | 640 | 53862.8 | 18439.1 | 0.206285 | 12.5061 | 55.1161 | 11.1004 | 0.0375201 | 3.84124e-05 | 1.73348e-05 | 2(Loss) | true |
