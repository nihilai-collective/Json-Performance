
----
### Int64 Test Write Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 584.275 | 0.183265 | 225.573ms | 1313 | 160 | 2468.16 | 2143.12 | 0.263158 | 4.18556 | 1(Win) | true |
| Glaze | 122.091 | 0.369833 | 1043.14ms | 1313 | 4890 | 7.03524e+06 | 10256 | 0.301199 | 20.2093 | 2(Loss) | true |
