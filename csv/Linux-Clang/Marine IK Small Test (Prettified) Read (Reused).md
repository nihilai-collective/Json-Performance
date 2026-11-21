
----
### Marine IK Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3563.61 | 0.0508843 | 570.731ms | 18245 | 40 | 246.907 | 4882.62 | 0.196832 | 0.69093 | 1(Win) | true |
| Jsonifier | 2758.22 | 0.255676 | 714.938ms | 18245 | 1280 | 332980 | 6308.34 | 0.273737 | 0.893946 | 2(Loss) | true |
| simdjson (ondemand) | 2140.05 | 0.221954 | 890.251ms | 18245 | 1280 | 416846 | 8130.55 | 0.123762 | 1.15303 | 3(Loss) | true |
| Glaze | 2052.85 | 0.238376 | 925.89ms | 18245 | 1280 | 522530 | 8475.93 | 0.0251049 | 1.20235 | 4(Loss) | true |
