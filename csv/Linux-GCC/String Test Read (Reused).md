
----
### String Test Read (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1404.65 | 0.093703 | 779.32ms | 9578 | 4890 | 181564 | 6502.9 | 0.0683813 | 1.75561 | 1(Win) | true |
| Jsonifier (generic) | 889.073 | 0.0345481 | 1170.05ms | 9578 | 40 | 503.946 | 10274 | 0.102142 | 2.77792 | 2(Loss) | true |
