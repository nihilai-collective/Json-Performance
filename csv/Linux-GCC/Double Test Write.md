
----
### Double Test Write Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 392.705 | 0.0364373 | 498.724ms | 1997 | 30 | 93.6782 | 4849.67 | 0.0267988 | 6.27014 | 1(Win) | true |
| simdjson (reflection) | 318.534 | 0.184498 | 590.596ms | 1997 | 1280 | 155754 | 5978.92 | 0.0413079 | 7.73831 | 2(Loss) | true |
| Glaze | 289.552 | 0.060922 | 609.158ms | 1798 | 30 | 390.478 | 5921.93 | 0.0489465 | 8.51472 | 3(Loss) | true |
