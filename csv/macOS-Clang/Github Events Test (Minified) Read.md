
----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1845.75 | 0.0334788 | 2787.05ms | 53331 | 30 | 2553.15 | 27555.5 | 0.351503 | 1(Win) | true |
| Jsonifier (two-stage) | 1565.15 | 0.0721022 | 3360.65ms | 53331 | 2560 | 1.40535e+06 | 32495.5 | 0.46524 | 2(Loss) | true |
| Glaze | 1529.89 | 0.13912 | 3462.54ms | 53331 | 30 | 64170.8 | 33244.4 | 0.0165469 | 3(Loss) | true |
| simdjson (ondemand) | 887.926 | 0.0484214 | 5872.95ms | 53331 | 4890 | 3.76174e+06 | 57280 | 0.0289847 | 4(Loss) | true |
