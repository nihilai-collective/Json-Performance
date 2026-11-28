
----
### Double Test Write Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (reflection) | 307.973 | 0.298506 | 644.734ms | 1997 | 4890 | 1.66627e+06 | 6183.94 | 1.63773 | 1(Win) | true |
| Jsonifier | 286.016 | 0.264487 | 645.932ms | 1997 | 4890 | 1.51668e+06 | 6658.67 | 2.13883 | 2(Loss) | true |
| Glaze | 208.075 | 0.545474 | 946.897ms | 1798 | 320 | 646602 | 8240.8 | 0.242107 | 3(Loss) | true |
