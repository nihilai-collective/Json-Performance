
----
### String Test Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5647.3 | 0.123238 | 164.776ms | 9578 | 2560 | 10171.7 | 1617.46 | 0.157225 | 0.530777 | 1(Win) | true |
| simdjson (stage-1) | 2669.39 | 0.0833366 | 344.551ms | 9578 | 4890 | 39765.4 | 3421.86 | 0.153145 | 1.13222 | 2(Loss) | true |
