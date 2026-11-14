
----
### String Test Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3571.13 | 0.128366 | 267.854ms | 9578 | 320 | 3449.75 | 2557.81 | 0.0366659 | 0.842856 | 1(Win) | true |
| simdjson (stage-1) | 2135.43 | 0.156322 | 446.368ms | 9578 | 40 | 1788.46 | 4277.5 | 0.368789 | 1.41821 | 2(Loss) | true |
