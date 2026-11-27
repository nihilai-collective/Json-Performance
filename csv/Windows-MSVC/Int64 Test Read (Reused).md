
----
### Int64 Test Read (Reused) Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 719.317 | 0.111677 | 178.66ms | 1313 | 640 | 2418.79 | 1740.78 | 0.098832 | 4.15644 | 1(Win) | true |
| simdjson (ondemand) | 367.341 | 0.129879 | 344.548ms | 1313 | 80 | 1568.04 | 3408.75 | 0.183688 | 8.21148 | 2(Loss) | true |
