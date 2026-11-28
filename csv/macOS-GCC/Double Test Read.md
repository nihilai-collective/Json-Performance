
----
### Double Test Read Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 854.12 | 0.418716 | 201.945ms | 1811 | 4890 | 350547 | 2022.09 | 2.12082 | 1(Win) | true |
| Glaze | 681.465 | 1.142 | 224.61ms | 1811 | 320 | 268061 | 2534.4 | 2.39173 | 2(Loss) | true |
| simdjson (reflection) | 242.299 | 0.882121 | 737.949ms | 1811 | 320 | 1.26515e+06 | 7128 | 1.85185 | 3(Loss) | true |
| simdjson (ondemand) | 236.417 | 0.304233 | 719.892ms | 1811 | 4890 | 2.41546e+06 | 7305.32 | 1.06831 | 4(Loss) | true |
