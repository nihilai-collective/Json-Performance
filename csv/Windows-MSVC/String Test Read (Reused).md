
----
### String Test Read (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1359.27 | 0.0669695 | 894.121ms | 9578 | 80 | 1620.25 | 6720 | 0.296736 | 1.81301 | 1(Win) | true |
| Glaze | 945.457 | 0.200077 | 1202.9ms | 9578 | 2560 | 956536 | 9661.25 | 0.111717 | 2.6108 | 2(Loss) | true |
| Jsonifier (two-stage) | 826.384 | 0.0838128 | 1361.1ms | 9578 | 30 | 2574.71 | 11053.3 | 0.180614 | 2.98572 | 3(Loss) | true |
| simdjson (ondemand) | 667.467 | 0.298046 | 1624.09ms | 9578 | 640 | 1.06472e+06 | 13685 | 0.241469 | 3.7029 | 4(Loss) | true |
