
----
### Marine IK Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 9535.27 | 0.313157 | 255.541ms | 24579 | 4890 | 289798 | 2458.28 | 0.191613 | 1(Win) | true |
| Glaze | 3820.44 | 0.107225 | 619.722ms | 24579 | 4890 | 211643 | 6135.52 | 0.0557561 | 2(Loss) | true |
| simdjson (reflection) | 323.212 | 0.356671 | 7924.45ms | 24893 | 80 | 5.49041e+06 | 73449.6 | 0.380478 | 3(Loss) | true |
