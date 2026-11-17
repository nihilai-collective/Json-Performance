
----
### Marine IK Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2128.85 | 0.184886 | 1012.04ms | 18245 | 30 | 6850.57 | 8173.33 | 0.0814996 | 1.15842 | 1(Win) | true |
| Jsonifier | 1802.17 | 0.283153 | 1121.54ms | 18245 | 1280 | 956645 | 9654.92 | 0.0961989 | 1.36951 | 2(Loss) | true |
| simdjson (ondemand) | 734.953 | 0.177617 | 2598.85ms | 18245 | 1280 | 2.26333e+06 | 23674.7 | 0.296771 | 3.36481 | 3(Loss) | true |
| Glaze | 601.297 | 0.167407 | 3065.34ms | 18245 | 1280 | 3.00376e+06 | 28937.1 | 0.138848 | 4.11387 | 4(Loss) | true |
