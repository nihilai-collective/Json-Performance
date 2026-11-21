
----
### Marine IK Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 2393.12 | 0.047667 | 886.592ms | 18245 | 80 | 960.918 | 7270.76 | 0.0844847 | 1(Win) | true |
| Jsonifier | 2352.6 | 0.119135 | 884.835ms | 18245 | 2560 | 198752 | 7395.97 | 0.0458335 | 2(Loss) | true |
| Glaze | 1382.15 | 0.0535362 | 1507.23ms | 18245 | 80 | 3633.83 | 12589 | 0.0529514 | 3(Loss) | true |
| simdjson (ondemand) | 1366.39 | 0.145594 | 1565.52ms | 18245 | 1280 | 439981 | 12734.1 | 0.0687147 | 4(Loss) | true |
