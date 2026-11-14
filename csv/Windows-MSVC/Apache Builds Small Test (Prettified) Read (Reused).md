
----
### Apache Builds Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2067.69 | 0.170107 | 183.822ms | 3370 | 4890 | 34185.5 | 1554.34 | 0.248218 | 1.45228 | 1(Win) | true |
| Glaze | 1719.61 | 0.0845432 | 218.325ms | 3370 | 4890 | 12208.6 | 1868.96 | 0.214189 | 1.74735 | 2(Loss) | true |
| Jsonifier | 1699.55 | 0.153439 | 224.723ms | 3370 | 2560 | 21552.7 | 1891.02 | 0.111672 | 1.77115 | 3(Loss) | true |
| simdjson (ondemand) | 1547.69 | 0.0955188 | 233.041ms | 3370 | 2560 | 10071.8 | 2076.56 | 0.157764 | 1.94425 | 4(Loss) | true |
