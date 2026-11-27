
----
### Apache Builds Test (Minified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1570.18 | 0.0253445 | 6497.52ms | 94653 | 1280 | 271737 | 57489.1 | 0.0437486 | 3.22612 | 14.2473 | 2.80962 | 0.00913928 | 8.8316e-06 | 5.25769e-06 | 1(Win) | true |
| simdjson (ondemand) | 1273.65 | 0.0478735 | 7842.25ms | 94653 | 640 | 736782 | 70873.5 | 0.0134126 | 4.0039 | 15.8434 | 3.10317 | 0.0121331 | 2.34244e-05 | 1.56328e-05 | 2(Loss) | true |
