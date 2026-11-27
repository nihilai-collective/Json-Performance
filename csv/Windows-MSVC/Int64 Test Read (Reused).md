
----
### Int64 Test Read (Reused) Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 639.118 | 0.267765 | 200.12ms | 1313 | 4890 | 134582 | 1959.22 | 0.107337 | 3.82072 | 1(Win) | true |
| simdjson (ondemand) | 309.944 | 0.13643 | 403.779ms | 1313 | 80 | 2430.38 | 4040 | 0.185989 | 7.91501 | 2(Loss) | true |
