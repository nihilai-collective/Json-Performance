
----
### Twitter Small Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 865.047 | 0.281239 | 439.546ms | 3770 | 320 | 43722.6 | 4156.25 | 0.805489 | 3.49921 | 1(Win) | true |
| simdjson (ondemand) | 373.349 | 0.212113 | 1018.76ms | 3770 | 30 | 12517.2 | 9630 | 0.755754 | 8.12389 | 2(Loss) | true |
