
----
### Int64 Test Write (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 5108.84 | 0.297898 | 829.074ms | 3862 | 80 | 368.982 | 720.925 | 0.0832957 | 1.04947 | 5.36665 | 0.628949 | 0.00026217 | 2.58933e-05 | 0 | 1(Win) | true |
| Glaze | 2154.62 | 0.192469 | 934.788ms | 3862 | 4890 | 52931.4 | 1709.39 | 0.140228 | 2.42149 | 8.65251 | 1.04868 | 0.00510983 | 6.76192e-05 | 2.86468e-05 | 2(Loss) | true |
