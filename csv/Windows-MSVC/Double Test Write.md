
----
### Double Test Write Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 492.175 | 0.295157 | 401.156ms | 1997 | 1280 | 166968 | 3869.53 | 0.165283 | 4.97492 | 1(Win) | true |
| Glaze | 146.807 | 0.125857 | 1253.55ms | 1798 | 30 | 6482.76 | 11680 | 0.142491 | 16.8088 | 2(Loss) | true |
