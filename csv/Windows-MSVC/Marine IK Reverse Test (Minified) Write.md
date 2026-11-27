
----
### Marine IK Reverse Test (Minified) Write Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 978.937 | 0.095453 | 5946.1ms | 1922245 | 160 | 5.1122e+08 | 1.87264e+06 | 0.00864496 | 2.52894 | 1(Win) | true |
| Glaze | 483.602 | 0.0910858 | 5438.8ms | 1833577 | 30 | 3.2542e+08 | 3.61585e+06 | 0.544918 | 5.11937 | 2(Loss) | true |
