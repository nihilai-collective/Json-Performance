
----
### Marine IK Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1282.49 | 0.520295 | 9047.68ms | 1834197 | 160 | 8.05756e+09 | 1.36393e+06 | 0.470141 | 1(Win) | true |
| Glaze | 846.07 | 1.11554 | 6483.46ms | 1833577 | 30 | 1.59468e+10 | 2.06677e+06 | 0.168326 | 2(Loss) | true |
| simdjson (reflection) | 694.357 | 0.432004 | 7939.6ms | 1922245 | 160 | 2.08136e+10 | 2.64013e+06 | 1.38308 | 3(Loss) | true |
