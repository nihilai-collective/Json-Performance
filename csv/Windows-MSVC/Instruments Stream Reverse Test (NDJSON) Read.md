
----
### Instruments Stream Reverse Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Instruments%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 734.137 | 0.553158 | 8362.64ms | 4197496 | 30 | 2.72927e+10 | 5.45272e+06 | 0.00751974 | 4.13986 | 1(Win) | true |
| simdjson (ondemand) DID NOT CONVERGE | 549.973 | 0.428804 | 5359.02ms | 4197496 | 40 | 3.89651e+10 | 7.27862e+06 | 3.07408 | 5.52579 | -(Loss) | false |
