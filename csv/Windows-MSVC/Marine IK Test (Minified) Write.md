
----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 894.602 | 0.0662479 | 6145.25ms | 1834197 | 40 | 6.71175e+07 | 1.95531e+06 | 0.104265 | 2.76739 | 1(Win) | true |
| Glaze | 626.183 | 0.10695 | 8776.36ms | 1833577 | 30 | 2.67595e+08 | 2.79253e+06 | 0.0233903 | 3.95369 | 2(Loss) | true |
