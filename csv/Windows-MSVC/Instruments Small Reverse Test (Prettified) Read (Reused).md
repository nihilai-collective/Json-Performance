
----
### Instruments Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 728.411 | 0.156298 | 1072.92ms | 7932 | 40 | 10538.5 | 10385 | 0.0481232 | 4.16631 | 1(Win) | true |
| simdjson (ondemand) | 342.219 | 0.122859 | 2322.87ms | 7932 | 2560 | 1.88802e+06 | 22104.4 | 0.514068 | 8.87204 | 2(Loss) | true |
