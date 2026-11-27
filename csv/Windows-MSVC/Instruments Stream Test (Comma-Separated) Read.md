
----
### Instruments Stream Test (Comma-Separated) Read Results [(Here is the data we used for this test)](./json/Instruments%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1259.62 | 0.214625 | 5214.25ms | 4197495 | 80 | 3.72176e+09 | 3.17796e+06 | 0.455738 | 1.96536 | 1(Win) | true |
| simdjson (ondemand) DID NOT CONVERGE | 830.239 | 0.299885 | 7951.15ms | 4197495 | 30 | 6.27199e+09 | 4.82155e+06 | 2.84696 | 2.98191 | -(Loss) | false |
