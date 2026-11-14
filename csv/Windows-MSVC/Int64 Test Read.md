
----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1589.92 | 0.082682 | 233.882ms | 3862 | 4890 | 17939.2 | 2316.52 | 0.193541 | 1.89547 | 1(Win) | true |
| Glaze | 953.749 | 0.0692062 | 389.972ms | 3862 | 4890 | 34926.6 | 3861.7 | 0.0187585 | 3.16994 | 2(Loss) | true |
| Jsonifier (two-stage) | 877.449 | 0.104038 | 420.77ms | 3862 | 40 | 762.821 | 4197.5 | 0.258758 | 3.44182 | 3(Loss) | true |
| simdjson (ondemand) | 459.283 | 0.155526 | 813.702ms | 3862 | 640 | 99551.8 | 8019.22 | 0.318608 | 6.60154 | 4(Loss) | true |
