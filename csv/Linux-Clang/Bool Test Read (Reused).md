
----
### Bool Test Read (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2212.02 | 0.132106 | 754.348ms | 905 | 4890 | 1299.19 | 390.176 | 0.0182468 | 2.56468 | 12.842 | 2.17127 | 0.00111311 | 0.000147556 | 1.51397e-05 | 1(Win) | true |
| Glaze | 1645.81 | 0.0825688 | 766.742ms | 905 | 4890 | 916.804 | 524.406 | 0.0568845 | 3.39313 | 16.9249 | 2.17127 | 0.00114226 | 9.8973e-05 | 1.22021e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 642.509 | 0.207272 | 851.701ms | 905 | 640 | 4961.36 | 1343.29 | 0.169422 | 8.11372 | 41.6022 | 4.94807 | 0.00116195 | 0.000117403 | 2.24448e-05 | 3(Loss) | true |
| simdjson (ondemand) | 290.057 | 0.235426 | 1019.2ms | 905 | 1280 | 62813.2 | 2975.54 | 0.235252 | 17.8128 | 88.3271 | 9.35912 | 0.020821 | 0.000132079 | 1.46754e-05 | 4(Loss) | true |
