
----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (reflection) | 258.982 | 0.273164 | 723.903ms | 1997 | 4890 | 1.97321e+06 | 7353.74 | 2.16939 | 1(Win) | true |
| Jsonifier | 251.062 | 0.897201 | 721.993ms | 1811 | 640 | 2.43801e+06 | 6879.2 | 1.08146 | 2(Loss) | true |
| Glaze | 167.334 | 0.909009 | 996.86ms | 1798 | 320 | 2.7765e+06 | 10247.2 | 0.0078064 | 3(Loss) | true |
