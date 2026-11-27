
----
### Twitter Test (Minified) Write Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Glaze | 5330.24 | 0.216038 | 8665.97ms | 475954 | 4890 | 1.65503e+08 | 85156.5 | 0.0687627 | 0.570029 | 1(Win) | true |
| Jsonifier | 4212.48 | 0.123962 | 5465.26ms | 475954 | 2560 | 4.56744e+07 | 107752 | 1.12402 | 0.720789 | 2(Loss) | true |
