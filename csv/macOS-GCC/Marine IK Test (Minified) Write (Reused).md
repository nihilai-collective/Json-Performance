
----
### Marine IK Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier DID NOT CONVERGE | 1202.35 | 0.490443 | 9504.06ms | 1922245 | 160 | 8.94652e+09 | 1.52468e+06 | 5.5616 | -(Win) | false |
| simdjson (reflection) | 1083.11 | 0.480161 | 5347.52ms | 1922245 | 80 | 5.28372e+09 | 1.69253e+06 | 0.485026 | 2(Loss) | true |
| Glaze | 756.393 | 1.23291 | 7117.87ms | 1833577 | 30 | 2.43718e+10 | 2.31181e+06 | 2.66676 | 3(Loss) | true |
