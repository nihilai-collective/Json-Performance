
----
### String Test Read (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1198.06 | 0.335519 | 951.744ms | 9578 | 1280 | 837599 | 7624.22 | 0.125169 | 2.52916 | 1(Win) | true |
| simdjson (ondemand) | 1147.13 | 0.101486 | 983.406ms | 9578 | 4890 | 319336 | 7962.72 | 0.134413 | 2.64268 | 2(Loss) | true |
