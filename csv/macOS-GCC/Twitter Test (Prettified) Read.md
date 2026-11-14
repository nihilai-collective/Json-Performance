
----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1693.34 | 0.561383 | 5133.3ms | 360584 | 320 | 4.15904e+08 | 203078 | 0.372869 | 1(Win) | true |
| simdjson (ondemand) | 1671.1 | 0.169855 | 5264.5ms | 360584 | 160 | 1.95472e+07 | 205781 | 0.112614 | 2(Loss) | true |
