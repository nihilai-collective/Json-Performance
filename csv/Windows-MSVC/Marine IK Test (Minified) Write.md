
----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 725.192 | 0.115993 | 7473.82ms | 1834197 | 40 | 3.13121e+08 | 2.41209e+06 | 0.0570066 | 4.19079 | 1(Win) | true |
| Glaze | 587.503 | 0.100437 | 9204.67ms | 1833577 | 160 | 1.42984e+09 | 2.97638e+06 | 0.268292 | 5.17305 | 2(Loss) | true |
