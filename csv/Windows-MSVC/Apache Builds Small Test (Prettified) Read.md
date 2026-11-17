
----
### Apache Builds Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1392.8 | 0.180144 | 233.07ms | 3370 | 2560 | 44234.5 | 2307.5 | 0.0372288 | 2.16449 | 1(Win) | true |
| Jsonifier | 1193.63 | 0.0798599 | 271.91ms | 3370 | 4890 | 22609.4 | 2692.54 | 0.0769532 | 2.52761 | 2(Loss) | true |
| Glaze | 950.743 | 0.125826 | 339.862ms | 3370 | 1280 | 23157 | 3380.39 | 0.04851 | 3.17701 | 3(Loss) | true |
| simdjson (ondemand) | 837.337 | 0.0799181 | 386.467ms | 3370 | 4890 | 46010.7 | 3838.22 | 0.0432814 | 3.61019 | 4(Loss) | true |
