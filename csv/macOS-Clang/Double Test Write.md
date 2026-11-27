
----
### Double Test Write Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 325.297 | 0.0711543 | 591.973ms | 1997 | 4890 | 84860.7 | 5854.61 | 0.0106913 | 1(Win) | true |
| Glaze | 214.171 | 0.102296 | 805.879ms | 1798 | 2560 | 171717 | 8006.25 | 0.0534014 | 2(Loss) | true |
