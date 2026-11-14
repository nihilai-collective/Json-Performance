
----
### Discord Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2758.6 | 0.0327646 | 3060.59ms | 83958 | 30 | 2713.17 | 29025.1 | 0.0333156 | 1(Win) | true |
| Jsonifier (two-stage) | 2258.83 | 0.177123 | 4228.98ms | 83958 | 40 | 157677 | 35446.9 | 0.112878 | 2(Loss) | true |
| Glaze | 2152.43 | 0.088707 | 3859.77ms | 83958 | 2560 | 2.78754e+06 | 37199.1 | 0.14987 | 3(Loss) | true |
| simdjson (ondemand) | 1212.15 | 0.114846 | 6785.36ms | 83958 | 640 | 3.68319e+06 | 66055.3 | 0.419007 | 4(Loss) | true |
