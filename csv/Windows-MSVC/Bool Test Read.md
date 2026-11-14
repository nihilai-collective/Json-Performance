
----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 239.434 | 0.0790359 | 367.258ms | 905 | 4890 | 39690 | 3604.64 | 0.252034 | 12.6246 | 1(Win) | true |
| simdjson (ondemand) | 119.705 | 0.138696 | 708.326ms | 905 | 30 | 3000 | 7210 | 0.551724 | 25.3172 | 2(Loss) | true |
