
----
### Twitter Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1912.37 | 0.12689 | 6835.06ms | 264040 | 2560 | 7.14646e+07 | 131673 | 0.565679 | 1.29428 | 1(Win) | true |
| Jsonifier (generic) | 1828.85 | 0.0900061 | 7098.12ms | 264040 | 640 | 9.82892e+06 | 137686 | 0.0305821 | 1.35334 | 2(Loss) | true |
