
----
### Marine IK Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 718.203 | 0.281531 | 8872.4ms | 1834197 | 160 | 7.52262e+09 | 2.43556e+06 | 1.09209 | 1(Win) | true |
| Jsonifier (two-stage) | 600.109 | 0.38071 | 10338.1ms | 1834197 | 80 | 9.85168e+09 | 2.91485e+06 | 0.565197 | 2(Loss) | true |
| Glaze | 483.942 | 0.563363 | 6021.07ms | 1834197 | 40 | 1.6586e+10 | 3.61454e+06 | 0.393698 | 3(Loss) | true |
| simdjson (ondemand) | 412.329 | 0.479415 | 7059.55ms | 1834197 | 80 | 3.30917e+10 | 4.24231e+06 | 0.888054 | 4(Loss) | true |
