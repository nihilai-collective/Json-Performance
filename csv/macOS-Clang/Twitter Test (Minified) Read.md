
----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1777.3 | 3.1287 | 5992.23ms | 466906 | 160 | 9.83071e+09 | 250535 | 0.086602 | 1(Win) | true |
| Jsonifier (two-stage) | 1636.97 | 0.760629 | 7052.81ms | 466906 | 80 | 3.42464e+08 | 272013 | 2.42737 | 2(Loss) | true |
| Glaze | 1353.5 | 0.98101 | 8166.9ms | 466906 | 30 | 3.1247e+08 | 328981 | 0.931065 | 3(Loss) | true |
| simdjson (ondemand) | 811.133 | 0.0866537 | 7472.21ms | 466906 | 640 | 1.4482e+08 | 548956 | 0.428692 | 4(Loss) | true |
