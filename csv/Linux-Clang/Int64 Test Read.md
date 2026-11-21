
----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2766.4 | 0.102145 | 134.39ms | 3862 | 30 | 55.4816 | 1331.37 | 0.149996 | 0.876739 | 1(Win) | true |
| Jsonifier | 2747.24 | 0.0395505 | 138.083ms | 3862 | 160 | 44.9836 | 1340.65 | 0.0727788 | 0.883289 | 2(Loss) | true |
| Glaze | 1422.42 | 0.0222352 | 269.758ms | 3862 | 160 | 53.0361 | 2589.32 | 0.0513867 | 1.72351 | 3(Loss) | true |
| simdjson (ondemand) | 795.255 | 0.0447483 | 465.796ms | 3862 | 30 | 128.851 | 4631.33 | 0.0518478 | 3.09568 | 4(Loss) | true |
