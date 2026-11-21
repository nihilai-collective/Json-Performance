
----
### Twitter Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2357.67 | 0.241318 | 200.842ms | 3808 | 30 | 414.506 | 1540.33 | 0.979279 | 1(Win) | true |
| Glaze | 2086.08 | 0.158421 | 213.625ms | 3808 | 160 | 1216.96 | 1740.87 | 0.582466 | 2(Loss) | true |
| Jsonifier (two-stage) | 1777.22 | 0.646406 | 204.158ms | 3808 | 640 | 111662 | 2043.42 | 2.06608 | 3(Loss) | true |
| simdjson (ondemand) | 843.742 | 1.56708 | 426.543ms | 3808 | 40 | 181976 | 4304.15 | 2.88397 | 4(Loss) | true |
