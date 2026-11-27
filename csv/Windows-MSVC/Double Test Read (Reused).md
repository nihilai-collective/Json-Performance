
----
### Double Test Read (Reused) Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1140.94 | 0.255955 | 158.285ms | 1811 | 80 | 1200.95 | 1513.75 | 0.0825083 | 2.13441 | 1(Win) | true |
| Glaze | 491.12 | 0.19679 | 361.149ms | 1811 | 30 | 1436.78 | 3516.67 | 0.189934 | 5.00283 | 2(Loss) | true |
| simdjson (ondemand) | 336.231 | 0.174209 | 530.261ms | 1811 | 30 | 2402.3 | 5136.67 | 0.129618 | 7.31377 | 3(Loss) | true |
