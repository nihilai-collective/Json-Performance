
----
### Marine IK Test (Minified) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 7675.29 | 0.231585 | 5819.19ms | 1834197 | 1280 | 3.56561e+08 | 227904 | 0.962324 | 0.395778 | 1(Win) | true |
| simdjson (stage-1) | 6506 | 0.404325 | 6891.81ms | 1834197 | 640 | 7.5632e+08 | 268864 | 0.0167399 | 0.466952 | 2(Loss) | true |
