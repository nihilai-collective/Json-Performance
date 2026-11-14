
----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2379.53 | 0.176122 | 3401.78ms | 83958 | 1280 | 4.49554e+06 | 33649 | 0.242167 | 1(Win) | true |
| Glaze | 1873.92 | 0.112434 | 4299.75ms | 83958 | 1280 | 2.95412e+06 | 42727.9 | 0.212253 | 2(Loss) | true |
| Jsonifier (two-stage) | 1784.91 | 0.0910208 | 4505.24ms | 83958 | 2560 | 4.26788e+06 | 44858.6 | 0.108358 | 3(Loss) | true |
| simdjson (ondemand) | 1108.24 | 0.0618779 | 7343.46ms | 83958 | 4890 | 9.77321e+06 | 72248.5 | 0.111799 | 4(Loss) | true |
