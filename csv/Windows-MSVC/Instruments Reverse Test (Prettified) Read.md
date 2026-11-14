
----
### Instruments Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 748.123 | 0.25121 | 5969.68ms | 183677 | 30 | 1.03791e+07 | 234143 | 0.0512769 | 4.0625 | 1(Win) | true |
| simdjson (ondemand) | 317.759 | 0.474385 | 6980.59ms | 183677 | 80 | 5.47097e+08 | 551260 | 0.12487 | 9.56474 | 2(Loss) | true |
