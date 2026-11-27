
----
### String Test Read Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (stage-1) | 2389.84 | 0.463043 | 172.357ms | 4215 | 4890 | 296625 | 1682.01 | 0.25684 | 1(Win) | true |
| simdjson (stage-1) | 1610.22 | 0.308847 | 257.635ms | 4215 | 4890 | 290684 | 2496.39 | 0.283897 | 2(Loss) | true |
