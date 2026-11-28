
----
### Double Test Read Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1308.83 | 0.0366469 | 137.122ms | 1811 | 320 | 74.8335 | 1319.58 | 0.074416 | 1.85219 | 1(Win) | true |
| Glaze | 898.006 | 0.101263 | 200.106ms | 1811 | 30 | 113.789 | 1923.27 | 0.0520219 | 2.72006 | 2(Loss) | true |
| simdjson (ondemand) | 399.78 | 0.0680604 | 437.989ms | 1811 | 30 | 259.361 | 4320.13 | 0.0701646 | 6.15794 | 3(Loss) | true |
