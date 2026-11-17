
----
### Github Events Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1646.04 | 0.458492 | 127.797ms | 2158 | 320 | 10515.6 | 1250.29 | 0.0651923 | 1(Win) | true |
| Jsonifier (two-stage) | 1467.09 | 0.260264 | 149.602ms | 2158 | 30 | 399.89 | 1402.8 | 0.392899 | 2(Loss) | true |
| Glaze | 1361.85 | 0.643776 | 149.798ms | 2158 | 160 | 15143.8 | 1511.2 | 0.0917302 | 3(Loss) | true |
| simdjson (ondemand) | 1285.4 | 0.244044 | 179.524ms | 2158 | 40 | 610.687 | 1601.08 | 1.21855 | 4(Loss) | true |
