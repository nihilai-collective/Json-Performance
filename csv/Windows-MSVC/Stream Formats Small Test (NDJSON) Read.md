
----
### Stream Formats Small Test (NDJSON) Read Results [(View the data used in the following test)](./json/Stream%20Formats%20Small%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Stream%20Formats%20Small%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Stream%20Formats%20Small%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3687.83 | 0.23638 | 6280.29ms | 16002592 | 30 | 2.87066e+09 | 4.13828e+06 | 0.372035 | 0.67133 | 1(Win) | true |
| simdjson (ondemand) | 2739.3 | 0.256634 | 8537.17ms | 16002592 | 40 | 8.17691e+09 | 5.57123e+06 | 0.185253 | 0.903813 | 2(Loss) | true |
