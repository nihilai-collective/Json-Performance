
----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2684.98 | 0.0688598 | 3021.39ms | 83958 | 2560 | 1.07948e+06 | 29820.9 | 0.0118873 | 0.9213 | 1(Win) | true |
| Jsonifier | 2134.5 | 0.0541408 | 3757.38ms | 83958 | 4890 | 2.01693e+06 | 37511.7 | 0.0682063 | 1.15904 | 2(Loss) | true |
| Glaze | 1987.79 | 0.140958 | 4012.59ms | 83958 | 640 | 2.06319e+06 | 40280.1 | 0.0739853 | 1.24466 | 3(Loss) | true |
| simdjson (ondemand) | 1278.4 | 0.0455079 | 6278.99ms | 83958 | 4890 | 3.97257e+06 | 62631.7 | 0.0129964 | 1.9358 | 4(Loss) | true |
