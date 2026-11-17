
----
### Random Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Random%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1208.72 | 0.284578 | 6229.45ms | 4506446 | 30 | 3.07141e+09 | 3.55555e+06 | 0.131308 | 2.04817 | 1(Win) | true |
| simdjson (ondemand) | 1031.6 | 0.27108 | 7149.38ms | 4506446 | 30 | 3.82618e+09 | 4.16605e+06 | 1.47791 | 2.39988 | 2(Loss) | true |
