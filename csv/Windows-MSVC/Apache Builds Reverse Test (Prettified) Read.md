
----
### Apache Builds Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 747.458 | 0.400874 | 8100.34ms | 124597 | 2560 | 1.03967e+09 | 158972 | 0.427875 | 4.06518 | 1(Win) | true |
| simdjson (ondemand) | 574.021 | 0.462155 | 5262.76ms | 124597 | 1280 | 1.1715e+09 | 207004 | 0.504302 | 5.29366 | 2(Loss) | true |
