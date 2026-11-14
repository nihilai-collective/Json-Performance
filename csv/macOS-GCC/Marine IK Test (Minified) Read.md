
----
### Marine IK Test (Minified) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (stage-1) | 3501.6 | 0.606188 | 6773.74ms | 1834197 | 160 | 1.46721e+09 | 499550 | 1.31145 | 1(Win) | true |
| Jsonifier | 3046.54 | 0.527691 | 7452.35ms | 1834197 | 160 | 1.46878e+09 | 574168 | 0.499339 | 2(Loss) | true |
