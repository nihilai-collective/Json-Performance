
----
### Marine IK Reverse Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1161.18 | 0.388288 | 9330.95ms | 1834197 | 160 | 5.47418e+09 | 1.50642e+06 | 0.964809 | 1(Win) | true |
| Glaze | 862.597 | 0.163215 | 6457.42ms | 1833577 | 40 | 4.37887e+08 | 2.02717e+06 | 1.11798 | 2(Loss) | true |
| simdjson (reflection) | 744.355 | 0.825262 | 8262.67ms | 1922245 | 30 | 1.23926e+10 | 2.4628e+06 | 0.998404 | 3(Loss) | true |
