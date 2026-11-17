
----
### Marine IK Reverse Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1266.35 | 0.531586 | 8970.92ms | 1834197 | 320 | 1.72538e+10 | 1.38132e+06 | 0.804617 | 1(Win) | true |
| Glaze | 752.693 | 0.528547 | 7137.27ms | 1833577 | 160 | 2.41241e+10 | 2.32317e+06 | 1.71438 | 2(Loss) | true |
| simdjson (reflection) | 739.364 | 0.583203 | 7790.87ms | 1922245 | 40 | 8.36374e+09 | 2.47942e+06 | 1.42473 | 3(Loss) | true |
