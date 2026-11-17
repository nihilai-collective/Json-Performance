
----
### Int64 Test Read (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 633.582 | 0.059313 | 592.071ms | 3862 | 160 | 1902.12 | 5813.12 | 0.204697 | 3.88784 | 1(Win) | true |
| simdjson (ondemand) | 323.213 | 0.209135 | 1160.86ms | 3862 | 1280 | 726959 | 11395.2 | 0.137615 | 7.64213 | 2(Loss) | true |
