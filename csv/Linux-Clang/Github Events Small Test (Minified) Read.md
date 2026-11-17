
----
### Github Events Small Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2248.32 | 0.057407 | 75.2922ms | 1691 | 320 | 54.2564 | 717.275 | 0.369946 | 1.05986 | 1(Win) | true |
| Jsonifier (two-stage) | 1966.1 | 0.205398 | 84.4651ms | 1691 | 30 | 85.1506 | 820.233 | 0.162292 | 1.21666 | 2(Loss) | true |
| Glaze | 1892.75 | 0.107974 | 90.2616ms | 1691 | 320 | 270.824 | 852.022 | 0.0583512 | 1.26683 | 3(Loss) | true |
| simdjson (ondemand) | 1361.24 | 0.085582 | 124.904ms | 1691 | 160 | 164.475 | 1184.7 | 0.194817 | 1.7747 | 4(Loss) | true |
