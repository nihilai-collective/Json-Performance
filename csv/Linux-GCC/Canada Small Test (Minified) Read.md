
----
### Canada Small Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 906.086 | 0.153752 | 492.028ms | 4630 | 2560 | 143717 | 4873.17 | 0.125067 | 2.71665 | 1(Win) | true |
| Jsonifier (two-stage) | 830.885 | 0.060247 | 534.84ms | 4630 | 40 | 410.025 | 5314.23 | 0.0368644 | 2.96457 | 2(Loss) | true |
| simdjson (ondemand) | 739.043 | 0.110862 | 628.209ms | 4630 | 30 | 1316.17 | 5974.63 | 0.111458 | 3.33578 | 3(Loss) | true |
| Glaze | 699.52 | 0.0648182 | 638.795ms | 4630 | 80 | 1339.2 | 6312.2 | 0.206316 | 3.52464 | 4(Loss) | true |
| simdjson (reflection) | 687.714 | 0.126359 | 639.309ms | 4630 | 30 | 1974.6 | 6420.57 | 0.317697 | 3.58439 | 5(Loss) | true |
