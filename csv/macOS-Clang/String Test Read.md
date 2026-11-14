
----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (ondemand) | 861.382 | 0.0628397 | 1167.37ms | 9578 | 40 | 1776.18 | 10604.2 | 0.0914678 | 1(Win) | true |
| Jsonifier (generic) | 567.298 | 0.616122 | 1696.85ms | 9578 | 640 | 6.29855e+06 | 16101.4 | 1.81067 | 2(Loss) | true |
