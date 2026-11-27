
----
### Instruments Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 833.497 | 0.172824 | 5450.73ms | 183677 | 80 | 1.05536e+07 | 210160 | 0.202316 | 1(Win) | true |
| simdjson (ondemand) | 271.698 | 0.163039 | 8263.71ms | 183677 | 160 | 1.76781e+08 | 644715 | 0.0208188 | 2(Loss) | true |
