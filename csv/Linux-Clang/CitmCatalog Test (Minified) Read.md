
----
### CitmCatalog Test (Minified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 10753.1 | 0.0439153 | 5165.78ms | 500299 | 2560 | 971985 | 44370.5 | 0.00113126 | 0.477922 | 2.5935 | 0.189557 | 2.1762e-05 | 1.46163e-06 | 9.2679e-07 | 1(Win) | true |
| simdjson (stage-1) | 9358.24 | 0.073264 | 5814.34ms | 500299 | 30 | 41857.5 | 50984.2 | 0.183511 | 0.540448 | 2.57783 | 0.112559 | 4.73717e-05 | 1.39916e-06 | 6.66268e-08 | 2(Loss) | true |
