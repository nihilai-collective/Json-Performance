
----
### Stream Formats Small Test (Comma-Separated) Read Results [(Here is the data we used for this test)](./json/Stream%20Formats%20Small%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Stream%20Formats%20Small%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Stream%20Formats%20Small%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2958.42 | 0.652959 | 7573.66ms | 16002591 | 80 | 9.0766e+10 | 5.15859e+06 | 2.00355 | 1.02732 | 1(Win) | true |
| simdjson (ondemand) | 1845.98 | 0.314547 | 5864.67ms | 16002591 | 40 | 2.70496e+10 | 8.2673e+06 | 0.753396 | 1.64644 | 2(Loss) | true |
