
----
### Marine IK Reverse Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1258.11 | 0.314001 | 8833.07ms | 1834197 | 320 | 6.09916e+09 | 1.39037e+06 | 1.00856 | 1(Win) | true |
| Glaze | 858.184 | 0.20331 | 6715.38ms | 1833577 | 40 | 6.86463e+08 | 2.0376e+06 | 0.516619 | 2(Loss) | true |
| simdjson (reflection) | 720.675 | 0.429176 | 7858.76ms | 1922245 | 160 | 1.90691e+10 | 2.54372e+06 | 4.24706 | 3(Loss) | true |
