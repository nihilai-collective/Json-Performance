
----
### Instruments Stream Reverse Test (Comma-Separated) Read Results [(Here is the data we used for this test)](./json/Instruments%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 793.743 | 0.0831844 | 8116.26ms | 4197495 | 30 | 5.27989e+08 | 5.04325e+06 | 0.295954 | 3.8286 | 1(Win) | true |
| simdjson (ondemand) | 460.398 | 0.750417 | 6077.52ms | 4197495 | 30 | 1.27714e+11 | 8.69474e+06 | 0.831014 | 6.60105 | 2(Loss) | true |
