
----
### Double Test Write Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 494.672 | 0.227807 | 404.562ms | 1997 | 40 | 3076.92 | 3850 | 0.172861 | 4.9841 | 1(Win) | true |
| Glaze | 130.031 | 0.397686 | 1266.27ms | 1798 | 4890 | 1.34485e+07 | 13186.9 | 0.0371842 | 18.9934 | 2(Loss) | true |
