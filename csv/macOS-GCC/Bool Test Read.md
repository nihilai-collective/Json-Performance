
----
### Bool Test Read Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2098 | 1.71862 | 43.4519ms | 905 | 4890 | 244430 | 411.38 | 1.90239 | 1(Win) | true |
| Glaze | 1495.47 | 1.24864 | 62.4689ms | 905 | 4890 | 253934 | 577.126 | 2.72794 | 2(Loss) | true |
| simdjson (reflection) | 878.18 | 0.4255 | 98.466ms | 905 | 1280 | 22384 | 982.8 | 0.162536 | 3(Loss) | true |
| simdjson (ondemand) | 424.965 | 1.99837 | 223.781ms | 905 | 30 | 49415.7 | 2030.93 | 0 | 4(Loss) | true |
