
----
### Amazon Cellphones Test (NDJSON) Read Results [(View the data used in the following test)](./json/Amazon%20Cellphones%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3676.58 | 0.103337 | 7323.16ms | 277673 | 640 | 3.54547e+06 | 72026.2 | 0.103696 | 1(Win) | true |
| simdjson (ondemand) | 3101.64 | 0.05733 | 8617.51ms | 277673 | 2560 | 6.13319e+06 | 85377.2 | 0.0186235 | 2(Loss) | true |
