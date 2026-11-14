
----
### Canada Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1698.16 | 0.202572 | 1410.22ms | 11579 | 40 | 6940.73 | 6502.7 | 0.0988355 | 3.05323 | 15.138 | 2.72675 | 0.00185897 | 3.02271e-05 | 4.31816e-06 | 1(Win) | true |
| Jsonifier (generic) | 1530.38 | 0.0515207 | 1449.89ms | 11579 | 160 | 2211.19 | 7215.57 | 0.128031 | 3.38587 | 14.815 | 2.88091 | 0.00339516 | 3.72441e-05 | 2.21306e-05 | 2(Loss) | true |
