
----
### Int64 Test Write Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 587.186 | 0.3517 | 219.469ms | 1313 | 40 | 2250 | 2132.5 | 0.274295 | 4.16131 | 1(Win) | true |
| Glaze | 126.288 | 0.283393 | 1010.19ms | 1313 | 2560 | 2.02125e+06 | 9915.2 | 0.467803 | 19.537 | 2(Loss) | true |
