
----
### Instruments Small Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 893.928 | 0.0337767 | 1572.22ms | 7932 | 4890 | 39948.9 | 8462.14 | 0.182231 | 5.77335 | 24.1813 | 4.65545 | 0.00563888 | 8.18563e-05 | 3.88785e-05 | 1(Win) | true |
| simdjson (ondemand) | 393.645 | 0.0419415 | 2665.61ms | 7932 | 4890 | 317653 | 19216.7 | 0.0546861 | 13.0082 | 61.2099 | 10.986 | 0.0284187 | 9.04931e-05 | 5.16919e-05 | 2(Loss) | true |
