
----
### Double Test Read (Reused) Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1403.15 | 0.0866456 | 127.043ms | 1811 | 40 | 45.4968 | 1230.88 | 0.0777973 | 1.72702 | 1(Win) | true |
| Glaze | 897.244 | 0.109255 | 198.716ms | 1811 | 40 | 176.913 | 1924.9 | 0.0346458 | 2.72125 | 2(Loss) | true |
| simdjson (ondemand) | 438.203 | 0.165343 | 400.827ms | 1811 | 30 | 1274.02 | 3941.33 | 0.0228297 | 5.61055 | 3(Loss) | true |
