
----
### Discord Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1626.19 | 0.28914 | 4805.11ms | 83958 | 160 | 3.24277e+06 | 49236.8 | 0.0552127 | 1(Win) | true |
| simdjson (ondemand) | 1217.35 | 0.567873 | 6801.66ms | 83958 | 40 | 5.58026e+06 | 65772.8 | 0.309084 | 2(Loss) | true |
