
----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 467.475 | 0.303837 | 189.386ms | 905 | 80 | 2517.41 | 1846.25 | 0.0677507 | 5.21739 | 1(Win) | true |
| Glaze | 446.322 | 0.275116 | 200.384ms | 905 | 80 | 2264.24 | 1933.75 | 0.194301 | 5.47811 | 2(Loss) | true |
| Jsonifier (two-stage) | 165.129 | 0.157113 | 542.218ms | 905 | 30 | 2022.99 | 5226.67 | 0 | 14.8702 | 3(Loss) | true |
| simdjson (ondemand) | 69.1193 | 0.102167 | 1266.61ms | 905 | 4890 | 795852 | 12486.7 | 0.0775968 | 35.7099 | 4(Loss) | true |
