
----
### Marine IK Small Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1903.46 | 0.431839 | 234.858ms | 4604 | 2560 | 254018 | 2306.7 | 0.744406 | 1(Win) | true |
| simdjson (reflection) | 1506.45 | 0.484136 | 320.987ms | 4918 | 1280 | 290814 | 3113.4 | 0.238249 | 2(Loss) | true |
| Glaze | 996.798 | 0.355992 | 447.102ms | 4604 | 4890 | 1.20239e+06 | 4404.82 | 3.48705 | 3(Loss) | true |
