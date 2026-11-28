
----
### Int64 Test Read (Reused) Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1352.79 | 0.374035 | 111.16ms | 1313 | 160 | 1917.85 | 925.625 | 0.338753 | 1.77595 | 1(Win) | true |
| Glaze | 410.538 | 0.232222 | 313.931ms | 1313 | 4890 | 245323 | 3050.08 | 0.0613157 | 5.94391 | 2(Loss) | true |
| simdjson (ondemand) | 300.946 | 0.232672 | 432.652ms | 1313 | 4890 | 458301 | 4160.8 | 0.0840174 | 8.15572 | 3(Loss) | true |
