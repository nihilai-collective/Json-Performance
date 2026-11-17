
----
### Marine IK Small Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1569.35 | 0.023069 | 284.569ms | 4604 | 160 | 66.6516 | 2797.8 | 0.161918 | 1.56323 | 1(Win) | true |
| simdjson (reflection) | 1284.99 | 0.0388456 | 359.837ms | 4918 | 30 | 60.3092 | 3649.97 | 0.0602382 | 1.91288 | 2(Loss) | true |
| Glaze | 1095.04 | 0.506978 | 404.397ms | 4604 | 1280 | 528926 | 4009.62 | 0.372344 | 2.24652 | 3(Loss) | true |
