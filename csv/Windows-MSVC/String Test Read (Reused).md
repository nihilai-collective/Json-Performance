
----
### String Test Read (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 648.539 | 0.183079 | 1675.94ms | 9578 | 2560 | 1.70213e+06 | 14084.4 | 0.197357 | 3.81006 | 1(Win) | true |
| simdjson (ondemand) | 599.449 | 0.211698 | 1778.05ms | 9578 | 1280 | 1.33195e+06 | 15237.8 | 0.0614867 | 4.12296 | 2(Loss) | true |
