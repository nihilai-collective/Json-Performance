
----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 808.661 | 0.574411 | 6242.85ms | 53331 | 4890 | 6.38235e+08 | 62894.6 | 0.112612 | 3.75623 | 1(Win) | true |
| simdjson (ondemand) | 722.005 | 0.306867 | 7434.66ms | 53331 | 30 | 1.40185e+06 | 70443.3 | 0.0852475 | 4.20776 | 2(Loss) | true |
