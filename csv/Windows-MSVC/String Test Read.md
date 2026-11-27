
----
### String Test Read Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 652.638 | 1.10401 | 650.417ms | 4215 | 640 | 2.9592e+06 | 6159.22 | 0.11909 | 4.63638 | 1(Win) | true |
| Glaze | 518.425 | 0.344098 | 778.314ms | 4215 | 80 | 56947.8 | 7753.75 | 0.847187 | 5.84295 | 2(Loss) | true |
| simdjson (ondemand) | 482.724 | 0.179053 | 894.618ms | 4215 | 320 | 71139.4 | 8327.19 | 0.748659 | 6.27908 | 3(Loss) | true |
