
----
### Marine IK Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 689.336 | 0.205566 | 7904.64ms | 1834197 | 80 | 2.17682e+09 | 2.53755e+06 | 0.0493819 | 1(Win) | true |
| Jsonifier (two-stage) | 599.35 | 0.143184 | 9104.83ms | 1834197 | 160 | 2.79411e+09 | 2.91854e+06 | 0.304023 | 2(Loss) | true |
| Glaze | 490.272 | 0.22757 | 5362.86ms | 1834197 | 30 | 1.97773e+09 | 3.56787e+06 | 0.000426957 | 3(Loss) | true |
| simdjson (ondemand) | 415.8 | 0.150547 | 6362.72ms | 1834197 | 80 | 3.20891e+09 | 4.20689e+06 | 0.0023673 | 4(Loss) | true |
