
----
### Marine IK Small Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2088.28 | 0.0860455 | 215.925ms | 4604 | 160 | 523.683 | 2102.55 | 0.0237863 | 1(Win) | true |
| simdjson (ondemand) | 1334.09 | 0.0404321 | 335.706ms | 4604 | 160 | 283.319 | 3291.18 | 0.0473078 | 2(Loss) | true |
