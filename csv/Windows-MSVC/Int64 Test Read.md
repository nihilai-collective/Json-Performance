
----
### Int64 Test Read Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 883.904 | 0.809464 | 148.58ms | 1313 | 1280 | 168316 | 1416.64 | 1.94138 | 2.74976 | 1(Win) | true |
| Glaze | 352.849 | 0.279328 | 372.783ms | 1313 | 160 | 15721.7 | 3548.75 | 0.141093 | 6.94081 | 2(Loss) | true |
| simdjson (ondemand) | 278.958 | 0.0885614 | 475.934ms | 1313 | 80 | 1264.24 | 4488.75 | 0.251256 | 8.81254 | 3(Loss) | true |
