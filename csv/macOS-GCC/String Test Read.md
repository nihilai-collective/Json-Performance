
----
### String Test Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 4310.58 | 0.344907 | 229.679ms | 9578 | 4890 | 261211 | 2119.04 | 0.210031 | 1(Win) | true |
| simdjson (stage-1) | 2975.38 | 0.400028 | 316.993ms | 9578 | 4890 | 737487 | 3069.96 | 0.450176 | 2(Loss) | true |
