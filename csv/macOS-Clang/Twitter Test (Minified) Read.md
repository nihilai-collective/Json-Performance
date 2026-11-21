
----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2122.64 | 0.39655 | 5381.59ms | 466906 | 80 | 5.53596e+07 | 209775 | 0.0977175 | 1(Win) | true |
| Jsonifier (two-stage) | 1608.49 | 0.509559 | 7062.24ms | 466906 | 80 | 1.59185e+08 | 276829 | 1.12999 | 2(Loss) | true |
| Glaze | 1499.36 | 0.428732 | 7579.77ms | 466906 | 320 | 5.18766e+08 | 296978 | 0.599053 | 3(Loss) | true |
| simdjson (ondemand) | 771.94 | 0.22212 | 7493.44ms | 466906 | 160 | 2.62656e+08 | 576828 | 0.56947 | 4(Loss) | true |
