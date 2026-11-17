
----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1725.83 | 0.158703 | 6857.08ms | 466906 | 640 | 1.07304e+08 | 258007 | 1.57166 | 1.4343 | 1(Win) | true |
| Jsonifier (two-stage) | 1686.4 | 0.152755 | 6838.09ms | 466906 | 160 | 2.60283e+07 | 264039 | 0.278812 | 1.46784 | 2(Loss) | true |
| Glaze | 1641.41 | 0.113046 | 6993.45ms | 466906 | 320 | 3.00945e+07 | 271276 | 0.124217 | 1.50808 | 3(Loss) | true |
| simdjson (ondemand) | 871.571 | 0.0676561 | 6498.62ms | 466906 | 320 | 3.82311e+07 | 510889 | 0.317055 | 2.84037 | 4(Loss) | true |
