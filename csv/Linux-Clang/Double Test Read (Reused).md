
----
### Double Test Read (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1318.97 | 0.51935 | 133.889ms | 1811 | 1280 | 59197 | 1309.44 | 0.146388 | 1.83777 | 1(Win) | true |
| Glaze | 868.557 | 0.0403038 | 202.664ms | 1811 | 40 | 25.6917 | 1988.47 | 0.310411 | 2.81064 | 2(Loss) | true |
| Jsonifier (two-stage) | 463.177 | 0.035136 | 386.702ms | 1811 | 40 | 68.6609 | 3728.82 | 0.279244 | 5.30577 | 3(Loss) | true |
| simdjson (ondemand) | 288.037 | 0.100415 | 598.645ms | 1811 | 80 | 2900.18 | 5996.11 | 0.0849187 | 8.55425 | 4(Loss) | true |
