
----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 713.874 | 0.204896 | 538.662ms | 3862 | 2560 | 286081 | 5159.3 | 0.0950644 | 1(Win) | true |
| simdjson (ondemand) | 410.57 | 0.309674 | 898.884ms | 3862 | 4890 | 3.77371e+06 | 8970.68 | 3.04138 | 2(Loss) | true |
