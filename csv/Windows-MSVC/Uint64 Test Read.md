
----
### Uint64 Test Read Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 534.091 | 0.166592 | 227.942ms | 1213 | 1280 | 16665.3 | 2165.94 | 0.0216372 | 5.63421 | 1(Win) | true |
| simdjson (ondemand) | 301.252 | 0.236906 | 403.586ms | 1213 | 30 | 2482.76 | 3840 | 0.173913 | 10.0306 | 2(Loss) | true |
