
----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1750.21 | 0.0968458 | 4621.19ms | 83958 | 1280 | 2.51256e+06 | 45748.1 | 0.0367248 | 1(Win) | true |
| simdjson (ondemand) | 1471.29 | 0.0869887 | 5455.75ms | 83958 | 2560 | 5.73715e+06 | 54420.8 | 0.0150873 | 2(Loss) | true |
