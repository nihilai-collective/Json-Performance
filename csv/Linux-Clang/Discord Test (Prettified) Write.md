
----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 17127.8 | 0.443725 | 516.887ms | 94370 | 640 | 347917 | 5254.53 | 0.238398 | 0.143774 | 1(Win) | true |
| Glaze | 3136.84 | 0.0675895 | 2890.31ms | 94370 | 4890 | 1.83887e+06 | 28690.7 | 0.354878 | 0.788496 | 2(Loss) | true |
