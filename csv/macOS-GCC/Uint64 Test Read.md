
----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 738.953 | 0.409546 | 518.837ms | 3873 | 40 | 16762.1 | 4998.4 | 1.34083 | 1(Win) | true |
| simdjson (ondemand) | 463.696 | 0.102784 | 805.836ms | 3873 | 4890 | 327787 | 7965.53 | 0.0945763 | 2(Loss) | true |
