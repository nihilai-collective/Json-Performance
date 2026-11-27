
----
### Int64 Test Read Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 499.87 | 0.199601 | 261.268ms | 1313 | 80 | 2000 | 2505 | 0 | 4.88858 | 1(Win) | true |
| simdjson (ondemand) | 281.783 | 0.125599 | 454.703ms | 1313 | 80 | 2492.09 | 4443.75 | 0.308469 | 8.74444 | 2(Loss) | true |
