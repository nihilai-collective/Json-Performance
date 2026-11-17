
----
### Marine IK Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1783.68 | 0.573756 | 246.259ms | 4604 | 2560 | 510658 | 2461.6 | 0.33423 | 1(Win) | true |
| simdjson (reflection) | 1677.46 | 0.735288 | 290.057ms | 4918 | 1280 | 541002 | 2796 | 0.667898 | 2(Loss) | true |
| Glaze | 1116.89 | 0.249843 | 402.469ms | 4604 | 2560 | 246960 | 3931.2 | 0.606796 | 3(Loss) | true |
