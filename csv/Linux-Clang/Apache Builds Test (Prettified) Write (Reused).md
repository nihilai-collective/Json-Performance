
----
### Apache Builds Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 19098.1 | 0.0954569 | 1429.81ms | 136037 | 30 | 1261.44 | 6793.07 | 0.222281 | 0.26638 | 1.27457 | 0.214104 | 0.000291342 | 1.47019e-06 | 9.80126e-07 | 1(Win) | true |
| Glaze | 5813.51 | 0.0799857 | 2981.15ms | 136076 | 1280 | 408057 | 22322.5 | 0.0064821 | 0.867668 | 4.06236 | 0.682685 | 0.00144943 | 7.09622e-06 | 3.65719e-06 | 2(Loss) | true |
