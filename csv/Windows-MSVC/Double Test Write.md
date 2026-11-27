
----
### Double Test Write Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 464.509 | 0.123505 | 435.332ms | 1997 | 40 | 1025.64 | 4100 | 0.162338 | 5.27187 | 1(Win) | true |
| Glaze | 135.085 | 0.565061 | 1326.84ms | 1798 | 2560 | 1.31703e+07 | 12693.6 | 0.368481 | 18.277 | 2(Loss) | true |
