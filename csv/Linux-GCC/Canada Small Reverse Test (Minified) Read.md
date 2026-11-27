
----
### Canada Small Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Canada%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 715.343 | 0.043226 | 1350.71ms | 4630 | 2560 | 18224.8 | 6172.58 | 0.0399415 | 7.20727 | 35.8788 | 6.75594 | 0.00445675 | 8.3862e-05 | 5.09584e-05 | 1(Win) | true |
| Jsonifier (generic) | 678.2 | 0.102145 | 1393.58ms | 4630 | 30 | 1326.79 | 6510.63 | 0.0455457 | 7.64138 | 34.4138 | 7.03132 | 0.00897048 | 5.75954e-05 | 2.15983e-05 | 2(Loss) | true |
