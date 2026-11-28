
----
### Double Test Write Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 389.875 | 0.215787 | 499.286ms | 1997 | 1280 | 142222 | 4884.87 | 0.104721 | 6.31727 | 1(Win) | true |
| simdjson (reflection) | 325.698 | 0.255221 | 583.77ms | 1997 | 1280 | 285080 | 5847.4 | 1.06406 | 7.56802 | 2(Loss) | true |
| Glaze | 290.797 | 0.0520188 | 603.387ms | 1798 | 30 | 282.254 | 5896.57 | 0.0960089 | 8.47762 | 3(Loss) | true |
