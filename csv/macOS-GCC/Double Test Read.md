
----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 905.832 | 0.281507 | 195.128ms | 1811 | 4890 | 140874 | 1906.65 | 0.117853 | 1(Win) | true |
| Glaze | 758.906 | 0.422084 | 219.685ms | 1811 | 4890 | 451200 | 2275.78 | 0.560062 | 2(Loss) | true |
| Jsonifier (two-stage) | 476.785 | 0.767769 | 379.555ms | 1811 | 320 | 247517 | 3622.4 | 0.221337 | 3(Loss) | true |
| simdjson (ondemand) | 137.202 | 0.636889 | 1256.48ms | 1811 | 320 | 2.05679e+06 | 12588 | 0.108156 | 4(Loss) | true |
