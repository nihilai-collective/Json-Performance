
----
### Double Test Read Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1350.62 | 0.0261501 | 131.368ms | 1811 | 320 | 35.7821 | 1278.75 | 0.176999 | 1.79675 | 1(Win) | true |
| Glaze | 894.669 | 0.162185 | 196.257ms | 1811 | 4890 | 47933.9 | 1930.44 | 0.0142704 | 2.73046 | 2(Loss) | true |
| simdjson (ondemand) | 451.197 | 0.143824 | 385.304ms | 1811 | 4890 | 148209 | 3827.83 | 0.0105482 | 5.4505 | 3(Loss) | true |
