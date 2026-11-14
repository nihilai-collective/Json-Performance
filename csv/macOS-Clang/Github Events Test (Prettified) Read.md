
----
### Github Events Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1824.54 | 0.262456 | 3421.63ms | 65103 | 320 | 2.55246e+06 | 34028.9 | 0.163566 | 1(Win) | true |
| Jsonifier (two-stage) | 1730.23 | 0.066051 | 3611.83ms | 65103 | 4890 | 2.74702e+06 | 35883.7 | 0.0442354 | 2(Loss) | true |
| Glaze | 1689.32 | 0.153292 | 3739.81ms | 65103 | 640 | 2.03139e+06 | 36752.6 | 0.149565 | 3(Loss) | true |
| simdjson (ondemand) | 1053.8 | 0.109679 | 5928.24ms | 65103 | 1280 | 5.34492e+06 | 58917.5 | 0.12769 | 4(Loss) | true |
