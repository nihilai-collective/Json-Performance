
----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 321.172 | 0.10448 | 524.138ms | 1811 | 80 | 2525.32 | 5377.5 | 0.278164 | 7.65581 | 1(Win) | true |
| simdjson (ondemand) | 117.791 | 0.0903455 | 1259.66ms | 1811 | 40 | 7019.23 | 14662.5 | 1.48376 | 20.9669 | 2(Loss) | true |
