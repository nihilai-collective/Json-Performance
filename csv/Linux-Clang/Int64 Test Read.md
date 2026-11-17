
----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2719.6 | 0.113626 | 141.532ms | 3862 | 40 | 94.7173 | 1354.28 | 0.291903 | 0.89251 | 1(Win) | true |
| Glaze | 1347.11 | 0.029907 | 278.944ms | 3862 | 80 | 53.488 | 2734.07 | 0.0292518 | 1.81946 | 2(Loss) | true |
| Jsonifier (two-stage) | 834.066 | 0.0393984 | 446.821ms | 3862 | 40 | 121.071 | 4415.82 | 0.0628027 | 2.95024 | 3(Loss) | true |
| simdjson (ondemand) | 644.051 | 0.0340928 | 582.694ms | 3862 | 30 | 114.033 | 5718.63 | 0.0122422 | 3.8257 | 4(Loss) | true |
