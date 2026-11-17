
----
### Stream Formats Large Test (NDJSON) Read Results [(View the data used in the following test)](./json/Stream%20Formats%20Large%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Stream%20Formats%20Large%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Stream%20Formats%20Large%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 26025.3 | 0.179509 | 7856.16ms | 16197086 | 80 | 9.08125e+07 | 593529 | 0.0162139 | 0.0951247 | 1(Win) | true |
| simdjson (ondemand) | 9028.81 | 0.0518091 | 5351.34ms | 16197086 | 40 | 3.14256e+07 | 1.71083e+06 | 0.171892 | 0.274208 | 2(Loss) | true |
