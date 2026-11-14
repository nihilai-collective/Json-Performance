
----
### Marine IK Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 2411.41 | 0.0710078 | 880.598ms | 18245 | 80 | 2100.14 | 7215.61 | 0.043501 | 1(Win) | true |
| Jsonifier | 2264.96 | 0.134513 | 912.063ms | 18245 | 4890 | 522163 | 7682.16 | 0.288276 | 2(Loss) | true |
| simdjson (ondemand) | 1363.1 | 0.0968248 | 1419.28ms | 18245 | 4890 | 746992 | 12764.9 | 0.00646681 | 3(Loss) | true |
| Glaze | 1359.58 | 0.0761669 | 1461.23ms | 18245 | 40 | 3800.76 | 12797.9 | 0.0171933 | 4(Loss) | true |
