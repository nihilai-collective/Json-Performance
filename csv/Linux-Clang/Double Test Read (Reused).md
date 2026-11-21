
----
### Double Test Read (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1402.26 | 0.19656 | 131.764ms | 1811 | 4890 | 28660.2 | 1231.66 | 0.503247 | 1.72803 | 1(Win) | true |
| Jsonifier (two-stage) | 1392.39 | 0.0336878 | 127.322ms | 1811 | 160 | 27.9369 | 1240.39 | 0.061435 | 1.74111 | 2(Loss) | true |
| Glaze | 944.119 | 0.163716 | 185.764ms | 1811 | 4890 | 43860.6 | 1829.33 | 0.0510141 | 2.58554 | 3(Loss) | true |
| simdjson (ondemand) | 474.021 | 0.15763 | 368.102ms | 1811 | 2560 | 84442.8 | 3643.52 | 0.14574 | 5.18581 | 4(Loss) | true |
