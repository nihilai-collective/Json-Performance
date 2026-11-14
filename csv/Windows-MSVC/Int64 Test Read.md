
----
### Int64 Test Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3021.64 | 0.12708 | 126.219ms | 3862 | 640 | 1535.58 | 1218.91 | 0.141207 | 0.802222 | 1(Win) | true |
| simdjson (stage-1) | 626.884 | 0.268884 | 594.476ms | 3862 | 1280 | 319441 | 5875.23 | 0.0545488 | 3.91885 | 2(Loss) | true |
