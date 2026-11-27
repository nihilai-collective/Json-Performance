
----
### Marine IK Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2397.36 | 0.0454745 | 1552.47ms | 18245 | 640 | 6971.65 | 7257.88 | 0.341352 | 2.15368 | 8.8137 | 1.69466 | 0.00246009 | 8.82091e-06 | 5.99479e-07 | 1(Win) | true |
| simdjson (ondemand) | 2189.16 | 0.127183 | 1618.67ms | 18245 | 30 | 3065.59 | 7948.17 | 0.150365 | 2.32298 | 9.58854 | 1.55922 | 0.00285558 | 6.75984e-05 | 5.11556e-05 | 2(Loss) | true |
