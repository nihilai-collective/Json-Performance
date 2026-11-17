
----
### Discord Small Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1730.79 | 0.0932856 | 290.531ms | 4857 | 40 | 249.307 | 2676.22 | 0.0333292 | 1.41719 | 1(Win) | true |
| simdjson (reflection) | 1677.19 | 0.0967647 | 281.661ms | 4857 | 30 | 214.254 | 2761.77 | 0.109713 | 1.46245 | 2(Loss) | true |
| Glaze | 1588.82 | 0.0436604 | 294.088ms | 4857 | 160 | 259.23 | 2915.38 | 0.116059 | 1.54319 | 3(Loss) | true |
| Jsonifier (two-stage) | 1508.66 | 0.191706 | 337.788ms | 4857 | 30 | 1039.31 | 3070.27 | 0.327862 | 1.62768 | 4(Loss) | true |
| simdjson (ondemand) | 1282.34 | 0.189439 | 361.427ms | 4857 | 4890 | 228969 | 3612.14 | 0.0247856 | 1.91624 | 5(Loss) | true |
