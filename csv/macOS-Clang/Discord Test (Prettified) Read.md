
----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1739.11 | 0.0889212 | 4651.71ms | 83958 | 1280 | 2.14532e+06 | 46040 | 0.103713 | 1(Win) | true |
| simdjson (ondemand) | 1469.02 | 0.0616701 | 5537.37ms | 83958 | 2560 | 2.89239e+06 | 54504.7 | 0.17152 | 2(Loss) | true |
