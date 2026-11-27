
----
### Apache Builds Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2971.69 | 0.113942 | 836.686ms | 3370 | 1280 | 1943.71 | 1081.5 | 0.00101132 | 1.79828 | 7.42967 | 1.23264 | 0.00063265 | 8.97162e-05 | 4.42786e-05 | 1(Win) | true |
| simdjson (ondemand) | 2372.96 | 0.0707018 | 863.013ms | 3370 | 320 | 293.421 | 1354.38 | 0.0380565 | 2.23675 | 8.4003 | 1.35312 | 0.0015523 | 4.45104e-05 | 9.273e-06 | 2(Loss) | true |
