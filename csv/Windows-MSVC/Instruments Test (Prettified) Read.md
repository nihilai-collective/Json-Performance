
----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1554.59 | 0.250242 | 5897.4ms | 183677 | 640 | 5.08837e+07 | 112678 | 0.0768819 | 1.59221 | 1(Win) | true |
| simdjson (ondemand) | 1281.85 | 0.126493 | 6999.17ms | 183677 | 2560 | 7.64898e+07 | 136652 | 0.279572 | 1.931 | 2(Loss) | true |
