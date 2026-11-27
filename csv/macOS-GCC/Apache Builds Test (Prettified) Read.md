
----
### Apache Builds Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1340.61 | 0.200814 | 9036.52ms | 124597 | 320 | 1.01379e+07 | 88635.2 | 0.0252785 | 1(Win) | true |
| Glaze | 1309.19 | 0.0444592 | 9182.58ms | 124597 | 4890 | 7.96242e+06 | 90762.4 | 0.326032 | 2(Loss) | true |
| Jsonifier (two-stage) | 1259.08 | 0.249059 | 5063.36ms | 124597 | 40 | 2.20991e+06 | 94374.4 | 0.23904 | 3(Loss) | true |
| simdjson (reflection) | 1189.63 | 0.0772722 | 5313.68ms | 124597 | 1280 | 7.62514e+06 | 99884 | 0.200634 | 4(Loss) | true |
| simdjson (ondemand) | 948.869 | 0.240891 | 6364.2ms | 124597 | 320 | 2.91201e+07 | 125228 | 0.237571 | 5(Loss) | true |
