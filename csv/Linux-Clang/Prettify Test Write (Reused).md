
----
### Prettify Test Write (Reused) Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Prettify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Prettify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5589.83 | 0.183638 | 6311.89ms | 699405 | 160 | 7.68255e+06 | 119325 | 0.209805 | 0.442798 | 1(Win) | true |
| Glaze | 3874.79 | 0.146403 | 9007.89ms | 699405 | 320 | 2.0324e+07 | 172140 | 0.217489 | 0.638852 | 2(Loss) | true |
| simdjson (ondemand) | 2214.23 | 0.260159 | 8374.59ms | 767297 | 640 | 4.73086e+08 | 330476 | 0.305309 | 1.11799 | 3(Loss) | true |
