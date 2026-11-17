
----
### Double Test Read (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1179.82 | 0.389073 | 149.47ms | 1811 | 2560 | 83043.3 | 1463.87 | 0.463782 | 2.06008 | 1(Win) | true |
| Glaze | 393.119 | 0.186914 | 385.834ms | 1811 | 30 | 2022.99 | 4393.33 | 0.227101 | 6.25181 | 2(Loss) | true |
| Jsonifier (two-stage) | 378.785 | 0.180256 | 466.36ms | 1811 | 4890 | 330324 | 4559.59 | 0.272947 | 6.49604 | 3(Loss) | true |
| simdjson (ondemand) | 144.568 | 0.0775456 | 1264.54ms | 1811 | 30 | 2574.71 | 11946.7 | 0.0557724 | 17.0892 | 4(Loss) | true |
