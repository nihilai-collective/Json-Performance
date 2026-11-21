
----
### String Test Read (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1426.83 | 0.259791 | 871.174ms | 9578 | 1280 | 354047 | 6401.8 | 0.248348 | 1.72742 | 1(Win) | true |
| Jsonifier (two-stage) | 1404.74 | 0.116647 | 876.574ms | 9578 | 40 | 2301.28 | 6502.5 | 0.115207 | 1.75475 | 2(Loss) | true |
| Glaze | 1090.44 | 0.211729 | 1116.71ms | 9578 | 30 | 9436.78 | 8376.67 | 0.23819 | 2.26457 | 3(Loss) | true |
| simdjson (ondemand) | 873.22 | 0.273439 | 1283.36ms | 9578 | 1280 | 1.04721e+06 | 10460.5 | 0.185565 | 2.82725 | 4(Loss) | true |
