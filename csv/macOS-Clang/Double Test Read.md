
----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 729.306 | 0.422692 | 239.51ms | 1811 | 4890 | 489975 | 2368.15 | 1.11899 | 1(Win) | true |
| Glaze | 605.048 | 0.899607 | 277.88ms | 1811 | 640 | 422030 | 2854.49 | 0.635973 | 2(Loss) | true |
| Jsonifier (two-stage) | 301.142 | 0.299928 | 552.636ms | 1811 | 2560 | 757477 | 5735.19 | 0.794699 | 3(Loss) | true |
| simdjson (ondemand) | 198.138 | 0.138126 | 1011.16ms | 1811 | 30 | 4348.85 | 8716.67 | 0.459447 | 4(Loss) | true |
