
----
### Double Test Read Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 761.602 | 0.102727 | 229.901ms | 1811 | 40 | 217.076 | 2267.72 | 0.312477 | 3.2126 | 1(Win) | true |
| simdjson (ondemand) | 444.39 | 0.121804 | 392.481ms | 1811 | 4890 | 109583 | 3886.46 | 0.109494 | 5.53322 | 2(Loss) | true |
