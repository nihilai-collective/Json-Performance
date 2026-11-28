
----
### Double Test Write Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 279.532 | 0.397632 | 686.963ms | 1997 | 2560 | 1.87886e+06 | 6813.12 | 0.548308 | 1(Win) | true |
| Glaze | 208.602 | 0.276565 | 820.813ms | 1798 | 640 | 330765 | 8220 | 1.14655 | 2(Loss) | true |
