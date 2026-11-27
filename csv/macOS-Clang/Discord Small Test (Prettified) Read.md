
----
### Discord Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2206.06 | 0.0884161 | 299.222ms | 6701 | 80 | 524.804 | 2896.82 | 0.0733024 | 1(Win) | true |
| Jsonifier (two-stage) | 1895.49 | 0.0954415 | 345.646ms | 6701 | 2560 | 26506.4 | 3371.46 | 0.217428 | 2(Loss) | true |
| Glaze | 1615.06 | 0.101672 | 404.578ms | 6701 | 320 | 5179.17 | 3956.87 | 0.0552351 | 3(Loss) | true |
| simdjson (ondemand) | 875.252 | 0.125941 | 766.019ms | 6701 | 1280 | 108233 | 7301.41 | 0.253525 | 4(Loss) | true |
