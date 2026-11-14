
----
### Apache Builds Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1824.85 | 0.0215651 | 8481.56ms | 124597 | 2560 | 504784 | 65115 | 0.0299003 | 2.78059 | 13.3353 | 2.59718 | 0.00580241 | 3.39846e-06 | 5.51779e-07 | 1(Win) | true |
| simdjson (ondemand) | 1068.13 | 0.0279707 | 6691.65ms | 124597 | 2560 | 2.47865e+06 | 111246 | 0.0179339 | 4.76415 | 23.1406 | 4.67136 | 0.00758609 | 4.53023e-06 | 6.58373e-07 | 2(Loss) | true |
