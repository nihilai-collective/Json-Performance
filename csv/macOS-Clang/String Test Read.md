
----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (ondemand) | 788.306 | 0.800819 | 1160.03ms | 9578 | 160 | 1.37768e+06 | 11587.2 | 0.554527 | 1(Win) | true |
| Jsonifier (generic) | 638.181 | 0.666001 | 1466.02ms | 9578 | 160 | 1.45389e+06 | 14313 | 0.490014 | 2(Loss) | true |
