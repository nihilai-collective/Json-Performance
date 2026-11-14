
----
### Int64 Test Read (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 623.637 | 0.204541 | 615.084ms | 3862 | 2560 | 373561 | 5905.82 | 0.0799683 | 3.95251 | 1(Win) | true |
| simdjson (ondemand) | 307.914 | 0.315063 | 1233.35ms | 3862 | 640 | 908946 | 11961.4 | 0.712044 | 8.02223 | 2(Loss) | true |
