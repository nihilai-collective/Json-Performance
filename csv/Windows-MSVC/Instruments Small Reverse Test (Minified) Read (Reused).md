
----
### Instruments Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 481.207 | 0.130601 | 952.625ms | 4669 | 1280 | 186933 | 9253.2 | 0.0481021 | 6.30194 | 1(Win) | true |
| simdjson (ondemand) | 203.636 | 0.0960351 | 2216.88ms | 4669 | 2560 | 1.12886e+06 | 21866.1 | 0.311476 | 14.911 | 2(Loss) | true |
