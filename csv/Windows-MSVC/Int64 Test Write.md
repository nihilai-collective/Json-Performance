
----
### Int64 Test Write Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 608.96 | 1.30455 | 219.309ms | 1313 | 640 | 460524 | 2056.25 | 0.136965 | 4.93147 | 1(Win) | true |
| Glaze | 135.265 | 1.62936 | 918.455ms | 1313 | 4890 | 1.11249e+08 | 9257.18 | 1.2392 | 22.4072 | 2(Loss) | true |
