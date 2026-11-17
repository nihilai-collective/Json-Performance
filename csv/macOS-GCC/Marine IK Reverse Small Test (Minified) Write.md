
----
### Marine IK Reverse Small Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1673.04 | 0.67656 | 258.477ms | 4604 | 2560 | 807074 | 2624.4 | 0.837624 | 1(Win) | true |
| simdjson (reflection) | 1562.56 | 0.609804 | 306.376ms | 4918 | 40 | 13401.3 | 3001.6 | 0.0710227 | 2(Loss) | true |
| Glaze | 979.178 | 0.251571 | 447.365ms | 4604 | 4890 | 622267 | 4484.08 | 0.142561 | 3(Loss) | true |
