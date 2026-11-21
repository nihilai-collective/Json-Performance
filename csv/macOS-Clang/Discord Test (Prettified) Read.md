
----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2368.34 | 0.366493 | 3419.42ms | 83958 | 80 | 1.22817e+06 | 33807.8 | 0.219547 | 1(Win) | true |
| Glaze | 1841.22 | 0.130079 | 4377.76ms | 83958 | 2560 | 8.19154e+06 | 43486.7 | 0.114157 | 2(Loss) | true |
| Jsonifier (two-stage) | 1811.68 | 0.0870935 | 4673.15ms | 83958 | 1280 | 1.89647e+06 | 44195.9 | 0.0546945 | 3(Loss) | true |
| simdjson (ondemand) | 1101.46 | 0.992386 | 7724.36ms | 83958 | 30 | 1.56124e+07 | 72693.3 | 0.712255 | 4(Loss) | true |
