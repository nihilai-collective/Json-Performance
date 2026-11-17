
----
### Instruments Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2847.68 | 0.766126 | 281.927ms | 7932 | 640 | 265071 | 2656.39 | 0.119312 | 1(Win) | true |
| Jsonifier (two-stage) | 2497.87 | 0.534544 | 321.482ms | 7932 | 640 | 167715 | 3028.39 | 0.996739 | 2(Loss) | true |
| Glaze | 1653.99 | 0.355431 | 507.243ms | 7932 | 1280 | 338236 | 4573.51 | 2.58949 | 3(Loss) | true |
| simdjson (ondemand) | 821.421 | 0.456976 | 824.31ms | 7932 | 1280 | 2.26689e+06 | 9209.09 | 0.205654 | 4(Loss) | true |
