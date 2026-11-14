
----
### String Test Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2953.75 | 0.52041 | 350.93ms | 9578 | 320 | 82879.1 | 3092.44 | 0.135026 | 1(Win) | true |
| simdjson (stage-1) | 2872.62 | 0.291784 | 360.488ms | 9578 | 1280 | 110186 | 3179.77 | 0.0974453 | 2(Loss) | true |
