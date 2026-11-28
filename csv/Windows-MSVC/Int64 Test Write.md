
----
### Int64 Test Write Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 610.073 | 0.273735 | 208.131ms | 1313 | 80 | 2525.32 | 2052.5 | 0 | 4.0021 | 1(Win) | true |
| Glaze | 132.846 | 0.498058 | 952.412ms | 1313 | 2560 | 5.64198e+06 | 9425.74 | 0.101431 | 18.5761 | 2(Loss) | true |
