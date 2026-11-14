
----
### Github Events Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1819.94 | 0.282567 | 117.584ms | 2158 | 2560 | 26138 | 1130.82 | 0.02414 | 1(Win) | true |
| Jsonifier (two-stage) | 1559.67 | 0.133441 | 135.982ms | 2158 | 160 | 496.062 | 1319.53 | 0.215521 | 2(Loss) | true |
| Glaze | 1543.71 | 0.137409 | 137.908ms | 2158 | 320 | 1073.87 | 1333.17 | 0.343157 | 3(Loss) | true |
| simdjson (ondemand) | 1305.55 | 0.179913 | 161.16ms | 2158 | 640 | 5147.75 | 1576.36 | 0.418546 | 4(Loss) | true |
