
----
### String Test Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 4636.7 | 1.1855 | 217.244ms | 9578 | 640 | 349073 | 1970 | 0.264658 | 1(Win) | true |
| simdjson (stage-1) | 3102.68 | 1.28375 | 315.904ms | 9578 | 40 | 57133.9 | 2944 | 0.290698 | 2(Loss) | true |
