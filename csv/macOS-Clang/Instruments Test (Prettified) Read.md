
----
### Instruments Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1879.22 | 0.242976 | 9382.73ms | 183677 | 40 | 2.05184e+06 | 93213.4 | 0.119511 | 1(Win) | true |
| simdjson (ondemand) | 1786.95 | 0.0948725 | 5080.77ms | 183677 | 1280 | 1.10707e+07 | 98026 | 0.0245435 | 2(Loss) | true |
