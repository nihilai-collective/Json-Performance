
----
### Int64 Test Read Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 545.214 | 0.254259 | 151.613ms | 1313 | 30 | 1022.99 | 2296.67 | 0.291121 | 4.5036 | 1(Win) | true |
| Glaze | 384.103 | 0.240633 | 342.947ms | 1313 | 40 | 2461.54 | 3260 | 0.102145 | 6.37317 | 2(Loss) | true |
| simdjson (ondemand) | 289.583 | 0.126302 | 445.869ms | 1313 | 320 | 9544.57 | 4324.06 | 0.00722648 | 8.48831 | 3(Loss) | true |
