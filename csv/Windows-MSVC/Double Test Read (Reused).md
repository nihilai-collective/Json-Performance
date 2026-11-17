
----
### Double Test Read (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 386.918 | 0.121166 | 475.965ms | 1811 | 80 | 2340.19 | 4463.75 | 0.140213 | 6.37303 | 1(Win) | true |
| simdjson (ondemand) | 148.646 | 0.116057 | 1174.29ms | 1811 | 4890 | 889172 | 11618.9 | 0.0301634 | 16.6198 | 2(Loss) | true |
