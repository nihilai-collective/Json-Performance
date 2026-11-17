
----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 185.024 | 0.129633 | 514.022ms | 905 | 4890 | 178807 | 4664.68 | 0.330938 | 1(Win) | true |
| simdjson (ondemand) | 169.662 | 0.734051 | 550.857ms | 905 | 160 | 223100 | 5087.02 | 1.35271 | 2(Loss) | true |
