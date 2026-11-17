
----
### Marine IK Reverse Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 6519.68 | 0.23716 | 9317.2ms | 9930848 | 40 | 4.74749e+08 | 1.45265e+06 | 0.0905467 | 1(Win) | true |
| Glaze | 3060.64 | 0.200101 | 9796.63ms | 9930228 | 160 | 6.13352e+09 | 3.09419e+06 | 0.0966356 | 2(Loss) | true |
| simdjson (reflection) DID NOT CONVERGE | 255.664 | 1.04444 | 10709.4ms | 10018896 | 30 | 4.57076e+12 | 3.73723e+07 | 7.08361 | -(Loss) | false |
