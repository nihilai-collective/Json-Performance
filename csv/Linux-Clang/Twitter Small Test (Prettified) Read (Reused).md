
----
### Twitter Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3088.81 | 0.145353 | 125.809ms | 3808 | 40 | 116.82 | 1175.72 | 0.0290516 | 0.783771 | 1(Win) | true |
| Glaze | 2523.98 | 0.135854 | 154.868ms | 3808 | 30 | 114.626 | 1438.83 | 0.184992 | 0.963813 | 2(Loss) | true |
| Jsonifier | 2059.93 | 0.189117 | 186.309ms | 3808 | 30 | 333.482 | 1762.97 | 0.243314 | 1.18365 | 3(Loss) | true |
| simdjson (ondemand) | 1422.93 | 0.0885828 | 264.178ms | 3808 | 30 | 153.338 | 2552.2 | 0.0692693 | 1.72124 | 4(Loss) | true |
