
----
### Marine IK Reverse Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1287.74 | 0.85823 | 8830.89ms | 1834197 | 40 | 5.43634e+09 | 1.35837e+06 | 1.92745 | 1(Win) | true |
| Glaze | 800.003 | 0.796802 | 6647.3ms | 1833577 | 40 | 1.21332e+10 | 2.18579e+06 | 0.292777 | 2(Loss) | true |
| simdjson (reflection) | 696.739 | 1.3839 | 8164.88ms | 1922245 | 30 | 3.97745e+10 | 2.63111e+06 | 0.047977 | 3(Loss) | true |
