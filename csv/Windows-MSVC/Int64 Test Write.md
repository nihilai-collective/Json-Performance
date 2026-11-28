
----
### Int64 Test Write Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 603.639 | 0.231158 | 211.179ms | 1313 | 160 | 3678.85 | 2074.38 | 0.150421 | 4.04512 | 1(Win) | true |
| Glaze | 131.049 | 0.124002 | 1083.09ms | 1313 | 40 | 5615.38 | 9555 | 0.226244 | 18.8094 | 2(Loss) | true |
