
----
### Int64 Test Read Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 744.865 | 0.0953579 | 171.611ms | 1313 | 40 | 102.789 | 1681.08 | 0.0739161 | 3.27365 | 1(Win) | true |
| simdjson (ondemand) | 365.446 | 0.0339883 | 347.949ms | 1313 | 80 | 108.501 | 3426.43 | 0.123155 | 6.72413 | 2(Loss) | true |
