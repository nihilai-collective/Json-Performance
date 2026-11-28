
----
### Int64 Test Read (Reused) Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1426.98 | 0.26644 | 92.6409ms | 1313 | 320 | 1749.22 | 877.5 | 0.0711744 | 1.68424 | 1(Win) | true |
| Glaze | 445.218 | 0.188293 | 290.899ms | 1313 | 40 | 1121.79 | 2812.5 | 0.383707 | 5.50535 | 2(Loss) | true |
| simdjson (ondemand) | 331.044 | 0.11302 | 400.164ms | 1313 | 80 | 1462.03 | 3782.5 | 0.263678 | 7.40386 | 3(Loss) | true |
