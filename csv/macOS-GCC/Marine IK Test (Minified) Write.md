
----
### Marine IK Test (Minified) Write Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1235.67 | 0.330001 | 9631.83ms | 1922245 | 320 | 7.66992e+09 | 1.48356e+06 | 0.764527 | 1(Win) | true |
| simdjson (reflection) | 1056.71 | 0.655554 | 5426.93ms | 1922245 | 40 | 5.17352e+09 | 1.73482e+06 | 1.72596 | 2(Loss) | true |
| Glaze | 748.28 | 0.450365 | 7287.6ms | 1833577 | 160 | 1.77223e+10 | 2.33687e+06 | 0.853293 | 3(Loss) | true |
