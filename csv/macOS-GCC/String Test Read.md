
----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 811.486 | 0.0834861 | 1176.59ms | 9578 | 4890 | 431842 | 11256.3 | 0.12054 | 1(Win) | true |
| simdjson (ondemand) | 793.079 | 0.1248 | 1173.94ms | 9578 | 2560 | 528917 | 11517.5 | 0.651255 | 2(Loss) | true |
