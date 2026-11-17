
----
### Marine IK Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2231.15 | 0.13575 | 977.033ms | 18245 | 30 | 3362.25 | 7798.57 | 0.57346 | 1(Win) | true |
| Jsonifier (two-stage) | 2149.47 | 0.328502 | 1055ms | 18245 | 640 | 452563 | 8094.91 | 0.494389 | 2(Loss) | true |
| simdjson (ondemand) | 1275 | 0.0810371 | 1637.12ms | 18245 | 40 | 4892.12 | 13646.9 | 0.306878 | 3(Loss) | true |
| Glaze | 1164.8 | 0.651454 | 1669.76ms | 18245 | 640 | 6.06081e+06 | 14938 | 1.49183 | 4(Loss) | true |
