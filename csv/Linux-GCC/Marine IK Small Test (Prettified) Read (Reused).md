
----
### Marine IK Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2339.81 | 0.0340139 | 1563.18ms | 18245 | 2560 | 16378.7 | 7436.41 | 0.138152 | 2.1983 | 8.60184 | 1.64377 | 0.00240963 | 3.36779e-05 | 1.84126e-05 | 1(Win) | true |
| simdjson (ondemand) | 2313.52 | 0.0299089 | 1569.36ms | 18245 | 2560 | 12953.3 | 7520.92 | 0.111657 | 2.23017 | 9.19867 | 1.56267 | 0.0025061 | 3.07447e-05 | 1.43661e-05 | 2(Loss) | true |
