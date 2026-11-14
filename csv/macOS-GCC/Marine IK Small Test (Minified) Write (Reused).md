
----
### Marine IK Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1889.86 | 0.435439 | 239.544ms | 4604 | 2560 | 262002 | 2323.3 | 4.32007 | 1(Win) | true |
| simdjson (reflection) | 1574.36 | 0.393771 | 297.994ms | 4918 | 2560 | 352288 | 2979.1 | 2.59315 | 2(Loss) | true |
| Glaze | 1090.7 | 0.851593 | 410.901ms | 4604 | 40 | 47009.5 | 4025.6 | 0.892857 | 3(Loss) | true |
