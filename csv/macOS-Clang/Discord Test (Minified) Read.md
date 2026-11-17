
----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2180.24 | 0.986556 | 2544.38ms | 56369 | 160 | 9.46753e+06 | 24656.8 | 0.244263 | 1(Win) | true |
| Glaze | 1270 | 1.30037 | 4213.04ms | 56369 | 80 | 2.42378e+07 | 42328.8 | 1.36362 | 2(Loss) | true |
| Jsonifier (two-stage) | 1026.02 | 1.72448 | 4929.97ms | 56369 | 30 | 2.44912e+07 | 52394.5 | 1.95129 | 3(Loss) | true |
| simdjson (ondemand) | 657.565 | 0.201365 | 8665.12ms | 56369 | 4890 | 1.3252e+08 | 81752.6 | 1.25883 | 4(Loss) | true |
