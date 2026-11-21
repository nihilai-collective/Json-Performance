
----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 4759.97 | 0.539748 | 6159.03ms | 10018896 | 80 | 9.39082e+09 | 2.00732e+06 | 0.523871 | 1(Win) | true |
| Glaze | 2504.3 | 0.509429 | 5725.13ms | 9930228 | 80 | 2.96895e+10 | 3.78157e+06 | 0.601281 | 2(Loss) | true |
