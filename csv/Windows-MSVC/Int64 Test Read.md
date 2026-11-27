
----
### Int64 Test Read Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1010.07 | 0.312862 | 132.585ms | 1313 | 640 | 9627.45 | 1239.69 | 2.33875 | 2.96665 | 1(Win) | true |
| Glaze | 366.133 | 0.217188 | 368.186ms | 1313 | 30 | 1655.17 | 3420 | 0 | 8.27086 | 2(Loss) | true |
| simdjson (ondemand) | 324.959 | 0.240418 | 420.958ms | 1313 | 30 | 2574.71 | 3853.33 | 0.434405 | 9.29086 | 3(Loss) | true |
